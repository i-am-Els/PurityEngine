//
// Created by Eniola Olawale on 5/8/2024.
//

#pragma once

#include <vector>

#include "component.h"
#include "buffer.h"
#include "assets_types.h"

using namespace pnt::graphics;
namespace pnt::mesh{
    class P3DGeometricMeshSS;
}

namespace pnt::ecs{
    struct SMeshProfile{
        bool isVisible;
        std::string relAssetPath;
    };

    class PNT_API PMeshComponent final : public PComponent{
    public:
        explicit PMeshComponent(PEntity *entity, SMeshProfile profile);
        ~PMeshComponent() override { PLog::echoMessage("Destroying mesh"); }

        void update(float deltaTime) override;
        void start() override;


        P_GET_COMPONENT_TYPE(PComponentType::PMeshComponent)
        SMeshProfile m_MeshProfile;

    private:
        assetDB::PAssetHandle<assetDB::PStaticMeshAsset>* meshHandle;
        static unsigned int s_count; // All components must have this

    protected:
        std::vector<Vector3f> m_vertices = {
                Vector3f(-.5f, -.5f, 0.f),
                Vector3f(-.5f, .5f, 0.f),
                Vector3f(.5f, .5f, 0.f),
                Vector3f(.5f, -.5f, 0.f),
                Vector3f(-.5f, -.5f, 1.f),
                Vector3f(-.5f, .5f, 1.f),
                Vector3f(.5f, .5f, 1.f),
                Vector3f(.5f, -.5f, 1.f)
                };
        std::vector<unsigned int> m_indices = {
                0, 1, 2, // Forward triangles
                2, 3, 0,
                3, 2, 6, // Right triangles
                6, 7, 3,
                7, 6, 5, // Back triangles
                5, 4, 7,
                4, 5, 1, // Left triangles
                1, 0, 4,
                1, 5, 6, // Top triangles
                5, 2, 1,
                4, 0, 3, // Bottom triangles
                3, 7, 4
        };
        friend class pnt::mesh::P3DGeometricMeshSS;

    };
}
