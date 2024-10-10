//
// Created by emman on 7/14/2024.
//

#pragma once

#include "islemath.h"
#include "mesh_system.h"
#include "service_base.h"
#include "isystems.h"
#include "mesh.h"

using namespace pnt::ecs;

namespace pnt::ecs{
    class PNT_API P3DGeometricMeshSS final : public IMeshSystem{
    public:
        P3DGeometricMeshSS();

        P3DGeometricMeshSS(const P3DGeometricMeshSS& manager) = delete;
        P3DGeometricMeshSS operator=(const P3DGeometricMeshSS& manager) = delete;

        void init() override;

        void process() override;

        void render() override;

        void update(float deltaTime) override;

        void destroy() override;

        void start() override;

        ~P3DGeometricMeshSS() override {
            PLog::echoMessage("Destroying 3D Geometric Mesh System.");
        }

        PMeshComponent *AddComponent(PEntity *entity) override;

        void RemoveComponent(PEntity *entity, PMeshComponent *component) override;

//        void LoadAllMeshAssets();
//
//        assetDB::PAssetHandle<assetDB::PStaticMeshAsset>* getAssetFromDataAssetBase();

    private:
        std::vector<std::unique_ptr<PMeshComponent>> meshComponents;
        ElementBuffer EBO;
        VertexBuffer VBO;

        void SendBuffersToRenderSystem();
    };
}

