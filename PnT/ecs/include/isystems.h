//
// Created by emman on 7/8/2024.
//

#pragma once

#include "component.h"

namespace pnt::ecs{
    class ISystemBase{
    public:
        virtual ~ISystemBase() = default;
    };

    template<typename ComponentType>
    class ISystem : public ISystemBase{
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

        virtual ComponentType* AddComponent(PEntity* entity) = 0;
        virtual ComponentType* GetComponent(unsigned int id) = 0;
        virtual void RemoveComponent(PEntity* entity, ComponentType* component) = 0;
        virtual void RemoveComponentByTag(PEntity* entity, ComponentType* component, std::string tag) = 0;
        virtual void RemoveComponentsByTag(PEntity* entity, std::string tag) = 0;
        virtual ComponentType* FindComponentByTag(PEntity* entity, std::string tag) = 0;
        virtual std::vector<ComponentType*> FindComponentsByTag(PEntity* entity, std::string tag) = 0;

    };

}
