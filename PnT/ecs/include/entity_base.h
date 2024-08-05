//
// Created by Eniola Olawale on 8/8/2024.
//

#pragma once

#include <vector>
//#include "component.h"

namespace pnt::ecs{
    class ManipulativeBehaviour;

    class PEntityBase{
    public:
        explicit PEntityBase(unsigned int mInstanceId) : m_instanceID(mInstanceId) {}

        [[nodiscard]] inline unsigned int getInstanceId() const { return m_instanceID; };
    protected:
        unsigned int m_instanceID{};
        std::vector<PComponent*> m_components;

        friend class ManipulativeBehaviour;
    };
}
