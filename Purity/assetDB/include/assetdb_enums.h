//
// Created by Eniola Olawale on 9/13/2024.
//

#pragma once

#define P_ENUM_FLAG_BIT(index) 1 << index

namespace purity::assetDB{
    enum class QueryOperation
    {
        Read, Write, Update, Delete
    };

    enum class AssetType{
        None,
        TextureAsset,
        SpriteAsset,
        ShaderAsset,
        MeshAsset,
        SkeletonAsset,
        StaticMeshAsset,
        MaterialAsset,
        SplineAsset,
        P2DPolygonMeshAsset,
        SoundSourceAsset,
        P3DSoundSourceAsset,
        LevelAsset,
        ParticleAsset,
        RenderMapAsset
    };
}
