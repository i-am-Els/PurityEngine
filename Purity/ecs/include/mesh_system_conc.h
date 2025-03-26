//
// Created by emman on 7/14/2024.
//

#pragma once

#include "mesh_system.h"
#include "mesh.h"

using namespace purity::ecs;

namespace purity::ecs{
    class PURITY_API P3DGeometricMeshSS final : public IMeshSystem{
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
    };
}

