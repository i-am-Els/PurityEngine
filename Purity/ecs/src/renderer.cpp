//
// Created by Eniola Olawale on 6/18/2024.
//

#include "renderer.h"
#include <functional>

namespace purity::ecs{

    unsigned int PRenderComponent::s_count = 0;

    PRenderComponent::PRenderComponent(std::weak_ptr<PEntity> entity, SRenderProfile profile) : PComponent(entity) {
        m_RenderProfile = profile;
    }

    void PRenderComponent::update(float deltaTime) {
        PComponent::update(deltaTime);
    }

    void PRenderComponent::start() {
        PComponent::start();
    }

    void PRenderComponent::Serialize(cereal::JSONOutputArchive& ar) const
    {
    }

    void PRenderComponent::Deserialize(cereal::JSONInputArchive& ar)
    {
    }
}

CEREAL_REGISTER_TYPE(purity::ecs::PRenderComponent)
CEREAL_REGISTER_POLYMORPHIC_RELATION(purity::ecs::PComponent, purity::ecs::PRenderComponent)