//
// Created by AWA on 30/10/2023.
//
#pragma once
#include "core.h"

namespace isle_engine::math
{
    class ISLE_API IMatrix
    {
    public:
        virtual void get_openGlInterface()=0;
    };
}