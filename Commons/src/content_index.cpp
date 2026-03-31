//
// Created by Eniola Olawale on 16/12/2025.
//

#include "content_index.h"
#include "serialize_utilities.h"
#include "time_manager.h"


namespace commons::database {
	ContentIndex::~ContentIndex()
	{
		close_db();
	}

	bool ContentIndex::create_or_open_db(const std::filesystem::path& file_path)
	{
		close_db();

		const int rc = sqlite3_open(file_path.string().c_str(), &db);
		if (rc != SQLITE_OK)
		{
			std::cerr << "Error Loading/Creating Database" << (db ? sqlite3_errmsg(db) : "unknown error") << std::endl;
			if (db)
			{
				sqlite3_close_v2(db);
				db = nullptr;
			}
			return false;
		}
		std::cout << "Opening/Creating Database is successful..." << std::endl;
		return true;
	}

	bool ContentIndex::execute(const std::filesystem::path& sql_path) const
	{
		const std::string sql_query = fileIO::extractSourceFromFile(sql_path.string().c_str());
		return execute(sql_query);
	}

	bool ContentIndex::execute(const std::string& sql_query) const
	{
		if (!db) return false;
		char* err_msg = nullptr;
		if(sqlite3_exec(db, sql_query.c_str(), nullptr, nullptr, &err_msg) != SQLITE_OK)
		{
			std::cerr << "SQL Error" << (err_msg ? err_msg : sqlite3_errmsg(db)) << std::endl;
			sqlite3_free(err_msg);
			return false;
		}
		std::cout << "SQL Executed successfully..." << std::endl;
		return true;
	}

	bool ContentIndex::insertAsset(AssetRecord& record) const
	{
		if (!db) return false;

		const char* sql =
			"INSERT INTO assets ("
			"uuid, name, asset_type, representation, "
			"meta_path, source_path, binary_path, "
			"is_dirty, is_deleted, created_at, modified_at"
			") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

		sqlite3_stmt* stmt = nullptr;

		if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
		{
			std::cerr << "SQLite prepare failed: " << sqlite3_errmsg(db) << std::endl;
			return false;
		}

		sqlite3_bind_text(stmt, 1, static_cast<std::string>(record.uuid).c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 2, record.name.c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_int(stmt, 3, static_cast<int>(record.assetType));
		sqlite3_bind_int(stmt, 4, static_cast<int>(record.representation));
		sqlite3_bind_text(stmt, 5, record.metaPath.string().c_str(), -1, SQLITE_TRANSIENT);

		if (record.sourcePath)
			sqlite3_bind_text(stmt, 6, record.sourcePath->string().c_str(), -1, SQLITE_TRANSIENT);
		else
			sqlite3_bind_null(stmt, 6);

		if (record.binaryPath)
			sqlite3_bind_text(stmt, 7, record.binaryPath->string().c_str(), -1, SQLITE_TRANSIENT);
		else
			sqlite3_bind_null(stmt, 7);

		sqlite3_bind_int(stmt, 8, record.isDirty ? 1 : 0);
		sqlite3_bind_int(stmt, 9, record.isDeleted ? 1 : 0);
		sqlite3_bind_int64(stmt, 10, record.createdAt);
		sqlite3_bind_int64(stmt, 11, record.modifiedAt);

		const bool success = (sqlite3_step(stmt) == SQLITE_DONE);

		if (success)
		{
			record.id = sqlite3_last_insert_rowid(db);
		}
		else
		{
			std::cerr << "SQLite insert failed: " << sqlite3_errmsg(db) << std::endl;
		}

		sqlite3_finalize(stmt);
		return success;
	}

	AssetRecordMap ContentIndex::readAllAssets(const AssetFilter& filter) const
	{
	    AssetRecordMap records;
		if (!db) return records;

	    const char* sql =
	        "SELECT "
	        "id, uuid, name, asset_type, representation, "
	        "meta_path, source_path, binary_path, "
	        "is_dirty, is_deleted, created_at, modified_at "
	        "FROM assets "
	        "WHERE is_deleted = 0;";

	    sqlite3_stmt* stmt = nullptr;

	    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
	    {
	    	std::cerr << "SQLite prepare failed: " << sqlite3_errmsg(db) << std::endl;
	    	return records;
	    }

	    while (sqlite3_step(stmt) == SQLITE_ROW)
	    {
	        AssetRecord record;
			if (!db) return records;

	        record.id = sqlite3_column_int64(stmt, 0);

	    	const unsigned char* uuidText = sqlite3_column_text(stmt, 1);
	    	const unsigned char* nameText = sqlite3_column_text(stmt, 2);
	    	const unsigned char* metaText = sqlite3_column_text(stmt, 5);

	        // UUID (TEXT → std::string → PUUID)
	    	if (!uuidText || !nameText || !metaText)
	            continue; // corrupted row, skip

	    	record.uuid = commons::PUUID::fromString(std::string(reinterpret_cast<const char*>(uuidText)));
	        record.name = reinterpret_cast<const char*>(nameText);
	        record.metaPath = std::filesystem::path(reinterpret_cast<const char*>(metaText));


	        record.assetType = static_cast<AssetType>(
	            sqlite3_column_int(stmt, 3)
	        );

	        record.representation = static_cast<AssetRepresentation>(
	            sqlite3_column_int(stmt, 4)
	        );


	        // source_path (nullable)
	        {
	            const unsigned char* src = sqlite3_column_text(stmt, 6);
	            if (src)
	                record.sourcePath = std::filesystem::path(
	                    reinterpret_cast<const char*>(src)
	                );
	            else
	                record.sourcePath.reset();
	        }

	        // binary_path (nullable)
	        {
	            const unsigned char* bin = sqlite3_column_text(stmt, 7);
	            if (bin)
	                record.binaryPath = std::filesystem::path(
	                    reinterpret_cast<const char*>(bin)
	                );
	            else
	                record.binaryPath.reset();
	        }

	        record.isDirty   = sqlite3_column_int(stmt, 8) != 0;
	        record.isDeleted = sqlite3_column_int(stmt, 9) != 0;

	        record.createdAt  = sqlite3_column_int64(stmt, 10);
	        record.modifiedAt = sqlite3_column_int64(stmt, 11);

	    	// KEY FILTER HOOK (policy lives outside DB)
	    	if (filter && !filter(record))
	    		continue;

	        // Insert into map keyed by UUID
	        records.emplace(record.uuid, std::move(record));
	    }

	    sqlite3_finalize(stmt);
	    return records;
	}

	std::optional<AssetRecord> ContentIndex::readAssetByUUID(const commons::PUUID& uuid) const
	{
	    const char* sql =
	        "SELECT "
	        "id, uuid, name, asset_type, representation, "
	        "meta_path, source_path, binary_path, "
	        "is_dirty, is_deleted, created_at, modified_at "
	        "FROM assets "
	        "WHERE uuid = ? AND is_deleted = 0 "
	        "LIMIT 1;";

	    sqlite3_stmt* stmt = nullptr;

	    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
	        return std::nullopt;

	    sqlite3_bind_text(stmt, 1, static_cast<std::string>(uuid).c_str(), -1, SQLITE_TRANSIENT);

	    return construct_single_asset_record_and_finalize(stmt);
	}

	std::optional<AssetRecord> ContentIndex::construct_single_asset_record_and_finalize(sqlite3_stmt* stmt) const
	{
		AssetRecord record;
		bool found = false;

		if (sqlite3_step(stmt) == SQLITE_ROW)
		{
			found = true;

			const unsigned char* uuidText = sqlite3_column_text(stmt, 1);
			const unsigned char* nameText = sqlite3_column_text(stmt, 2);
			const unsigned char* metaText = sqlite3_column_text(stmt, 5);

			if (!uuidText || !nameText || !metaText)
			{
				sqlite3_finalize(stmt);
				return std::nullopt;
			}

			record.id = sqlite3_column_int64(stmt, 0);
			record.uuid = commons::PUUID::fromString(std::string(reinterpret_cast<const char*>(uuidText)));
			record.name = reinterpret_cast<const char*>(nameText);
			record.metaPath = std::filesystem::path(reinterpret_cast<const char*>(metaText));

			record.assetType = static_cast<AssetType>(
				sqlite3_column_int(stmt, 3)
			);

			record.representation = static_cast<AssetRepresentation>(
				sqlite3_column_int(stmt, 4)
			);

			const unsigned char* src = sqlite3_column_text(stmt, 6);
			record.sourcePath = src
				                    ? std::optional<std::filesystem::path>(reinterpret_cast<const char*>(src))
				                    : std::nullopt;

			const unsigned char* bin = sqlite3_column_text(stmt, 7);
			record.binaryPath = bin
				                    ? std::optional<std::filesystem::path>(reinterpret_cast<const char*>(bin))
				                    : std::nullopt;

			record.isDirty   = sqlite3_column_int(stmt, 8) != 0;
			record.isDeleted = sqlite3_column_int(stmt, 9) != 0;

			record.createdAt  = sqlite3_column_int64(stmt, 10);
			record.modifiedAt = sqlite3_column_int64(stmt, 11);
		}

		sqlite3_finalize(stmt);

		if (!found)
			return std::nullopt;

		return record;
	}

	std::optional<AssetRecord> ContentIndex::readAssetById(int64_t id) const
	{
		const char* sql =
			"SELECT "
			"id, uuid, name, asset_type, representation, "
			"meta_path, source_path, binary_path, "
			"is_dirty, is_deleted, created_at, modified_at "
			"FROM assets "
			"WHERE id = ? AND is_deleted = 0 "
			"LIMIT 1;";

		sqlite3_stmt* stmt = nullptr;

		if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
			return std::nullopt;

		sqlite3_bind_int64(stmt, 1, id);

		return construct_single_asset_record_and_finalize(stmt);
	}

	// TODO : Verify Method Correctness
	std::optional<AssetRecord> ContentIndex::readAssetByRelPathUnique(const std::string& rel_path) const
	{
		const char* sql =
			"SELECT "
			"id, uuid, name, asset_type, representation, "
			"meta_path, source_path, binary_path, "
			"is_dirty, is_deleted, created_at, modified_at "
			"FROM assets "
			"WHERE meta_path = ? AND is_deleted = 0 "
			"LIMIT 1;";

		sqlite3_stmt* stmt = nullptr;

		if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
			return std::nullopt;

		sqlite3_bind_text(stmt, 1, rel_path.c_str(), -1, SQLITE_TRANSIENT);

		return construct_single_asset_record_and_finalize(stmt);
	}

	bool ContentIndex::updateAsset(const AssetRecord& record) const
	{
		if (!db || record.id < 0)
			return false; // must already exist

		const char* sql =
			"UPDATE assets SET "
			"name = ?, "
			"asset_type = ?, "
			"representation = ?, "
			"meta_path = ?, "
			"source_path = ?, "
			"binary_path = ?, "
			"is_dirty = ?, "
			"modified_at = ? "
			"WHERE id = ?;";

		sqlite3_stmt* stmt = nullptr;

		if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
		{
			std::cerr << "SQLite prepare failed: " << sqlite3_errmsg(db) << std::endl;
			return false;
		}

		sqlite3_bind_text(stmt, 1, record.name.c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_int(stmt, 2, static_cast<int>(record.assetType));
		sqlite3_bind_int(stmt, 3, static_cast<int>(record.representation));
		sqlite3_bind_text(stmt, 4, record.metaPath.string().c_str(), -1, SQLITE_TRANSIENT);

		if (record.sourcePath)
			sqlite3_bind_text(stmt, 5, record.sourcePath->string().c_str(), -1, SQLITE_TRANSIENT);
		else
			sqlite3_bind_null(stmt, 5);

		if (record.binaryPath)
			sqlite3_bind_text(stmt, 6, record.binaryPath->string().c_str(), -1, SQLITE_TRANSIENT);
		else
			sqlite3_bind_null(stmt, 6);

		sqlite3_bind_int(stmt, 7, record.isDirty ? 1 : 0);
		sqlite3_bind_int64(stmt, 8, record.modifiedAt);
		sqlite3_bind_int64(stmt, 9, record.id);

		const bool success = (sqlite3_step(stmt) == SQLITE_DONE);
		if (!success)
		{
			std::cerr << "SQLite update failed: " << sqlite3_errmsg(db) << std::endl;
		}
		sqlite3_finalize(stmt);
		return success;
	}

	bool ContentIndex::deleteAsset(const int64_t id) const
	{
		if (!db) return false;

		const char* sql =
			"UPDATE assets SET "
			"is_deleted = 1, "
			"modified_at = ? "
			"WHERE id = ?;";

		sqlite3_stmt* stmt = nullptr;

		if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
		{
			std::cerr << "SQLite prepare failed: " << sqlite3_errmsg(db) << std::endl;
			return false;
		}

		sqlite3_bind_int64(stmt, 1, TimeManager::now_seconds());
		sqlite3_bind_int64(stmt, 2, id);

		bool success = (sqlite3_step(stmt) == SQLITE_DONE);
		if (!success)
		{
			std::cerr << "SQLite delete failed: " << sqlite3_errmsg(db) << std::endl;
		}
		sqlite3_finalize(stmt);
		return success;
	}



	void ContentIndex::close_db()
	{
		if (!db) return;
		sqlite3_close_v2(db);
		db = nullptr;
	}
} // database
// commons