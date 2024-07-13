//
// Created by Eniola Olawale on 6/18/2024.
//

#include "renderer.h"

namespace pnt::ecs{
    PRenderComponent::PRenderComponent(PEntity *entity) : PComponent(entity) {
    }

    void PRenderComponent::update(float deltaTime) {
        PComponent::update(deltaTime);
    }

    void PRenderComponent::start() {
        PComponent::start();
    }


};
