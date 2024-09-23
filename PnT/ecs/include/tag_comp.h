//
// Created by Eniola Olawale on 9/17/2024.
//

#pragma once

#include "component.h"
#include "tags.h"

namespace pnt::ecs{
    class PNT_API PTagComponent final : public PComponent{
    public:
        explicit PTagComponent(PEntity *entity);
        ~PTagComponent() override { PLog::echoMessage("Destroying Tag Component"); };

        void update(float deltaTime) override;

        void start() override;

        P_GET_COMPONENT_TYPE(PComponentType::PTagComponent)

        artifacts::ETags tag;
    };
}
