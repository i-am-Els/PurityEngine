//
// Created by Eniola Olawale on 9/13/2024.
//

#pragma once

#include "purity_core_pch.h"
#include "core_macros.h"
#include "assetdb_enums.h"
#include "assetdb_type_strategy.h"

namespace purity::assetDB
{
    // Base Spec
    class PURITY_API QuerySpec
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
            PLog::echoMessage("Destroying query spec.");
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

    class PURITY_API QueryStaticMeshAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QueryStaticMeshAssetSpec(const std::string& meshName, const std::string& meshRelPath, const std::string& materialName)
            : QuerySpec(new StaticMeshAssetOperationStrategy()), m_meshName(meshName), m_meshRelPath(meshRelPath), m_materialName(materialName)
        {
        }

        ~QueryStaticMeshAssetSpec() override {
            PLog::echoMessage("Destroying static mesh query spec.");
        }
        QueryAssetType m_type = QueryAssetType::StaticMeshAsset;
        const std::string& m_meshName;
        const std::string& m_meshRelPath;
        const std::string& m_materialName;

        // and other rules
    };

    class PURITY_API QueryMeshAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QueryMeshAssetSpec()
            : QuerySpec(new MeshAssetOperationStrategy())
        {
        }

        ~QueryMeshAssetSpec() override {
            PLog::echoMessage("Destroying mesh query spec.");
        }
        QueryAssetType m_type = QueryAssetType::MeshAsset;

        // and other rules
    };

    class PURITY_API QueryTextureAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QueryTextureAssetSpec()
            : QuerySpec(new TextureAssetOperationStrategy())
        {
        }

        ~QueryTextureAssetSpec() override{
            PLog::echoMessage("Destroying texture query spec.");
        }
        QueryAssetType m_type = QueryAssetType::TextureAsset;

        // and other rules
    };

    class PURITY_API QuerySpriteAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QuerySpriteAssetSpec()
            : QuerySpec(new SpriteAssetOperationStrategy())
        {
        }

        ~QuerySpriteAssetSpec() override{
            PLog::echoMessage("Destroying material query spec.");
        }
        QueryAssetType m_type = QueryAssetType::SpriteAsset;

        // and other rules
    };

    class PURITY_API QueryShaderAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QueryShaderAssetSpec()
            : QuerySpec(new ShaderAssetOperationStrategy())
        {
        }

        ~QueryShaderAssetSpec() override{
            PLog::echoMessage("Destroying shader query spec.");
        }
        QueryAssetType m_type = QueryAssetType::ShaderAsset;

        // and other rules
    };

    class PURITY_API QuerySkeletonAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QuerySkeletonAssetSpec()
            : QuerySpec(new SkeletonAssetOperationStrategy())
        {
        }

        ~QuerySkeletonAssetSpec() override{
            PLog::echoMessage("Destroying skeleton query spec.");
        }
        QueryAssetType m_type = QueryAssetType::SkeletonAsset;

        // and other rules
    };

    class PURITY_API QueryMaterialAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QueryMaterialAssetSpec()
            : QuerySpec(new MaterialAssetOperationStrategy())
        {
        }

        ~QueryMaterialAssetSpec() override{
            PLog::echoMessage("Destroying material query spec.");
        }
        QueryAssetType m_type = QueryAssetType::MaterialAsset;

        // and other rules
    };

    class PURITY_API QuerySplineAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QuerySplineAssetSpec()
            : QuerySpec(new SplineAssetOperationStrategy())
        {
        }

        ~QuerySplineAssetSpec() override {
            PLog::echoMessage("Destroying spline query spec.");
        }
        QueryAssetType m_type = QueryAssetType::SplineAsset;

        // and other rules
    };

    class PURITY_API QueryP2DPolygonMeshAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QueryP2DPolygonMeshAssetSpec()
            : QuerySpec(new P2DPolygonMeshAssetOperationStrategy())
        {
        }

        ~QueryP2DPolygonMeshAssetSpec() override{
            PLog::echoMessage("Destroying 2d polygon query spec.");
        }
        QueryAssetType m_type = QueryAssetType::P2DPolygonMeshAsset;

        // and other rules
    };

    class PURITY_API QuerySoundSourceAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QuerySoundSourceAssetSpec()
            : QuerySpec(new SoundSourceAssetOperationStrategy())
        {
        }

        ~QuerySoundSourceAssetSpec() override{
            PLog::echoMessage("Destroying sound query spec.");
        }
        QueryAssetType m_type = QueryAssetType::SoundSourceAsset;

        // and other rules
    };

    class PURITY_API QueryP3DSoundSourceAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QueryP3DSoundSourceAssetSpec()
            : QuerySpec(new SoundSourceAssetOperationStrategy())
        {
        }

        ~QueryP3DSoundSourceAssetSpec() override {
            PLog::echoMessage("Destroying 3d sound query spec.");
        }
        QueryAssetType m_type = QueryAssetType::P3DSoundSourceAsset;

        // and other rules
    };

    class PURITY_API QueryLevelAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QueryLevelAssetSpec()
            : QuerySpec(new LevelAssetOperationStrategy())
        {
        }

        ~QueryLevelAssetSpec() override{
            PLog::echoMessage("Destroying level query spec.");
        }
        QueryAssetType m_type = QueryAssetType::LevelAsset;

        // and other rules
    };

    class PURITY_API QueryParticleAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QueryParticleAssetSpec()
            : QuerySpec(new ParticleAssetOperationStrategy())
        {
        }

        ~QueryParticleAssetSpec() override{
            PLog::echoMessage("Destroying particle query spec.");
        }
        QueryAssetType m_type = QueryAssetType::ParticleAsset;

        // and other rules
    };

    class PURITY_API QueryRenderMapAssetSpec final : public QuerySpec
    {
        friend class PAssetDatabase;
    public:
        QueryRenderMapAssetSpec()
            : QuerySpec(new RenderMapAssetOperationStrategy())
        {
        }

        ~QueryRenderMapAssetSpec() override {
            PLog::echoMessage("Destroying render map query spec.");
        }
        QueryAssetType m_type = QueryAssetType::RenderMapAsset;

        // and other rules
    };
}
