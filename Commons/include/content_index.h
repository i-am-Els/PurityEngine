//
// Created by Eniola Olawale on 16/12/2025.
//

#pragma once

#include <filesystem>
#include <iostream>
#include <sqlite3.h>

#include "asset_record.h"

namespace commons::database {

	class COMMON_API ContentIndex {
		sqlite3* db;
	public:
		ContentIndex() = default;
		~ContentIndex();

		ContentIndex(const ContentIndex&) = delete;
		ContentIndex& operator=(const ContentIndex&) = delete;

		bool create_or_open_db(const std::filesystem::path& file_path);

		bool execute(const std::filesystem::path& sql_path) const;

		bool execute(const std::string& sql_query) const;

		bool insertAsset(AssetRecord& record) const;

		void close_db() const;

	};

} // database // commons

