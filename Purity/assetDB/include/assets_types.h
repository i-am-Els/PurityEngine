//
// Created by Eniola Olawale on 9/16/2024.
//

#pragma once

#include "asset_enums.h"
#include "buffer.h"
#include "handle_base.h"
#include "purity_core_pch.h"
#include "serialization_macros.h"
#include "vertex_array.h"
//#include <cereal/types/base_class.hpp>
//#include <cereal/types/memory.hpp>


using namespace commons;
using namespace isle_engine::math;
using namespace purity::graphics;

namespace purity::assetDB {

    class PURITY_API PAsset {
    protected:
        // void* m_data;
        PUUID id;

    public:
        PAsset() = default; /// TODO: We expect that serialisables should be created by the create() function call
        PURE_NODISCARD PAsset(void* data, const PUUID& id)
            : id(id)
        {
        }

        ~PAsset() = default;

        void setID(const PUUID& _id) { this->id = _id; }
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
            PTextureAsset() = default;
            void setType(std::string _type) { type = _type; }
        std::string getType() const { return type; }
        std::string type; // Diffuse or Normal
        //void setID(uint64_t uuid); 
    };

    class PURITY_API PSpriteAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PSpriteAsset)
            PSpriteAsset() = default;
            void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PShaderAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PShaderAsset)
            PShaderAsset() = default;
            void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PMeshAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PMeshAsset)
            PMeshAsset() = default;
            void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PSkeletonAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PSkeletonAsset)
            PSkeletonAsset() = default;
            void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PStaticMeshAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PStaticMeshAsset)
            PStaticMeshAsset() = default;
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

    class PURITY_API PMaterialAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PMaterialAsset)
            PMaterialAsset() = default;
            void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PSplineAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PSplineAsset)
            PSplineAsset() = default;
            void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PP2DPolygonMeshAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PP2DPolygonMeshAsset)
            PP2DPolygonMeshAsset() = default;
            void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PSoundSourceAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PSoundSourceAsset)
            PSoundSourceAsset() = default;
            void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PP3DSoundSourceAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PP3DSoundSourceAsset)
            PP3DSoundSourceAsset() = default;
            void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PLevelAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PLevelAsset)
            PLevelAsset() = default;
        explicit PLevelAsset(scene::PScene* scenePtr) : m_scene(scenePtr) {}
        void SetScene(scene::PScene* scenePtr) { m_scene = scenePtr; }
        scene::PScene* GetScene() const { return m_scene; }
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    private:
        scene::PScene* m_scene = nullptr;
    };

    class PURITY_API PParticleAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PParticleAsset)
            PParticleAsset() = default;
            void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PRenderMapAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PRenderMapAsset)
            PRenderMapAsset() = default;
            void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PProjectAsset final : public PAsset, public ISerializable {
    public:
        SERIALIZABLE(PProjectAsset)
            PProjectAsset() = default;
            std::string project_name;
        std::string start_up_scene;
        std::string projectDB;
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };
}