//
// Created by Eniola Olawale on 6/19/2024.
//

#pragma once

#include "component.h"
#include "components_behavior.h"

namespace pnt::ecs{
    class PBehaviourScriptComponent : public PComponent, ManipulativeBehaviour{
        explicit PBehaviourScriptComponent(PEntity *entity);

    public:
        ~PBehaviourScriptComponent() override { PLog::echoMessage("Destroying Behaviour Script Component"); };

        void update(float deltaTime) override;

        void start() override;
    private:
        static unsigned int s_count; // All components must have this
    };
}
