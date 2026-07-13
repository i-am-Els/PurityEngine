//
// Created by Eniola Olawale on 4/30/2024.
//

#include <sstream>
#include "entity.h"

namespace purity::ecs{

//    unsigned int PEntity::s_count = 0;

    PEntity::PEntity() : m_id(PUUID()) {

    }

    PEntity::PEntity(PUUID uuid) : m_id(uuid) {

    }

    void PEntity::Serialize(cereal::JSONOutputArchive& ar) const
    {
    }

    void PEntity::Deserialize(cereal::JSONInputArchive& ar)
    {
    }

    PEntity::PEntity(const std::string &name, PUUID uuid): m_id(uuid) {
        m_name = name;
    }

}

CEREAL_REGISTER_TYPE(purity::ecs::PEntity)