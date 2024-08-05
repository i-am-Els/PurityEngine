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

namespace pnt::mesh{
    class P3DGeometricMeshSS : public IMeshSystem{
    public:
        P3DGeometricMeshSS();

        void init() override;

        void process() override;

        void render() override;

        void update(float deltaTime) override;

        void destroy() override;

        void start() override;

        ~P3DGeometricMeshSS() override = default;

        PMeshComponent *AddComponent(PEntity *entity) override;

        PMeshComponent *GetComponent(unsigned int id) override;

        void RemoveComponent(PEntity *entity, PMeshComponent *component) override;

        void RemoveComponentByTag(PEntity *entity, PMeshComponent *component, std::string tag) override;

        void RemoveComponentsByTag(PEntity *entity, std::string tag) override;

        PMeshComponent *FindComponentByTag(PEntity *entity, std::string tag) override;

        std::vector<PMeshComponent *> FindComponentsByTag(PEntity *entity, std::string tag) override;

    private:
        std::vector<std::unique_ptr<PMeshComponent>> meshComponents;

    };
}

