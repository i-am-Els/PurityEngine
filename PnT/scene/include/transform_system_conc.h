//
// Created by emman on 8/8/2024.
//

#pragma once
#include "transform_system.h"

using namespace pnt::ecs;

namespace pnt::scene{
    class PTransformSS final : public ITransformSystem {
    public:
        void init() override;

        void start() override;

        void process() override;

        void render() override;

        void update(float deltaTime) override;

        void destroy() override;

        ~PTransformSS() override = default;

        PTransformComponent *AddComponent(PEntity *entity) override;

        void RemoveComponent(PEntity *entity, PTransformComponent *component) override;

    private:
        std::vector<std::unique_ptr<PTransformComponent>> transformComponents;


    };

}


