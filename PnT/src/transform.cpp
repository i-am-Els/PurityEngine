//
// Created by Eniola Olawale on 9/18/2023.
//

#include "math/transform.h"

namespace pnt::math
{
    Transform::Transform()
    {
        position = Vector2<float>();
    }

    Transform::Transform(const Vector2<float>& _position) : position (_position){}

    float* Transform::GenQuadVertices(float rad) const
    {
        return new float[8]{
                position.x - rad, position.y + rad,
                position.x + rad, position.y + rad,
                position.x - rad, position.y - rad,
                position.x + rad, position.y - rad
        };
    }

    void Transform::Translate(float*& vertices, float dX, float dY)
    {
        position.x += dX;
        position.y += dY;
        for (int i=0; i < 8; i++){
            if(i%2 == 0)
                vertices[i] += dX;
            else
                vertices[i] += dY;
        }
    }

    void Transform::Rotate(float* vertices, float angle)
    {
        float arr[8] = {
                vertices[0] * std::cos(angle) + vertices[1] * -1 * std::sin(angle),
                vertices[0] * std::sin(angle) + vertices[1] * std::cos(angle),
                vertices[2] * std::cos(angle) + vertices[3] * -1 * std::sin(angle),
                vertices[2] * std::sin(angle) + vertices[3] * std::cos(angle),
                vertices[4] * std::cos(angle) + vertices[5] * -1 * std::sin(angle),
                vertices[4] * std::sin(angle) + vertices[5] * std::cos(angle),
                vertices[6] * std::cos(angle) + vertices[7] * -1 * std::sin(angle),
                vertices[6] * std::sin(angle) + vertices[7] * std::cos(angle)
        };
        vertices[0] = arr[0];
        vertices[1] = arr[1];
        vertices[2] = arr[2];
        vertices[3] = arr[3];
        vertices[4] = arr[4];
        vertices[5] = arr[5];
        vertices[6] = arr[6];
        vertices[7] = arr[7];
    }

    void Transform::Scale(float* vertices, float sX, float sY)
    {
        for (int i=0; i < 8; i++){
            if(i%2 == 0)
                vertices[i] *= sX;
            else
                vertices[i] *= sY;
        }
    }
}
