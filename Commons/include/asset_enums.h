//
// Created by Eniola Olawale on 17/12/2025.
//

#pragma once

#define P_ENUM_FLAG_BIT(index) 1 << index
#include <cstdint>
#include "common_macros.h"

namespace commons{
	enum class COMMON_API QueryOperation
	{
		Read, Write, Update, Delete
	};

	enum class COMMON_API AssetType : uint32_t {
		None                    = 0,

		TextureAsset            = 1,
		SpriteAsset             = 2,
		ShaderAsset             = 3,

		MeshAsset               = 10,
		StaticMeshAsset         = 11,
		SkeletonAsset           = 12,
		P2DPolygonMeshAsset     = 13,

		MaterialAsset           = 20,
		RenderMapAsset          = 21,

		SoundSourceAsset        = 30,
		P3DSoundSourceAsset     = 31,

		ParticleAsset           = 40,
		SplineAsset             = 41,

		LevelAsset              = 50,
		ProjectAsset            = 52,

		// reserve ranges, never reuse
	};

	enum class COMMON_API AssetRepresentation: uint8_t
	{
		Native = 0, // meta file is runtime.
		Imported = 1, // meta + bin files
	};
}

