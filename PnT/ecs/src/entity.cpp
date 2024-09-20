//
// Created by Eniola Olawale on 4/30/2024.
//

#include <sstream>
#include "entity.h"

namespace pnt::ecs{

//    unsigned int PEntity::s_count = 0;

    PEntity::PEntity() : PEntityBase() {

    }

    PEntity::PEntity(PUUID uuid) : PEntityBase(uuid) {

    }

    PEntity::PEntity(const std::string &name) : PEntityBase() {
        m_name = name;
    }

}

