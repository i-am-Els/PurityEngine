//
// Created by Eniola Olawale on 9/20/2024.
//

#include "quad_comp.h"

namespace user_script {
    QuadComp::~QuadComp() {

    }

    void QuadComp::update(float deltaTime) {
        PBehaviourScriptComponent::update(deltaTime);
    }

    void QuadComp::start() {
        PBehaviourScriptComponent::start();
        std::cout << getName() << std::endl;

        auto transform = GetComponent<PTransformComponent>();
        // PLog::echoValue(ecs::fetch_or_throw(transform)->m_right);
    }
} // user_script