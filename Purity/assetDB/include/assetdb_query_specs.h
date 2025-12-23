//
// Created by Eniola Olawale on 9/13/2024.
//

#pragma once

#include "purity_core_pch.h"
#include "core_macros.h"
#include "asset_enums.h"
#include "assets_types.h"

using AssetType = commons::AssetType;


namespace purity::assetDB
{
    // Base Spec
    template<class AssetTypeRef>
    class PURITY_API QuerySpec
    {
        friend class PAssetDatabase;
    public:
        explicit QuerySpec(const AssetRecord& record) : assetRecord(record)
        {
        }

        PURE_NODISCARD virtual AssetType getAssetType() const
        {
            return m_type;
        }


        virtual ~QuerySpec()
        {
            PLog::echoMessage("Destroying query spec.");
        }

        AssetRecord assetRecord;

    private:
        const AssetType m_type{};
    }; // BaseClass for the different AssetType


    //
    // Derived Specs
    //

    template<>
    class PURITY_API QuerySpec<PStaticMeshAsset>
    {
        friend class PAssetDatabase;
    public:
        QuerySpec(const AssetRecord& record, const std::string& material_) : assetRecord(record)
        {
            m_meshName = record.name;
            m_meshRelPath = record.metaPath.string();
            m_materialName = material_;
        }

        ~QuerySpec() {
            PLog::echoMessage("Destroying static mesh query spec.");
        }
        const AssetType m_type = AssetType::StaticMeshAsset;
        std::string m_meshName;
        std::string m_meshRelPath;
        std::string m_materialName;
        AssetRecord assetRecord;

        // and other rules
    };

    template<>
    class PURITY_API QuerySpec<PMeshAsset>
    {
        friend class PAssetDatabase;
    public:
        QuerySpec(const AssetRecord& record)
            : assetRecord(record)
        {
        }

        ~QuerySpec() {
            PLog::echoMessage("Destroying mesh query spec.");
        }
        const AssetType m_type = AssetType::MeshAsset;
        AssetRecord assetRecord;

        // and other rules
    };

    template<>
    class PURITY_API QuerySpec<PTextureAsset>
    {
        friend class PAssetDatabase;
    public:
        QuerySpec(const AssetRecord& record)
            : assetRecord(record)
        {
        }

        ~QuerySpec() {
            PLog::echoMessage("Destroying texture query spec.");
        }
        const AssetType m_type = AssetType::TextureAsset;
        AssetRecord assetRecord;

        // and other rules
    };

    template<>
    class PURITY_API QuerySpec<PSpriteAsset>
    {
        friend class PAssetDatabase;
    public:
        QuerySpec(const AssetRecord& record)
            : assetRecord(record)
        {
        }

        ~QuerySpec() {
            PLog::echoMessage("Destroying material query spec.");
        }
        const AssetType m_type = AssetType::SpriteAsset;
        AssetRecord assetRecord;

        // and other rules
    };

    template<>
    class PURITY_API QuerySpec<PShaderAsset>
    {
        friend class PAssetDatabase;
    public:
        QuerySpec(const AssetRecord& record)
            : assetRecord(record)
        {
        }

        ~QuerySpec() {
            PLog::echoMessage("Destroying shader query spec.");
        }
        const AssetType m_type = AssetType::ShaderAsset;
        AssetRecord assetRecord;

        // and other rules
    };

    template<>
    class PURITY_API QuerySpec<PSkeletonAsset>
    {
        friend class PAssetDatabase;
    public:
        QuerySpec(const AssetRecord& record)
            : assetRecord(record)
        {
        }

        ~QuerySpec() {
            PLog::echoMessage("Destroying skeleton query spec.");
        }
        const AssetType m_type = AssetType::SkeletonAsset;
        AssetRecord assetRecord;

        // and other rules
    };

    template<>
    class PURITY_API QuerySpec<PMaterialAsset>
    {
        friend class PAssetDatabase;
    public:
        QuerySpec(const AssetRecord& record)
            : assetRecord(record)
        {
        }

        ~QuerySpec() {
            PLog::echoMessage("Destroying material query spec.");
        }
        const AssetType m_type = AssetType::MaterialAsset;
        AssetRecord assetRecord;

        // and other rules
    };

    template<>
    class PURITY_API QuerySpec<PSplineAsset>
    {
        friend class PAssetDatabase;
    public:
        QuerySpec(const AssetRecord& record)
            : assetRecord(record)
        {
        }

        ~QuerySpec() {
            PLog::echoMessage("Destroying spline query spec.");
        }
        const AssetType m_type = AssetType::SplineAsset;
        AssetRecord assetRecord;

        // and other rules
    };

    template<>
    class PURITY_API QuerySpec<PP2DPolygonMeshAsset>
    {
        friend class PAssetDatabase;
    public:
        QuerySpec(const AssetRecord& record)
            : assetRecord(record)
        {
        }

        ~QuerySpec() {
            PLog::echoMessage("Destroying 2d polygon query spec.");
        }
        const AssetType m_type = AssetType::P2DPolygonMeshAsset;
        AssetRecord assetRecord;

        // and other rules
    };

    template<>
    class PURITY_API QuerySpec<PSoundSourceAsset>
    {
        friend class PAssetDatabase;
    public:
        QuerySpec(const AssetRecord& record)
            : assetRecord(record)
        {
        }

        ~QuerySpec() {
            PLog::echoMessage("Destroying sound query spec.");
        }
        const AssetType m_type = AssetType::SoundSourceAsset;
        AssetRecord assetRecord;

        // and other rules
    };

    template<>
    class PURITY_API QuerySpec<PP3DSoundSourceAsset>
    {
        friend class PAssetDatabase;
    public:
        QuerySpec(const AssetRecord& record)
            : assetRecord(record)
        {
        }

        ~QuerySpec() {
            PLog::echoMessage("Destroying 3d sound query spec.");
        }
        const AssetType m_type = AssetType::P3DSoundSourceAsset;
        AssetRecord assetRecord;

        // and other rules
    };

    template<>
    class PURITY_API QuerySpec<PLevelAsset>
    {
        friend class PAssetDatabase;
    public:
        explicit QuerySpec(const AssetRecord& record)
            : assetRecord(record)
        {
        }

        ~QuerySpec() {
            PLog::echoMessage("Destroying level query spec.");
        }

        const AssetType m_type = AssetType::LevelAsset;
        AssetRecord assetRecord;
        // and other rules
    };

    template<>
    class PURITY_API QuerySpec<PParticleAsset>
    {
        friend class PAssetDatabase;
    public:
        QuerySpec(const AssetRecord& record)
            : assetRecord(record)
        {
        }

        ~QuerySpec() {
            PLog::echoMessage("Destroying particle query spec.");
        }
        const AssetType m_type = AssetType::ParticleAsset;
        AssetRecord assetRecord;

        // and other rules
    };

    template<>
    class PURITY_API QuerySpec<PRenderMapAsset>
    {
        friend class PAssetDatabase;
    public:
        QuerySpec(const AssetRecord& record)
            : assetRecord(record)
        {
        }

        ~QuerySpec() {
            PLog::echoMessage("Destroying render map query spec.");
        }
        const AssetType m_type = AssetType::RenderMapAsset;
        AssetRecord assetRecord;

        // and other rules
    };
}
