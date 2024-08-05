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
    };
}
