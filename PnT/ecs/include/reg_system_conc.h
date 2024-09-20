//
// Created by Eniola Olawale on 9/17/2024.
//

#pragma once

#include "reg_system.h"

namespace pnt::ecs{

    class PIDManager final : public IIDSystem {
    public:
        void init() override;
        void start() override;
        void process() override;
        void render() override;
        void update(float deltaTime) override;
        void destroy() override;
        ~PIDManager() override = default;
        PIDComponent *AddComponent(PEntity *entity) override;
        void RemoveComponent(PEntity *entity, PIDComponent *component) override;
    private:
        std::vector<std::unique_ptr<PIDComponent>> idComponents;
    };


    class PTagManager final : public ITagSystem {
    public:
        void init() override;
        void start() override;
        void process() override;
        void render() override;
        void update(float deltaTime) override;
        void destroy() override;
        ~PTagManager() override = default;
        PTagComponent *AddComponent(PEntity *entity) override;
        void RemoveComponent(PEntity *entity, PTagComponent *component) override;
    private:
        std::vector<std::unique_ptr<PTagComponent>> tagComponents;
    };
}
