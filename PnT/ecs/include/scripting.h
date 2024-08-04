//
// Created by Eniola Olawale on 6/19/2024.
//

#pragma once

#include "component.h"

namespace pnt::ecs{
    class PBehaviourScriptComponent : public PComponent{
        explicit PBehaviourScriptComponent(PEntity *entity);

    public:
        ~PBehaviourScriptComponent() override { PLog::echoMessage("Destroying Behaviour Script Component"); };

        void update(float deltaTime) override;

        void start() override;

        template<typename T>
        T* GetComponent();

        template<typename T>
        T* AddComponent();
    private:
        static unsigned int s_count; // All components must have this
    };
}
