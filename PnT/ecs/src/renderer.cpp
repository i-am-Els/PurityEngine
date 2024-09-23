//
// Created by Eniola Olawale on 6/18/2024.
//

#include "renderer.h"
#include <functional>

namespace pnt::ecs{

    unsigned int PRenderComponent::s_count = 0;

    PRenderComponent::PRenderComponent(PEntity *entity, SRenderProfile profile) : PComponent(entity) {
        m_RenderProfile = profile;
    }

    void PRenderComponent::update(float deltaTime) {
        PComponent::update(deltaTime);
    }

    void PRenderComponent::start() {
        PComponent::start();
    }

}
