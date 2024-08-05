//
// Created by Eniola Olawale on 4/30/2024.
//

#include <sstream>
#include "entity.h"

namespace pnt::ecs{

    unsigned int PEntity::s_count = 0;

    PEntity::PEntity() : PEntityBase(++s_count), m_tags(ETags::Default) {
        std::stringstream ss;
        ss << m_instanceID;
        m_name = "PEntity" + ss.str() ;
        PLog::echoMessage(m_name.c_str());
        initTransform();
        // sets m_transform
    }

    void PEntity::initTransform() {
        m_transform = AddComponent<PTransformComponent>();
    }

    PEntity::PEntity(const char* name) : PEntityBase(++s_count), m_name(name), m_tags(ETags::Default) {
        initTransform(); // sets m_transform
    }
}

