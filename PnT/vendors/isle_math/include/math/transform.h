//
// Created by Eniola Olawale on 9/18/2023.
//

#pragma once
#include "core.h"
#include "basis.h"
#include "quaternion.h"


    namespace isle_engine::math
    {
        /**
		 * @brief Represents a 3D transform component.
		 *
		 * This class represents the transform of a component in 3D space.
		 * It provides various coordinate space operations and utility functions for object transformation and coordination.
		 *
		 * @param T The data type of the vector m_components.
		 */
        class ISLE_API Transform : public Basis{
        public:
            Transform();
            Transform(const Vector3f& position, const Quaternion<float>& orientation, const Vector3f& scale);
            Transform(const Transform& t);
            ~Transform();

            Vector3<float> m_position;
            Quaternion<float> m_orientation;
            Vector3<float> m_scale;

            void resetTransform();
            void resetPosition();
            void resetRotation();
            void resetScale();

            void resetBasis() override;
        };
    }




