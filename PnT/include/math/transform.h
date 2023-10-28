//
// Created by Eniola Olawale on 9/18/2023.
//

#pragma once
#include "vector2.h"

namespace pnt::math
{
    class Transform
    {
    public:
        Transform();

        explicit Transform(const Vector2<float> &_position);

        Vector2<float> position;

        [[nodiscard]] float *GenQuadVertices(float rad) const;

        void Translate(float *&vertices, float dX, float dY);

        static void Rotate(float *vertices, float angle);

        static void Scale(float *vertices, float sX, float sY);
    };
}