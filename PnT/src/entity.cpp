//
// Created by Eniola Olawale on 9/18/2023.
//

#include "math/entity.h"
using namespace pnt;

namespace pnt::model
{
    Entity::Entity()
    {
        transform = math::Transform();
        setVertices();
        scaleFactor = 0.25f;
    }

    Entity::Entity(const Entity& e, float scaleF)
    {
        transform = e.transform;
        scaleFactor = e.scaleFactor;
        setVertices(scaleFactor);
    }

    Entity& Entity::operator=(const Entity& other)
    {
        if (this == &other) {
            return *this; // Self-assignment, no need to do anything
        }

        transform = other.transform;
        scaleFactor = other.scaleFactor;
        setVertices(scaleFactor);
        return *this;
    }

    Entity::Entity(const math::Vector2<float>& _position, float scaleF)
    {
        transform = math::Transform(_position);
        scaleFactor = scaleF;
        setVertices(scaleFactor);
    }

    void Entity::SetPosition(const math::Vector2<float>& v, float scaleF)
    {
        oldPosition = transform.position;
        transform.position = v;
        setVertices(scaleF);
    }

    void Entity::SetOldPosition(const math::Vector2<float>& pos)
    {
        oldPosition = pos;
    }

    void Entity::setVertices(float scaleF)
    {
        vertices = transform.GenQuadVertices(scaleF);
        scaleFactor = scaleF;
    }

    void Entity::printEntity() const
    {
        std::cout << transform.position.x << ", " << transform.position.y << std::endl;
        for (int i=0; i < 8;){
            std::cout << vertices[i++] << ", "<< vertices[i++] << std::endl;
        }
        std::cout << "\n";
    }

    void Entity::SetPosition(float x, float y, float scale = 0.25f)
    {
        oldPosition = transform.position;
        transform.position.x = x;
        transform.position.y = y;
        setVertices(scale);
    }
}
