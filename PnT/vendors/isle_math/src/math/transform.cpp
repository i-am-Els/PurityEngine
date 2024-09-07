//
// Created by Eniola Olawale on 9/18/2023.
//

#include "transform.h"

namespace isle_engine::math
{

    Transform::Transform() {
        m_position = Vector3f::zero;
        m_orientation = Quaternion<float>::s_createIdentity();
        m_scale = Vector3f::one;
    }

    Transform::Transform(const Vector3f &position, const Quaternion<float> &orientation, const Vector3f &scale) {
        m_position = position;
        m_orientation = orientation;
        m_scale = scale;
    }

    Transform::Transform(const Transform &t)  : Basis(t) {
        m_position = t.m_position;
        m_orientation = t.m_orientation;
        m_scale = t.m_scale;
    }

    void Transform::resetTransform() {
        m_position = Vector3f::zero;
        m_orientation = Quaternion<float>::s_createIdentity();
        m_scale = Vector3f::one;
        resetBasis();
    }

    void Transform::resetBasis() {
        m_right = Vector3f::right;
        m_up = Vector3f::up;
        m_forward = Vector3f::forward;
    }

    void Transform::resetPosition() {
        m_position = Vector3f::zero;
        // Call the translation function to move object to the origin
    }

    void Transform::resetRotation() {
        m_orientation = Quaternion<float>::s_createIdentity();
        // Call the rotation function to align object with new orientation
        // Rotate Basis to reflect the change in orientation
    }

    void Transform::resetScale() {
        m_scale = Vector3f::one;
        // Call the scale function
    }

    void Transform::setTransform(const Transform &t) {
        m_position = t.m_position;
        m_orientation = t.m_orientation;
        m_scale = t.m_scale;
    }

    Transform::~Transform() = default;

}
