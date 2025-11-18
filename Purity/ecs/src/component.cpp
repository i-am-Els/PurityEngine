//
// Created by Eniola Olawale on 4/30/2024.
//

#include "component.h"
#include "entity.h"

namespace purity::ecs {

    PComponent::PComponent(std::weak_ptr<PEntity> entity) : ISerializable(), m_entity(entity){
    }

}
