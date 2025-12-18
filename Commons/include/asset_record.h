//
// Created by Eniola Olawale on 17/12/2025.
//

#pragma once
#include <filesystem>
#include <optional>

#include "asset_enums.h"
#include "uuid.h"

namespace commons
{
	struct COMMON_API AssetRecord
	{
		int64_t id = -1; // DB assigned

		commons::PUUID uuid;

		std::string name;

		commons::AssetType assetType;
		commons::AssetRepresentation representation;

		std::filesystem::path metaPath;
		std::optional<std::filesystem::path> sourcePath;
		std::optional<std::filesystem::path> binaryPath;

		bool isDirty = false;
		bool isDeleted = false;

		int64_t createdAt = 0;
		int64_t modifiedAt = 0;
	};
}

