//
// Created by Eniola Olawale on 5/8/2024.
//

#pragma once

#include <vector>

#include "component.h"
#include "buffer.h"
#include "assets_types.h"

using namespace purity::graphics;

namespace purity::ecs{
    class P3DGeometricMeshSS;

    struct SMeshProfile{
        bool isVisible;
        std::string relAssetPath;
    };

    class PURITY_API PMeshComponent final : public PComponent{
    public:
        explicit PMeshComponent(PEntity *entity, SMeshProfile profile);
        ~PMeshComponent() override { PLog::echoMessage("Destroying mesh"); }

        void update(float deltaTime) override;
        void start() override;


        P_GET_COMPONENT_TYPE(PComponentType::PMeshComponent)
        SMeshProfile m_MeshProfile;

    private:
        assetDB::Ref<assetDB::PStaticMeshAsset>* meshHandle;
        static unsigned int s_count; // All components must have this

    protected:
        struct Vertex{
            std::vector<Vector3f> position;
            std::vector<Vector3f> normals;
            std::vector<Vector2f> textureCoord;
        } m_vertex_data;
        std::vector<unsigned int> m_indices;

        friend class P3DGeometricMeshSS;

    };
}
