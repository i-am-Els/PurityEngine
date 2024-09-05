//
// Created by Eniola Olawale on 9/18/2023.
//


#include "basis.h"


namespace isle_engine::math
{

    Basis::Basis() {
        m_right = Vector3f(1.0f, 0.0f, 0.0f);
        m_up = Vector3f(0.0f, 1.0f, 0.0f);
        m_forward = Vector3f(0.0f, 0.0f, 1.0f);
    }

    void Basis::resetBasis() {

    }

}
