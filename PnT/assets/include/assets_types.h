//
// Created by Eniola Olawale on 9/16/2024.
//

#pragma once

#include "handle_base.h"

namespace pnt::assetDB{
    class PNT_API PAsset {
        void * m_data;
    };


    // ---------------------------------------------------------
    // ---------------------- Asset Types ----------------------
    // ---------------------------------------------------------
    
    class PNT_API PTextureAsset : public PAsset{

    };

    class PNT_API PSpriteAsset : public PAsset{

    };

    class PNT_API PShaderAsset : public PAsset{

    };

    class PNT_API PMeshAsset : public PAsset{

    };

    class PNT_API PSkeletonAsset : public PAsset{

    };

    class PNT_API PStaticMeshAsset : public PAsset{

    };

    class PNT_API PMaterialAsset : public PAsset{

    };

    class PNT_API PSplineAsset : public PAsset{

    };

    class PNT_API PP2DPolygonMeshAsset : public PAsset{

    };

    class PNT_API PSoundSourceAsset : public PAsset{

    };

    class PNT_API PP3DSoundSourceAsset : public PAsset{

    };

    class PNT_API PLevelAsset : public PAsset{

    };

    class PNT_API PParticleAsset : public PAsset{

    };

    class PNT_API PRenderMapAsset : public PAsset{

    };

    // ----------------------------------------------------------------
    // ---------------------- Asset Type Handles ----------------------
    // ----------------------------------------------------------------
    template<typename AssetTypeRef>
    class PNT_API PAssetHandle final : public PHandleBase{
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


