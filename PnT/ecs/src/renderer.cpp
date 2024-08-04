//
// Created by Eniola Olawale on 6/18/2024.
//

#include "renderer.h"
#include <functional>

namespace pnt::ecs{

    PComponent::Traits::AddComponentCallback PRenderComponent::addComponentCallback = nullptr;
    PComponent::Traits::GetComponentCallback PRenderComponent::getComponentCallback = nullptr;
    PComponent::Traits::RemoveComponentCallback PRenderComponent::removeComponentCallback = nullptr;

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

    void PRenderComponent::SetAddComponentCallback(Traits::AddComponentCallback callback) {
        addComponentCallback = callback;
    }

    void PRenderComponent::SetGetComponentCallback(Traits::GetComponentCallback callback) {
        getComponentCallback = callback;
    }

    void PRenderComponent::SetRemoveComponentCallback(Traits::RemoveComponentCallback callback) {
        removeComponentCallback = callback;
    }

}
