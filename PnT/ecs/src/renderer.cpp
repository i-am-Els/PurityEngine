//
// Created by Eniola Olawale on 6/18/2024.
//

#include "renderer.h"
#include <functional>

namespace pnt::ecs{

    unsigned int PRenderComponent::s_count = 0;

    PRenderComponent::PRenderComponent(PEntity *entity) : PComponent(entity) {
        m_id = ++s_count;
    }

    void PRenderComponent::update(float deltaTime) {
        PComponent::update(deltaTime);
    }

    void PRenderComponent::start() {
        PComponent::start();
    }

}
