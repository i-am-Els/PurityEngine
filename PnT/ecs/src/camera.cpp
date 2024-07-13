//
// Created by Eniola Olawale on 3/23/2024.
//

#include "camera.h"

namespace pnt::ecs
{
    PCameraComponent::PCameraComponent(PEntity *entity) : PComponent(entity) {

    }

    PCameraComponent::PCameraComponent(PEntity *entity, unsigned int _width, unsigned int _height, int xPos, int yPos)
            : PComponent(entity), width(_width), height(_height), position(Vector2i(xPos, yPos)) {

    }

    PCameraComponent::PCameraComponent(PEntity *entity, const pnt::ecs::CameraProperties &prop) : PComponent(entity),
                                                                                                  width(prop.width),
                                                                                                  height(prop.height),
                                                                                                  position(prop.position)
                                                                                                  {

    }
}



