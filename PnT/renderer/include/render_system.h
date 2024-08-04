//
// Created by emman on 7/12/2024.
//

#pragma once

#include "isystems.h"

namespace pnt::ecs{
    class IRenderSystem : public ISystem{
        public:
            virtual void SwapBuffers() = 0;
            virtual void setUpShader() =  0;

            virtual PRenderComponent* AddRenderable() = 0;
            virtual PRenderComponent* GetRenderable() = 0;
            virtual void RemoveRenderable(PRenderComponent* component) = 0;

    };
}
