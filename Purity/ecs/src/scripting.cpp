//
// Created by Eniola Olawale on 6/19/2024.
//

#include "scripting.h"

namespace purity::ecs{
    unsigned int PBehaviourScriptComponent::s_count = 0;

    PBehaviourScriptComponent::PBehaviourScriptComponent(std::weak_ptr<PEntity> entity) : PComponent(entity) {
    }

    void PBehaviourScriptComponent::update(float deltaTime) {
        PComponent::update(deltaTime);
    }

    void PBehaviourScriptComponent::start() {
        PComponent::start();
    }

}
