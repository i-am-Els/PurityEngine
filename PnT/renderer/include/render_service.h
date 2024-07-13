//
// Created by emman on 7/12/2024.
//

#pragma once

#include "iservices.h"

namespace pnt{
    class IRenderService : public IService{
    public:
        virtual void SwapBuffers() = 0;
        virtual void setUpShader() =  0;

    };
}
