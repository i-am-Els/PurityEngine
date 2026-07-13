//
// Created by Eniola Olawale on 6/19/2024.
//

#pragma once

#include "component.h"
using namespace commons;

namespace purity::ecs{
    class PURITY_API PBehaviourScriptComponent : public PComponent, public std::enable_shared_from_this<PBehaviourScriptComponent>{
        explicit PBehaviourScriptComponent();

    public:
        ~PBehaviourScriptComponent() override { commons::PLog::echoMessage("Destroying Behaviour Script Component"); };

        void update(float deltaTime) override;

        void start() override;
        P_GET_COMPONENT_TYPE(PComponentType::PBehaviourScriptComponent)

    private:
        static unsigned int s_count; // All components must have this
    };
}
