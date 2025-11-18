//
// Created by emman on 8/5/2024.
//

#include "entity.h"
#include "scripting.h"
#include "components_behavior.h"

namespace purity::ecs{

    std::weak_ptr<PEntity> ManipulativeBehaviour::PImpl_ComponentBehaviour::getEntity(ManipulativeBehaviour* behaviourOwner) {
        if (const auto entity = dynamic_cast<PEntity*>(behaviourOwner))
            return entity->getSharedPtr();
        return {};
    }

    std::weak_ptr<PEntity> ManipulativeBehaviour::PImpl_ComponentBehaviour::getEntityFromBehaviour(ManipulativeBehaviour* behaviourOwner) {
        if (const auto script = dynamic_cast<PBehaviourScriptComponent*>(behaviourOwner))
            return script->m_entity;
        return {};
    }

    PEntityBase *ManipulativeBehaviour::PImpl_ComponentBehaviour::getEntityBase(const std::weak_ptr<PEntity>& entity) const {
        if (const auto locked = entity.lock())
            return locked.get();
        return nullptr;
    }
}