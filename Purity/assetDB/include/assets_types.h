//
// Created by Eniola Olawale on 9/16/2024.
//

#pragma once

#include "assetdb_enums.h"
#include "buffer.h"
#include "handle_base.h"
#include "purity_core_pch.h"
#include "ref_counted.h"
#include "serialization_macros.h"
#include "vertex_array.h"


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
        PUUID id;

    public:
        PAsset() = default;
        PURE_NODISCARD PAsset(void* data, const PUUID& id)
            : m_data(data),
              id(id)
        {
        }

        ~PAsset() override = default;

    protected:
        PUUID getID() { return id; }
    };


    // ---------------------------------------------------------
    // ---------------------- Asset Types ----------------------
    // ---------------------------------------------------------

    // Add getters and setters that should be exposed to handles in the asset classes, make them public, but make the asset constructor private.

    class PURITY_API PTextureAsset final : public PAsset, public ISerializable {
    public:
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;

        SERIALIZABLE(PTextureAsset)
        void setType(std::string _type) { type = _type; }
        std::string getType() const { return type; }
        std::string type; // Diffuse or Normal
        //void setID(uint64_t uuid); 
    };

    class PURITY_API PSpriteAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PSpriteAsset)
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PShaderAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PShaderAsset)
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PMeshAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PMeshAsset)
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PSkeletonAsset final : public PAsset , public ISerializable {
    public:
        SERIALIZABLE(PSkeletonAsset)
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PStaticMeshAsset final : public PAsset , public ISerializable {
    public:
        SERIALIZABLE(PStaticMeshAsset)

        std::vector<PVertex> vertices;
        std::vector<unsigned int> indices;
        PUUID getTextureAsset() const { return refTextureAssetID; }
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
        //        std::vector<PTextureAsset> textures; // I think the texture asset should only be referenced.

    private:
        PUUID refTextureAssetID;
        VertexArray vao;
        VertexBuffer vbo;
        ElementBuffer ebo;
    };

    class PURITY_API PMaterialAsset final : public PAsset , public ISerializable {
    public:
        SERIALIZABLE(PMaterialAsset)
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PSplineAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PSplineAsset)
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PP2DPolygonMeshAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PP2DPolygonMeshAsset)
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PSoundSourceAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PSoundSourceAsset)
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PP3DSoundSourceAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PP3DSoundSourceAsset)
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PLevelAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PLevelAsset)
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PParticleAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PParticleAsset)
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PRenderMapAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PRenderMapAsset)
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

}