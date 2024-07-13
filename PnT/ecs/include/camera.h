//
// Created by Eniola Olawale on 3/23/2024.
//

#pragma once

#include "vector2.h"
#include "component.h"

using namespace isle_engine::math;

namespace pnt::ecs{

    struct CameraProperties{
        unsigned int width;
        unsigned int height;
        Vector2i position;
    };

    class PCameraComponent : PComponent {
    public:
        explicit PCameraComponent(PEntity *entity);
        PCameraComponent(PEntity *entity, unsigned int _width, unsigned int _height, int xPos, int yPos);
        PCameraComponent(PEntity *entity, const pnt::ecs::CameraProperties &prop);
        PCameraComponent(const PCameraComponent & _camera) = default;
        PCameraComponent(const PCameraComponent && _camera) = delete;
        PCameraComponent& operator=(const PCameraComponent & _camera) = default;
        PCameraComponent& operator=(const PCameraComponent && _camera) = delete;
        ~PCameraComponent() override { PLog::echoMessage("Destroying Camera");};
    private:
        unsigned int width, height;
        Vector2i position;
    };
}