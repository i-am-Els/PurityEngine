//
// Created by Eniola Olawale on 9/17/2024.
//

#include "id_comp.h"
#include "entity.h"

namespace pnt::ecs{

    PIDComponent::PIDComponent(PEntity *entity) : PComponent(entity) {
    }

    PIDComponent::PIDComponent(PEntity *entity, PUUID id) : PComponent(entity) {
        setID(id);
    }

    void PIDComponent::update(float deltaTime) {
        PComponent::update(deltaTime);
    }

    void PIDComponent::start() {
        PComponent::start();
    }

    void PIDComponent::setID(PUUID id) {
        m_entityInstanceID = id;
        dynamic_cast<PEntityBase*>(m_entity)->m_instanceID = id;
    }
}