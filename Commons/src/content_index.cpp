//
// Created by Eniola Olawale on 16/12/2025.
//

#include "content_index.h"
#include "serialize_utilities.h"


namespace commons::database {
	ContentIndex::~ContentIndex()
	{
		close_db();
	}

	bool ContentIndex::create_or_open_db(const std::filesystem::path& file_path)
	{
		if (const int obj = sqlite3_open(file_path.string().c_str(), &db); obj != SQLITE_OK)
		{
			std::cerr << "Error Loading/Creating Database" << sqlite3_errmsg(db) << std::endl;
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
		char* err_msg = nullptr;
		if (!db) return false;
		if(sqlite3_exec(db, sql_query.c_str(), nullptr, nullptr, &err_msg) != SQLITE_OK)
		{
			std::cerr << "SQL Error" << err_msg << std::endl;
			sqlite3_free(err_msg);
			return false;
		}
		std::cout << "Table Created successfully..." << std::endl;
		return true;
	}

	bool ContentIndex::insertAsset(AssetRecord& record) const
	{
		const char* sql =
			"INSERT INTO assets ("
			"uuid, name, asset_type, representation, "
			"meta_path, source_path, binary_path, "
			"is_dirty, is_deleted, created_at, modified_at"
			") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

		sqlite3_stmt* stmt = nullptr;

		if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
			return false;

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

		bool success = (sqlite3_step(stmt) == SQLITE_DONE);

		if (success)
			record.id = sqlite3_last_insert_rowid(db);

		sqlite3_finalize(stmt);
		return success;
	}


	void ContentIndex::close_db() const
	{
		sqlite3_close(db);
	}
} // database
// commons