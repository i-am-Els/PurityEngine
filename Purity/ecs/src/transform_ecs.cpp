//
// Created by Eniola Olawale on 5/10/2024.


#include "transform_ecs.h"

#include <utility>

namespace purity::ecs{
    unsigned int PTransformComponent::s_count = 0;

    PTransformComponent::PTransformComponent(PEntity *entity, STransformProfile profile) : PComponent(entity) ,
                                                                                           m_TransformProfile(std::move(profile)){
    }

    void PTransformComponent::Translate(const Vector3f& delta, bool isWorld) {

    }

    void PTransformComponent::Rotate(const Vector3f& euler, bool isWorld) {

    }

    Matrix4f PTransformComponent::getModelTransformMatrix() const {
        return m_localToWorldTransformMatrix;
    }

    Matrix4f PTransformComponent::getLocalTransformMatrix() const {
        return m_worldToLocalTransformMatrix;
    }

    void PTransformComponent::update(float deltaTime) {
        PComponent::update(deltaTime);
    }

    void PTransformComponent::start() {
        PComponent::start();
    }

    void PTransformComponent::Scale(const Vector3f &vector) {
        Matrix4f scaleMat = Matrix4f::identity();
    }

}
