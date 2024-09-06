//
// Created by Eniola Olawale on 5/10/2024.
//

#pragma once

#include "component.h"
#include "islemath.h"

using namespace isle_engine::math;

namespace pnt::ecs{

    struct STransformProfile{
        Vector3f Position;
        Vector3f Rotation;
        Vector3f Scale;
//        Transform Parent;
    };

    class PTransformComponent : public PComponent {
    public:
        explicit PTransformComponent(PEntity *entity, STransformProfile profile);

        ~PTransformComponent() override { PLog::echoMessage("Destroying transform"); };

        /// @brief World Transform.Translate method that moves the object relative to the world space
        /// @param delta - Vector3f that represents the change in position on all axes.
        void Translate(const Vector3f& delta, bool isWorld=true);

        /// @brief World Transform.Rotate that rotates the object relative to the world space
        /// @param euler - Vector3f that represents the theta in angles on all axes.
        void Rotate(const Vector3f& euler, bool isWorld=true);

        /// @brief A read only getter for the model matrix representing the transform
        /// @return Matrix4f - the m_localToWorldTransform matrix.
        /// @details The return matrix is the transforms local to world space transformation matrix
        Matrix4f getModelTransformMatrix();

        /// @brief The return matrix is the transforms world to local space transformation matrix
        Matrix4f getLocalTransformMatrix();

    public:
        /// @brief Position - world position of the transform
        /// @details Vector3f - defaults to a Zero Vector.
        Vector3f m_position = Vector3f::zero;

        /// @brief Rotation - represents the rotation of the transform in world space
        /// @details Quaternion<float> - defaults to an identity quaternion.
        Quaternion<float> m_rotation = Quaternion<float>::s_createIdentity();

        /// @brief Local Position - local position relative to the transform's parent
        /// @details Vector3f - defaults to a Zero Vector.
        Vector3f m_localPosition = Vector3f::zero;

        /// @brief Local Rotation - represents the local rotation of the transform relative to its parent
        /// @details Quaternion<float> - defaults to an identity quaternion.
        Quaternion<float> m_localRotation = Quaternion<float>::s_createIdentity();

        /// @brief Scale - scale factor of the transform in local scale
        /// @details Vector3f - defaults to a Vector::one i.e. (1.0f, 1.0f, 1.0f).
        Vector3f m_scale = Vector3f::one;

        /// @brief Right Vector - The +X axis of the transform
        Vector3f m_right = Vector3f::right;
        /// @brief Up Vector - The +Y axis of the transform
        Vector3f m_up = Vector3f::up;
        /// @brief Forward Vector - The +Z axis of the transform
        Vector3f m_forward = Vector3f::forward;

        /// @brief The Parent transform of the entity that this component is attached to
        PTransformComponent* m_parent;

        STransformProfile m_TransformProfile;

        void update(float deltaTime) override;
        void start() override;

        P_GET_COMPONENT_TYPE(PComponentType::PTransformComponent)

    private:
        static unsigned int s_count; // All components must have this

        MatrixNM<4, 4, float> m_worldToLocalTransform;
        MatrixNM<4, 4, float> m_localToWorldTransform; // Model Matrix
    };
}
