//
// Created by Eniola Olawale on 9/13/2024.
//

#pragma once


#include "purity_core_pch.h"
#include "core_macros.h"
#include "assetdb_enums.h"
#include "assetdb_type_strategy.h"
#include "assets_types.h"


namespace purity::assetDB
{
    // Base Spec
    template<class AssetTypeRef>
    class PURITY_API QuerySpec
    {
        friend class PAssetDatabase;
    public:
        explicit QuerySpec(AssetOperationStrategy<AssetTypeRef>* strategy)
            : strategy(strategy)
        {
        }

        PURE_NODISCARD virtual AssetType getAssetType() const
        {
            return m_type;
        }

        // union u_asset_query_info
        // {
        //     std::string rel_path;
        //     PUUID asset_id;
        // } assetQueryInfo;

        std::variant<std::string, PUUID> assetQueryInfo;

        virtual ~QuerySpec()
        {
            PLog::echoMessage("Destroying query spec.");
            delete strategy;
        }
    protected:
        AssetOperationStrategy<AssetTypeRef>* strategy;

    private:
        AssetType m_type{};
    }; // BaseClass for the different AssetType


    //
    // Derived Specs
    //

    class PURITY_API QueryStaticMeshAssetSpec final : public QuerySpec<PStaticMeshAsset>
    {
        friend class PAssetDatabase;
    public:
        QueryStaticMeshAssetSpec(const std::string& meshName, const std::string& meshRelPath, const std::string& materialName)
            : QuerySpec<PStaticMeshAsset>(new StaticMeshAssetOperationStrategy()), m_meshName(meshName), m_meshRelPath(meshRelPath), m_materialName(materialName)
        {
        }

        ~QueryStaticMeshAssetSpec() override {
            PLog::echoMessage("Destroying static mesh query spec.");
        }
        AssetType m_type = AssetType::StaticMeshAsset;
        const std::string& m_meshName;
        const std::string& m_meshRelPath;
        const std::string& m_materialName;

        // and other rules
    };

    class PURITY_API QueryMeshAssetSpec final : public QuerySpec<PMeshAsset>
    {
        friend class PAssetDatabase;
    public:
        QueryMeshAssetSpec()
            : QuerySpec<PMeshAsset>(new MeshAssetOperationStrategy())
        {
        }

        ~QueryMeshAssetSpec() override {
            PLog::echoMessage("Destroying mesh query spec.");
        }
        AssetType m_type = AssetType::MeshAsset;

        // and other rules
    };

    class PURITY_API QueryTextureAssetSpec final : public QuerySpec<PTextureAsset>
    {
        friend class PAssetDatabase;
    public:
        QueryTextureAssetSpec()
            : QuerySpec<PTextureAsset>(new TextureAssetOperationStrategy())
        {
        }

        ~QueryTextureAssetSpec() override{
            PLog::echoMessage("Destroying texture query spec.");
        }
        AssetType m_type = AssetType::TextureAsset;

        // and other rules
    };

    class PURITY_API QuerySpriteAssetSpec final : public QuerySpec<PSpriteAsset>
    {
        friend class PAssetDatabase;
    public:
        QuerySpriteAssetSpec()
            : QuerySpec<PSpriteAsset>(new SpriteAssetOperationStrategy())
        {
        }

        ~QuerySpriteAssetSpec() override{
            PLog::echoMessage("Destroying material query spec.");
        }
        AssetType m_type = AssetType::SpriteAsset;

        // and other rules
    };

    class PURITY_API QueryShaderAssetSpec final : public QuerySpec<PShaderAsset>
    {
        friend class PAssetDatabase;
    public:
        QueryShaderAssetSpec()
            : QuerySpec<PShaderAsset>(new ShaderAssetOperationStrategy())
        {
        }

        ~QueryShaderAssetSpec() override{
            PLog::echoMessage("Destroying shader query spec.");
        }
        AssetType m_type = AssetType::ShaderAsset;

        // and other rules
    };

    class PURITY_API QuerySkeletonAssetSpec final : public QuerySpec<PSkeletonAsset>
    {
        friend class PAssetDatabase;
    public:
        QuerySkeletonAssetSpec()
            : QuerySpec<PSkeletonAsset>(new SkeletonAssetOperationStrategy())
        {
        }

        ~QuerySkeletonAssetSpec() override{
            PLog::echoMessage("Destroying skeleton query spec.");
            delete strategy;
        }
        AssetType m_type = AssetType::SkeletonAsset;

        // and other rules
    };

    class PURITY_API QueryMaterialAssetSpec final : public QuerySpec<PMaterialAsset>
    {
        friend class PAssetDatabase;
    public:
        QueryMaterialAssetSpec()
            : QuerySpec<PMaterialAsset>(new MaterialAssetOperationStrategy())
        {
        }

        ~QueryMaterialAssetSpec() override{
            PLog::echoMessage("Destroying material query spec.");
        }
        AssetType m_type = AssetType::MaterialAsset;

        // and other rules
    };

    class PURITY_API QuerySplineAssetSpec final : public QuerySpec<PSplineAsset>
    {
        friend class PAssetDatabase;
    public:
        QuerySplineAssetSpec()
            : QuerySpec<PSplineAsset>(new SplineAssetOperationStrategy())
        {
        }

        ~QuerySplineAssetSpec() override {
            PLog::echoMessage("Destroying spline query spec.");
        }
        AssetType m_type = AssetType::SplineAsset;

        // and other rules
    };

    class PURITY_API QueryP2DPolygonMeshAssetSpec final : public QuerySpec<PP2DPolygonMeshAsset>
    {
        friend class PAssetDatabase;
    public:
        QueryP2DPolygonMeshAssetSpec()
            : QuerySpec<PP2DPolygonMeshAsset>(new P2DPolygonMeshAssetOperationStrategy())
        {
        }

        ~QueryP2DPolygonMeshAssetSpec() override{
            PLog::echoMessage("Destroying 2d polygon query spec.");
        }
        AssetType m_type = AssetType::P2DPolygonMeshAsset;

        // and other rules
    };

    class PURITY_API QuerySoundSourceAssetSpec final : public QuerySpec<PSoundSourceAsset>
    {
        friend class PAssetDatabase;
    public:
        QuerySoundSourceAssetSpec()
            : QuerySpec<PSoundSourceAsset>(new SoundSourceAssetOperationStrategy())
        {
        }

        ~QuerySoundSourceAssetSpec() override{
            PLog::echoMessage("Destroying sound query spec.");
        }
        AssetType m_type = AssetType::SoundSourceAsset;

        // and other rules
    };

    class PURITY_API QueryP3DSoundSourceAssetSpec final : public QuerySpec<PP3DSoundSourceAsset>
    {
        friend class PAssetDatabase;
    public:
        QueryP3DSoundSourceAssetSpec()
            : QuerySpec<PP3DSoundSourceAsset>(new P3DSoundSourceAssetOperationStrategy())
        {
        }

        ~QueryP3DSoundSourceAssetSpec() override {
            PLog::echoMessage("Destroying 3d sound query spec.");
        }
        AssetType m_type = AssetType::P3DSoundSourceAsset;

        // and other rules
    };

    class PURITY_API QueryLevelAssetSpec final : public QuerySpec<PLevelAsset>
    {
        friend class PAssetDatabase;
    public:
        explicit QueryLevelAssetSpec(const PUUID& id)
            : QuerySpec<PLevelAsset>(new LevelAssetOperationStrategy())
        {
            assetQueryInfo = id;
        }

        explicit QueryLevelAssetSpec(const std::string& path)
            : QuerySpec<PLevelAsset>(new LevelAssetOperationStrategy())
        {
            assetQueryInfo = path;
        }

        ~QueryLevelAssetSpec() override{
            PLog::echoMessage("Destroying level query spec.");
        }
        AssetType m_type = AssetType::LevelAsset;
        // and other rules
    };

    class PURITY_API QueryParticleAssetSpec final : public QuerySpec<PParticleAsset>
    {
        friend class PAssetDatabase;
    public:
        QueryParticleAssetSpec()
            : QuerySpec<PParticleAsset>(new ParticleAssetOperationStrategy())
        {
        }

        ~QueryParticleAssetSpec() override{
            PLog::echoMessage("Destroying particle query spec.");
        }
        AssetType m_type = AssetType::ParticleAsset;

        // and other rules
    };

    class PURITY_API QueryRenderMapAssetSpec final : public QuerySpec<PRenderMapAsset>
    {
        friend class PAssetDatabase;
    public:
        QueryRenderMapAssetSpec()
            : QuerySpec<PRenderMapAsset>(new RenderMapAssetOperationStrategy())
        {
        }

        ~QueryRenderMapAssetSpec() override {
            PLog::echoMessage("Destroying render map query spec.");
        }
        AssetType m_type = AssetType::RenderMapAsset;

        // and other rules
    };
}
