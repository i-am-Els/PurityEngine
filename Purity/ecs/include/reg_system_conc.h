//
// Created by Eniola Olawale on 9/17/2024.
//

#pragma once

#include "reg_system.h"

namespace purity::ecs{

    class PURITY_API PIDManager final : public IIDSystem {
    public:
        PIDManager() = default;
        PIDManager(const PIDManager& manager) = delete;
        PIDManager operator=(const PIDManager& manager) = delete;
        void init() override;
        void start() override;
        void process() override;
        void render() override;
        void update(float deltaTime) override;
        void destroy() override;
        ~PIDManager() override {
            PLog::echoMessage("Destroying ID Manager.");
        }
        PIDComponent *AddComponent(PEntity *entity) override;
        void RemoveComponent(PEntity *entity, PIDComponent *component) override;
    private:
        std::vector<std::unique_ptr<PIDComponent>> idComponents;
    };


    class PURITY_API PTagManager final : public ITagSystem {
    public:
        PTagManager() = default;
        PTagManager(const PTagManager& manager) = delete;
        PTagManager operator=(const PTagManager& manager) = delete;
        void init() override;
        void start() override;
        void process() override;
        void render() override;
        void update(float deltaTime) override;
        void destroy() override;
        ~PTagManager() override {
            PLog::echoMessage("Destroying Tag Manager.");
        }
        PTagComponent *AddComponent(PEntity *entity) override;
        void RemoveComponent(PEntity *entity, PTagComponent *component) override;
    private:
        std::vector<std::unique_ptr<PTagComponent>> tagComponents;
    };
}
