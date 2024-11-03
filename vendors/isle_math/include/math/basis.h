//
// Created by Eniola Olawale on 9/18/2023.
//

#pragma once
#include "core.h"
#include "vector3.h"


namespace isle_engine::math
{
    /**
	 * @brief Represents a Basis Class for 3D object space.
	 *
	 * This class represents the Basis Vectors of a transform in 3D space.
	 * It provides various coordinate space operations and utility functions for object orientation.
	 *
	 * @param T The data type of the vector m_components.
	 */
    class ISLE_API Basis {
    public:
        Basis();

    protected:
        virtual void resetBasis();
        Vector3f m_right;
        Vector3f m_up;
        Vector3f m_forward;
    };
}



