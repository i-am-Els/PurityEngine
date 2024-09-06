//
// Created by Eniola Olawale on 5/10/2024.


#include "transform_ecs.h"

#include <utility>

namespace pnt::ecs{
    unsigned int PTransformComponent::s_count = 0;

    PTransformComponent::PTransformComponent(PEntity *entity, STransformProfile profile) : PComponent(entity) ,
                                                                                           m_TransformProfile(std::move(profile)){
        m_id = ++s_count;
        m_parent = nullptr;
    }

    void PTransformComponent::Translate(const Vector3f& delta, bool isWorld) {

    }

    void PTransformComponent::Rotate(const Vector3f& euler, bool isWorld) {

    }

    Matrix4f PTransformComponent::getModelTransformMatrix() {
        return m_localToWorldTransform;
    }

    Matrix4f PTransformComponent::getLocalTransformMatrix() {
        return m_worldToLocalTransform;
    }

    void PTransformComponent::update(float deltaTime) {
        PComponent::update(deltaTime);
    }

    void PTransformComponent::start() {
        PComponent::start();
    }

}
