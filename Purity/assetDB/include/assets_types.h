//
// Created by Eniola Olawale on 9/16/2024.
//

#pragma once

#include "purity_core_pch.h"
#include "vertex_array.h"
#include "buffer.h"
#include "handle_base.h"
#include "ref_counted.h"
#include "assetdb_enums.h"


using namespace commons;
using namespace isle_engine::math;
using namespace purity::graphics;

namespace purity::assetDB {

    struct AssetMetadata {
        PUUID id;
        std::string rel_path;
        AssetType type;
    };


    class PURITY_API PAsset : public RefCounted {
    protected:
        void* m_data;
        PUUID id{};

    };


    // ---------------------------------------------------------
    // ---------------------- Asset Types ----------------------
    // ---------------------------------------------------------

    // Add getters and setters that should be exposed to handles in the asset classes, make them public, but make the asset constructor private.

    class PURITY_API PTextureAsset : public PAsset {
    public:
        uint64_t getID() { return id; }
        void getType(std::string _type) { type = _type; }
        std::string getType() const { return type; }
        std::string type; // Diffuse or Specular
        //void setID(uint64_t uuid); 
    };

    class PURITY_API PSpriteAsset : public PAsset {

    };

    class PURITY_API PShaderAsset : public PAsset {

    };

    class PURITY_API PMeshAsset : public PAsset {

    };

    class PURITY_API PSkeletonAsset : public PAsset {

    };

    class PURITY_API PStaticMeshAsset : public PAsset {
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

    class PURITY_API PMaterialAsset : public PAsset {

    };

    class PURITY_API PSplineAsset : public PAsset {

    };

    class PURITY_API PP2DPolygonMeshAsset : public PAsset {

    };

    class PURITY_API PSoundSourceAsset : public PAsset {

    };

    class PURITY_API PP3DSoundSourceAsset : public PAsset {

    };

    class PURITY_API PLevelAsset : public PAsset {

    };

    class PURITY_API PParticleAsset : public PAsset {

    };

    class PURITY_API PRenderMapAsset : public PAsset {

    };

}