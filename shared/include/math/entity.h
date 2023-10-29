//
// Created by Eniola Olawale on 9/18/2023.
//

#pragma once

#include "transform.h"
using namespace pnt;

namespace pnt::model{
    struct Entity
    {
        Entity();
        explicit Entity(const math::Vector2<float>& _position, float scaleF = 0.25f);
        Entity(const Entity &e, float scaleF);
        Entity& operator=(const Entity& other);
        ~Entity()= default;

        void setVertices(float scaleF=0.25f);

        void printEntity() const;

        void SetPosition(float x, float y, float scale);
        void SetPosition(const math::Vector2<float>& v, float scaleF = 0.25f);
        void SetOldPosition(const math::Vector2<float>& pos);


        math::Transform transform;
        float* vertices{};
        math::Vector2<float> oldPosition;
        float scaleFactor;

    };
}
