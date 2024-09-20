//
// Created by Eniola Olawale on 6/19/2024.
//

#include "scripting.h"

namespace pnt::ecs{
    unsigned int PBehaviourScriptComponent::s_count = 0;

    PBehaviourScriptComponent::PBehaviourScriptComponent(PEntity *entity) : PComponent(entity) {
    }

    void PBehaviourScriptComponent::update(float deltaTime) {
        PComponent::update(deltaTime);
    }

    void PBehaviourScriptComponent::start() {
        PComponent::start();
    }

}
