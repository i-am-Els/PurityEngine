//
// Created by emman on 7/12/2024.
//

#pragma once

#include "isystems.h"

namespace pnt::ecs{
    class PNT_API IRenderSystem : public ISystem<PRenderComponent>{
        public:
            virtual void setUpShader() =  0;
    };
}
