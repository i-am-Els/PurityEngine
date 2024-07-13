//
// Created by Eniola Olawale on 6/18/2024.
//

#pragma once

#include "component.h"

namespace pnt::ecs{
    class PRenderComponent : public PComponent{
    public:
        explicit PRenderComponent(PEntity *entity);
        ~PRenderComponent() override { PLog::echoMessage("Destroying renderComponent"); }

        void update(float deltaTime) override;
        void start() override;
    };
}
