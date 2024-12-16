//
// Created by Eniola Olawale on 4/30/2024.
//

#include "component.h"
#include "entity.h"

namespace purity::ecs {

    PComponent::PComponent(PEntity *entity) : m_entity(entity){
        m_id = PUUID();
    }

}
