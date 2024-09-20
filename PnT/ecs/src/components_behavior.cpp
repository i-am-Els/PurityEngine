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

    PUUID ManipulativeBehaviour::PImpl_ComponentBehaviour::getIDFromEntity(PEntity* entity){
        auto id = getEntityBase(entity)->getInstanceId();
        return id;
    }

    PEntityBase *ManipulativeBehaviour::PImpl_ComponentBehaviour::getEntityBase(PEntity *entity) const {
        return dynamic_cast<PEntityBase*>(entity);
    }

    PTransformComponent *ManipulativeBehaviour::PImpl_ComponentBehaviour::getTransform(PEntity *entity) const {
        return entity->m_transform;
    }
}