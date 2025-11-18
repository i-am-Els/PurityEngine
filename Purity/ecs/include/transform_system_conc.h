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

        std::weak_ptr<PTransformComponent> AddComponent(std::weak_ptr<PEntity> entity) override;

        void RemoveComponent(std::weak_ptr<PEntity> entity, std::weak_ptr<PTransformComponent> component) override;

    private:
        std::vector<std::shared_ptr<PTransformComponent>> transformComponents;


    };

}


