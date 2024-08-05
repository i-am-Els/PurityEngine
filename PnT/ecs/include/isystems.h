//
// Created by emman on 7/8/2024.
//

#pragma once

#include "component.h"

namespace pnt::ecs{

    class ISystem{
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

        virtual ~ISystem() = default;

        virtual PComponent* AddComponent(PEntity* entity) = 0;
        virtual PComponent* GetComponent(unsigned int id) = 0;
        virtual void RemoveComponent(PEntity* entity, PComponent* component) = 0;
        virtual void RemoveComponents(PEntity* entity, PComponent* component) = 0;
        virtual void RemoveComponentByTag(PEntity* entity, PComponent* component, std::string tag) = 0;
        virtual void RemoveComponentsByTag(PEntity* entity, std::string tag) = 0;
        virtual PComponent* FindComponentByTag(PEntity* entity, std::string tag) = 0;
        virtual std::vector<PComponent*> FindComponentsByTag(PEntity* entity, std::string tag) = 0;

    };

}
