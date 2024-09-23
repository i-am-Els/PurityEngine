//
// Created by Eniola Olawale on 9/13/2024.
//

#pragma once

#include "pnt_core_pch.h"
#include "core_macros.h"
#include "assetdb_enums.h"
#include "assetdb_type_strategy.h"

namespace pnt::assetDB
{
    // Base Spec
    class PNT_API QuerySpec
    {
        friend class PAssetDatabase;
    public:
        explicit QuerySpec(AssetOperationStrategy* strategy)
            : strategy(strategy)
        {
        }

        [[nodiscard]] virtual QueryAssetType getAssetType() const
        {
            return m_type;
        }

        std::string rel_path;

        virtual ~QuerySpec()
        {
            delete strategy;
        }
    protected:
        AssetOperationStrategy* strategy;

    private:
        QueryAssetType m_type{};
    }; // BaseClass for the different QueryAssetType


    //
    // Derived Specs
    //

    class PNT_API QueryStaticMeshAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QueryStaticMeshAssetSpec(const std::string& meshName, const std::string& meshRelPath, const std::string& materialName)
            : QuerySpec(new StaticMeshAssetOperationStrategy()), m_meshName(meshName), m_meshRelPath(meshRelPath), m_materialName(materialName)
        {
        }

        ~QueryStaticMeshAssetSpec() override = default;
        QueryAssetType m_type = QueryAssetType::StaticMeshAsset;
        const std::string& m_meshName;
        const std::string& m_meshRelPath;
        const std::string& m_materialName;

        // and other rules
    };

    class PNT_API QueryMeshAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QueryMeshAssetSpec()
            : QuerySpec(new MeshAssetOperationStrategy())
        {
        }

        ~QueryMeshAssetSpec() override = default;
        QueryAssetType m_type = QueryAssetType::MeshAsset;

        // and other rules
    };

    class PNT_API QueryTextureAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QueryTextureAssetSpec()
            : QuerySpec(new TextureAssetOperationStrategy())
        {
        }

        ~QueryTextureAssetSpec() override = default;
        QueryAssetType m_type = QueryAssetType::TextureAsset;

        // and other rules
    };

    class PNT_API QuerySpriteAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QuerySpriteAssetSpec()
            : QuerySpec(new SpriteAssetOperationStrategy())
        {
        }

        ~QuerySpriteAssetSpec() override = default;
        QueryAssetType m_type = QueryAssetType::SpriteAsset;

        // and other rules
    };

    class PNT_API QueryShaderAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QueryShaderAssetSpec()
            : QuerySpec(new ShaderAssetOperationStrategy())
        {
        }

        ~QueryShaderAssetSpec() override = default;
        QueryAssetType m_type = QueryAssetType::ShaderAsset;

        // and other rules
    };

    class PNT_API QuerySkeletonAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QuerySkeletonAssetSpec()
            : QuerySpec(new SkeletonAssetOperationStrategy())
        {
        }

        ~QuerySkeletonAssetSpec() override = default;
        QueryAssetType m_type = QueryAssetType::SkeletonAsset;

        // and other rules
    };

    class PNT_API QueryMaterialAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QueryMaterialAssetSpec()
            : QuerySpec(new MaterialAssetOperationStrategy())
        {
        }

        ~QueryMaterialAssetSpec() override = default;
        QueryAssetType m_type = QueryAssetType::MaterialAsset;

        // and other rules
    };

    class PNT_API QuerySplineAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QuerySplineAssetSpec()
            : QuerySpec(new SplineAssetOperationStrategy())
        {
        }

        ~QuerySplineAssetSpec() override = default;
        QueryAssetType m_type = QueryAssetType::SplineAsset;

        // and other rules
    };

    class PNT_API QueryP2DPolygonMeshAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QueryP2DPolygonMeshAssetSpec()
            : QuerySpec(new P2DPolygonMeshAssetOperationStrategy())
        {
        }

        ~QueryP2DPolygonMeshAssetSpec() override = default;
        QueryAssetType m_type = QueryAssetType::P2DPolygonMeshAsset;

        // and other rules
    };

    class PNT_API QuerySoundSourceAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QuerySoundSourceAssetSpec()
            : QuerySpec(new SoundSourceAssetOperationStrategy())
        {
        }

        ~QuerySoundSourceAssetSpec() override = default;
        QueryAssetType m_type = QueryAssetType::SoundSourceAsset;

        // and other rules
    };

    class PNT_API QueryP3DSoundSourceAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QueryP3DSoundSourceAssetSpec()
            : QuerySpec(new SoundSourceAssetOperationStrategy())
        {
        }

        ~QueryP3DSoundSourceAssetSpec() override = default;
        QueryAssetType m_type = QueryAssetType::P3DSoundSourceAsset;

        // and other rules
    };

    class PNT_API QueryLevelAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QueryLevelAssetSpec()
            : QuerySpec(new LevelAssetOperationStrategy())
        {
        }

        ~QueryLevelAssetSpec() override = default;
        QueryAssetType m_type = QueryAssetType::LevelAsset;

        // and other rules
    };

    class PNT_API QueryParticleAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QueryParticleAssetSpec()
            : QuerySpec(new ParticleAssetOperationStrategy())
        {
        }

        ~QueryParticleAssetSpec() override = default;
        QueryAssetType m_type = QueryAssetType::ParticleAsset;

        // and other rules
    };

    class PNT_API QueryRenderMapAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QueryRenderMapAssetSpec()
            : QuerySpec(new RenderMapAssetOperationStrategy())
        {
        }

        ~QueryRenderMapAssetSpec() override = default;
        QueryAssetType m_type = QueryAssetType::RenderMapAsset;

        // and other rules
    };
}
