//
// Created by Eniola Olawale on 9/16/2024.
//

#pragma once

#include "handle_base.h"

namespace pnt::assetDB{
    class PAsset {
        void * m_data;
    };


    // ---------------------------------------------------------
    // ---------------------- Asset Types ----------------------
    // ---------------------------------------------------------
    
    class PTextureAsset : public PAsset{

    };

    class PSpriteAsset : public PAsset{

    };

    class PShaderAsset : public PAsset{

    };

    class PMeshAsset : public PAsset{

    };

    class PSkeletonAsset : public PAsset{

    };

    class PStaticMeshAsset : public PAsset{

    };

    class PMaterialAsset : public PAsset{

    };

    class PSplineAsset : public PAsset{

    };

    class PP2DPolygonMeshAsset : public PAsset{

    };

    class PSoundSourceAsset : public PAsset{

    };

    class PP3DSoundSourceAsset : public PAsset{

    };

    class PLevelAsset : public PAsset{

    };

    class PParticleAsset : public PAsset{

    };

    class PRenderMapAsset : public PAsset{

    };

    // ----------------------------------------------------------------
    // ---------------------- Asset Type Handles ----------------------
    // ----------------------------------------------------------------
    template<typename AssetTypeRef>
    class PAssetHandle final : public PHandleBase{
    public:
        PAssetHandle();
        explicit PAssetHandle(AssetTypeRef* data);
        ~PAssetHandle() { delete m_data; }
        explicit operator PUUID() { return m_handleId; }

    protected:
        explicit operator AssetTypeRef*() { return m_data; } // THis conversion operator is a way to retrieve the data of the asset.

    private:
        AssetTypeRef* m_data;
    };

    template<typename AssetTypeRef>
    PAssetHandle<AssetTypeRef>::PAssetHandle() : PHandleBase() {
        m_data = nullptr;
    }

    template<typename AssetTypeRef>
    PAssetHandle<AssetTypeRef>::PAssetHandle(AssetTypeRef *data) : PHandleBase(), m_data(data) {

    }

}


