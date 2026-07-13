//
// Created by Eniola Olawale on 3/23/2024.
//

#pragma once

#include "vector2.h"
#include "component.h"

using namespace isle_engine::math;

namespace purity::ecs{

    struct SCameraProfile{
        unsigned int width;
        unsigned int height;
        Vector2i position;
    };

    class PURITY_API PCameraComponent final : PComponent {
    public:
        PCameraComponent();
        PCameraComponent(unsigned int _width, unsigned int _height, int xPos, int yPos);
        PCameraComponent(const purity::ecs::SCameraProfile &prop);
        PCameraComponent(const PCameraComponent & _camera) = default;
        PCameraComponent(const PCameraComponent && _camera) = delete;
        PCameraComponent& operator=(const PCameraComponent & _camera) = default;
        PCameraComponent& operator=(const PCameraComponent && _camera) = delete;
        ~PCameraComponent() override { PLog::echoMessage("Destroying Camera");}
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
        P_GET_COMPONENT_TYPE(PComponentType::PCameraComponent)
    private:
        static unsigned int s_count; // All components must have this
        unsigned int width, height;
        Vector2i position;
    };
}