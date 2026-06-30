//
// Created by Eniola Olawale on 16/12/2025.
//

#pragma once

#include <iostream>
#include <filesystem>
#include <functional>
#include <sqlite3.h>
#include <map>

#include "asset_record.h"
using AssetRecordMap = std::unordered_map<commons::PUUID, commons::AssetRecord>;
using AssetFilter = std::function<bool(const commons::AssetRecord&)>;


namespace commons::database {

	class COMMON_API ContentIndex {
		sqlite3* db = nullptr;
	public:
		ContentIndex() = default;
		~ContentIndex();

		ContentIndex(const ContentIndex&) = delete;
		ContentIndex& operator=(const ContentIndex&) = delete;

		bool create_or_open_db(const std::filesystem::path& file_path);

		[[nodiscard]] bool execute(const std::filesystem::path& sql_path) const;

		[[nodiscard]] bool execute(const std::string& sql_query) const;

		[[maybe_unused]] bool insertAsset(AssetRecord& record) const;
		[[nodiscard]] AssetRecordMap readAllAssets(const AssetFilter& filter) const;
		[[nodiscard]] std::optional<AssetRecord> readAssetByUUID(const commons::PUUID& uuid) const;
		std::optional<AssetRecord> construct_single_asset_record_and_finalize(sqlite3_stmt* stmt) const;
		[[nodiscard]] std::optional<AssetRecord> readAssetById(int64_t id) const;
		[[nodiscard]] std::optional<AssetRecord> readAssetByRelPathUnique(const std::string& rel_path) const;
		[[nodiscard]] bool updateAsset(const AssetRecord& record) const;
		[[nodiscard]] bool deleteAsset(const int64_t id) const;

		void close_db();

	};

} // database // commons

