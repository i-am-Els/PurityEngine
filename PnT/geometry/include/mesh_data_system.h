//
// Created by emman on 7/14/2024.
//

#pragma once

#include "islemath.h"
#include "mesh_service.h"
#include "service_base.h"
#include "isystems.h"
#include "mesh.h"


using namespace pnt::ecs;

namespace pnt::mesh{
    class P3DGeometricMeshSS : public PServiceBase<IMeshService>, public ISystem{
    public:
        void init() override;

        void process() override;

        void render() override;

        void update(float deltaTime) override;

        void destroy() override;

    private:


    };
}

