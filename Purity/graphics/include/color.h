//
// Created by Eniola Olawale on 5/8/2024.
//

#pragma once
#include "iserializable.h"

namespace purity::graphics{
    struct PURITY_API Color{
        float r, g, b, a;

        Color();
        Color(float red, float green, float blue);
        Color(float red, float green, float blue, float alpha);
    };
}
