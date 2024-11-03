//
// Created by Eniola Olawale on 9/18/2023.
//


#include "basis.h"


namespace isle_engine::math
{

    Basis::Basis() {
        m_right = Vector3f::right;
        m_up = Vector3f::up;
        m_forward = Vector3f::forward;
    }

    void Basis::resetBasis() {

    }
}
