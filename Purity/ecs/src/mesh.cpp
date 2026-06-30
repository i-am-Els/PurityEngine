//
// Created by Eniola Olawale on 5/10/2024.
//

#include "mesh.h"

namespace purity::ecs{
    unsigned int PMeshComponent::s_count = 0;

    PMeshComponent::PMeshComponent(std::weak_ptr<PEntity> entity, SMeshProfile profile) : PComponent(entity) {
        m_MeshProfile = profile;
    }

    void PMeshComponent::update(float deltaTime) {
        PComponent::update(deltaTime);
    }

    void PMeshComponent::start() {
        PComponent::start();
    }

    void PMeshComponent::Serialize(cereal::JSONOutputArchive& ar) const
    {
    }

    void PMeshComponent::Deserialize(cereal::JSONInputArchive& ar)
    {
    }
}

CEREAL_REGISTER_TYPE(purity::ecs::PMeshComponent)
CEREAL_REGISTER_POLYMORPHIC_RELATION(purity::ecs::PComponent, purity::ecs::PMeshComponent)