//
// Created by emman on 8/5/2024.
//

#include "components_behavior.h"
#include "entity.h"
#include "scripting.h"

namespace pnt::ecs{

    PEntity *ManipulativeBehaviour::getEntity() {
        return dynamic_cast<PEntity*>(this);
    }

    PEntity *ManipulativeBehaviour::getEntityFromBehaviour() {
        return dynamic_cast<PBehaviourScriptComponent*>(this)->m_entity;
    }

    unsigned int ManipulativeBehaviour::getIDFromEntity(PEntity* entity) {
        return entity->getInstanceId();
    }

    PEntityBase *ManipulativeBehaviour::getEntityBase(PEntity *entity) const {
        return dynamic_cast<PEntityBase*>(entity);
    }
}