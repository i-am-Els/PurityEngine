//
// Created by Eniola Olawale on 9/17/2024.
//

#include "id_comp.h"
#include "entity.h"

namespace purity::ecs{

    PIDComponent::PIDComponent(std::weak_ptr<PEntity> entity) : PComponent(entity) {
    }

    PIDComponent::PIDComponent(std::weak_ptr<PEntity> entity, PUUID id) : PComponent(entity) {
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
        auto locked = m_entity.lock();
        (locked)->m_id = id;
    }

    void PIDComponent::Serialize(cereal::JSONOutputArchive& ar) const
    {
    }

    void PIDComponent::Deserialize(cereal::JSONInputArchive& ar)
    {
    }
}

CEREAL_REGISTER_TYPE(purity::ecs::PIDComponent)
CEREAL_REGISTER_POLYMORPHIC_RELATION(purity::ecs::PComponent, purity::ecs::PIDComponent)