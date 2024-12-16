//
// Created by emman on 8/8/2024.
//

#pragma once
#include "transform_system.h"

using namespace purity::ecs;

namespace purity::ecs{
    class PURITY_API PTransformSS final : public ITransformSystem {
    public:
        PTransformSS() = default;
        PTransformSS(const PTransformSS& manager) = delete;
        PTransformSS operator=(const PTransformSS& manager) = delete;
        void init() override;

        void start() override;

        void process() override;

        void render() override;

        void update(float deltaTime) override;

        void destroy() override;

        ~PTransformSS() override {
            PLog::echoMessage("Destroying Transform System.");
        }

        PTransformComponent *AddComponent(PEntity *entity) override;

        void RemoveComponent(PEntity *entity, PTransformComponent *component) override;

    private:
        std::vector<std::unique_ptr<PTransformComponent>> transformComponents;


    };

}


