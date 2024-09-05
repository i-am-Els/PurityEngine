//
// Created by Eniola Olawale on 3/23/2024.
//

#include "camera.h"

namespace pnt::ecs
{
    unsigned int PCameraComponent::s_count = 0;

    PCameraComponent::PCameraComponent(PEntity *entity) : PComponent(entity) {
    m_id = ++s_count;
    }

    PCameraComponent::PCameraComponent(PEntity *entity, unsigned int _width, unsigned int _height, int xPos, int yPos)
            : PComponent(entity), width(_width), height(_height), position(Vector2i(xPos, yPos)) {

    }

    PCameraComponent::PCameraComponent(PEntity *entity, const pnt::ecs::SCameraProfile &prop) : PComponent(entity),
                                                                                                  width(prop.width),
                                                                                                  height(prop.height),
                                                                                                  position(prop.position)
                                                                                                  {

    }
}



