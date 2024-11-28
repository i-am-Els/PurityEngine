//
// Created by Eniola Olawale on 9/16/2024.
//

#pragma once


#include "pnt_core_pch.h"
#include "vertex_array.h"
#include "buffer.h"
#include "handle_base.h"

using namespace isle_engine::math;
using namespace pnt::graphics;

namespace pnt::assetDB{
    class PNT_API PAsset {
        void * m_data;
    };


    // ---------------------------------------------------------
    // ---------------------- Asset Types ----------------------
    // ---------------------------------------------------------

    // Add getters and setters that should be exposed to handles in the asset classes, make them public, but make the asset constructor private.
    
    class PNT_API PTextureAsset : public PAsset{
    public:
        uint64_t getID() { return id; }
        void getType(std::string _type) { type = _type; }
        std::string getType() const { return type; }
    private:
        uint64_t id{};
        std::string type; // Diffuse or Specular
        void setID(uint64_t uuid);
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
    public:
        std::vector<PVertex> vertices;
        std::vector<unsigned int> indices;
        PUUID getTextureAsset() const { return refTextureAssetID; }
//        std::vector<PTextureAsset> textures; // I think the texture asset should only be referenced.

    private:
        PUUID refTextureAssetID;
        VertexArray vao;
        VertexBuffer vbo;
        ElementBuffer ebo;
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
    class PNT_API PAssetHandle final : public fileIO::PHandleBase, public AssetTypeRef {
    public:
        PAssetHandle();
        explicit PAssetHandle(AssetTypeRef* data);
        ~PAssetHandle() {
            m_data = nullptr;
            PLog::echoMessage("Destroying Asset Handle");
        }
        explicit operator PUUID() { return m_handleId; }

    protected:
//        explicit operator AssetTypeRef*() { return m_data; } // THis conversion operator is a way to retrieve the data of the asset.

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


