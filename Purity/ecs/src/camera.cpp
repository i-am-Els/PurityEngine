//
// Created by Eniola Olawale on 3/23/2024.
//

#include "camera.h"

namespace purity::ecs
{
    unsigned int PCameraComponent::s_count = 0;

    PCameraComponent::PCameraComponent() : PComponent() {
    }

    PCameraComponent::PCameraComponent(unsigned int _width, unsigned int _height, int xPos, int yPos)
            : PComponent(), width(_width), height(_height), position(Vector2i(xPos, yPos)) {

    }

    PCameraComponent::PCameraComponent(const purity::ecs::SCameraProfile &prop) : PComponent(),
                                                                                                  width(prop.width),
                                                                                                  height(prop.height),
                                                                                                  position(prop.position)
                                                                                                  {

    }

    void PCameraComponent::Serialize(cereal::JSONOutputArchive& ar) const
    {
    }

    void PCameraComponent::Deserialize(cereal::JSONInputArchive& ar)
    {
    }
}

CEREAL_REGISTER_TYPE(purity::ecs::PCameraComponent)
CEREAL_REGISTER_POLYMORPHIC_RELATION(purity::ecs::PComponent, purity::ecs::PCameraComponent)
