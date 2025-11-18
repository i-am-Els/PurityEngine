#pragma once
#include "common_macros.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <nlohmann/json-schema.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using json_schema_validator = nlohmann::json_schema::json_validator;
using ordered_json = nlohmann::basic_json<nlohmann::ordered_map>;


namespace commons{
	const json pProjectSchema = R"(
	{
		"$schema": "http://json-schema.org/draft-07/schema#",
		"type" : "object",
		"properties" : {
			"project_name": {
				"type": "string"
			},
			"start_up_scene" : {
				"type": "string",
				"default": "Assets/Scenes/DefaultScene.pscene"
			},
			"projectDB" : {
				"type": "string"
			}
		},
		"required": ["project_name", "projectDB"]
	})"_json;

	const json pDatabaseSchema = R"(
	{
		"$schema": "http://json-schema.org/draft-07/schema#",
		"type": "object",
		"properties": {
		  "id": {
			"type": "string"
		  },
		  "assets": {
			"type": "array",
			"items": {
			  "$ref": "#/definitions/Asset"
			}
		  }
		},
		"required": ["id", "assets"],
		"definitions": {
		  "Asset": {
			"type": "object",
			"properties": {
			  "id": {
				"type": "string"
			  },
			  "path": {
				"type": "string"
			  }
			}
		  }
		}
	})"_json;

	const json pAssetSchema = R"(
	{
	  "$schema": "http://json-schema.org/draft-07/schema#",
	  "type": "object",
	  "properties": {
		"id": {
		  "type": "string"
		},
		"source": {
		  "type": "string",
		  "enum": ["asset", "prefab", "scene"]
		},
		"parentID": {
		  "type": "string"
		},
		"type_": {
		  "type": "string",
		  "enum": [
			"TextureAsset",
			"SpriteAsset",
			"ShaderAsset",
			"MeshAsset",
			"SkeletonAsset",
			"StaticMeshAsset",
			"MaterialAsset",
			"SplineAsset",
			"PolygonMeshAsset",
			"SoundSourceAsset",
			"3DSoundSourceAsset",
			"LevelAsset",
			"ParticleAsset",
			"RenderMapAsset"
		  ]
		},
		"data_": {
		  "$ref": "#/definitions/Data"
		},
		"ref_assets": {
		  "type": "array",
		  "items": {
			"$ref": "#/definitions/Ref_asset"
		  }
		}
	  },
	  "required": ["id", "source", "parentID", "type_", "data_"],
	  "definitions": {
		"Data": {
		  "type": "object"
		},
		"Ref_asset": {
		  "type": "string"
		}
	  }
	})"_json;

	bool COMMON_API _validateFileExistence(const std::string& path);
	bool COMMON_API _validateFileExistence(const std::filesystem::path& path);
	bool COMMON_API _validateSchemaAdherence(const std::string& path, const json& schema);

	namespace fileIO
	{
		std::string COMMON_API extractSourceFromFile(const char *path);
		std::optional<json> COMMON_API extractSourceFromJSON(const char *path);
	}
}
