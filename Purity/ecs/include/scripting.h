//
// Created by Eniola Olawale on 6/19/2024.
//

#pragma once

#include "component.h"
#include "components_behavior.h"

namespace purity::ecs{
    class PURITY_API PBehaviourScriptComponent : public PComponent, public ManipulativeBehaviour, public std::enable_shared_from_this<PBehaviourScriptComponent>{
        explicit PBehaviourScriptComponent(std::weak_ptr<PEntity> entity);

    public:
        ~PBehaviourScriptComponent() override { PLog::echoMessage("Destroying Behaviour Script Component"); };

        void update(float deltaTime) override;

        void start() override;
        P_GET_COMPONENT_TYPE(PComponentType::PBehaviourScriptComponent)

    private:
        static unsigned int s_count; // All components must have this
    };
}
