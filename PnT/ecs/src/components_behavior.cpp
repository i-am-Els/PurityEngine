//
// Created by emman on 8/5/2024.
//

#include "entity.h"
#include "scripting.h"
#include "components_behavior.h"

namespace pnt::ecs{

    PEntity *ManipulativeBehaviour::PImpl_ComponentBehaviour::getEntity(ManipulativeBehaviour* behaviourOwner) {
        return dynamic_cast<PEntity*>(behaviourOwner);
    }

    PEntity *ManipulativeBehaviour::PImpl_ComponentBehaviour::getEntityFromBehaviour(ManipulativeBehaviour* behaviourOwner) {
        return dynamic_cast<PBehaviourScriptComponent*>(behaviourOwner)->m_entity;
    }

    PEntityBase *ManipulativeBehaviour::PImpl_ComponentBehaviour::getEntityBase(PEntity *entity) const {
        return dynamic_cast<PEntityBase*>(entity);
    }
}