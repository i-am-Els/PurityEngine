//
// Created by emman on 7/8/2024.
//

#pragma once

#include "component.h"

namespace purity::ecs{
    class PURITY_API ISystemBase{
    public:
        virtual ~ISystemBase() = default;
    };

    template<typename ComponentType>
    class PURITY_API ISystem : public ISystemBase{
    public:
        virtual void init() = 0;

        virtual void start() = 0;
//
        virtual void process() = 0;
//
        virtual void render() = 0;
//
        virtual void update(float deltaTime) = 0;
//
        virtual void destroy() = 0;

        virtual std::weak_ptr<ComponentType> AddComponent(std::weak_ptr<PEntity> entity) = 0;
        virtual void RemoveComponent(std::weak_ptr<PEntity> entity, std::weak_ptr<ComponentType> component) = 0;

    };

}
