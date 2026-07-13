//
// Created by Eniola Olawale on 9/16/2024.
//

#pragma once

#include "asset_enums.h"
#include "buffer.h"
#include "handle_base.h"
#include "purity_core_pch.h"
#include "vertex_array.h"
#include "iidentifiable.h"
#include "scene_graph.h"
//#include <cereal/types/base_class.hpp>
//#include <cereal/types/memory.hpp>


using namespace commons;
using namespace isle_engine::math;
using namespace purity::graphics;

namespace purity::assetDB {

    class PURITY_API PAsset : public ISerializable, public IIdentifiable {

    public:
        PAsset() = default; /// TODO: We expect that serialisables should be created by the create() function call
        PURE_NODISCARD PAsset(void* data, const PUUID& id)
        {
            m_id = id;
        }

        ~PAsset() = default;


        void setUUID(const PUUID& _id) { this->m_id = _id; }
        PUUID getUUID() const { return m_id; }
    protected:
    };

    static_assert(std::derived_from<PAsset, IIdentifiable>);

    // ---------------------------------------------------------
    // ---------------------- Asset Types ----------------------
    // ---------------------------------------------------------

    // Add getters and setters that should be exposed to handles in the asset classes, make them public, but make the asset constructor private.

    class PURITY_API PTextureAsset final : public PAsset {
    public:
        PTextureAsset() = default;
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
        void setType(std::string _type) { type = _type; }
        std::string getType() const { return type; }
        std::string type; // Diffuse or Normal
        //void setID(uint64_t uuid); 
    };

    class PURITY_API PSpriteAsset final : public PAsset {
    public:
        PSpriteAsset() = default;
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PShaderAsset final : public PAsset  {
    public:
        PShaderAsset() = default;
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PMeshAsset final : public PAsset  {
    public:
        PMeshAsset() = default;
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PSkeletonAsset final : public PAsset  {
    public:
        PSkeletonAsset() = default;
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PStaticMeshAsset final : public PAsset  {
    public:
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

    class PURITY_API PMaterialAsset final : public PAsset  {
    public:
        PMaterialAsset() = default;
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PSplineAsset final : public PAsset  {
    public:
        PSplineAsset() = default;
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PP2DPolygonMeshAsset final : public PAsset  {
    public:
        PP2DPolygonMeshAsset() = default;
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PSoundSourceAsset final : public PAsset  {
    public:
        PSoundSourceAsset() = default;
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PP3DSoundSourceAsset final : public PAsset  {
    public:
        PP3DSoundSourceAsset() = default;
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PLevelAsset final : public PAsset  {
    public:
        PLevelAsset() = default;
        void SetSceneGraph(scene::PSceneGraph sceneGraph) { m_sceneGraph = sceneGraph; }
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    private:
        scene::PSceneGraph m_sceneGraph;
    };

    class PURITY_API PParticleAsset final : public PAsset  {
    public:
        PParticleAsset() = default;
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PRenderMapAsset final : public PAsset  {
    public:
        PRenderMapAsset() = default;
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };

    class PURITY_API PProjectAsset final : public PAsset  {
    public:
        PProjectAsset() = default;
        std::string project_name;
        std::string start_up_scene;
        std::string projectDB;
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
    };
}