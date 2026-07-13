//
// Created by Eniola Olawale on 5/10/2024.
//

#include "renderer.h"

namespace purity::ecs{
    unsigned int PRendererComponent::s_count = 0;

	PRendererComponent::PRendererComponent() : PComponent() {
		m_RendererProfile = { true };
	}

    PRendererComponent::PRendererComponent(SRendererProfile profile) : PComponent() {
        m_RendererProfile = profile;
    }

    void PRendererComponent::update(float deltaTime) {
        PComponent::update(deltaTime);
    }

    void PRendererComponent::start() {
        PComponent::start();
    }

    void PRendererComponent::Serialize(cereal::JSONOutputArchive& ar) const
    {
    }

    void PRendererComponent::Deserialize(cereal::JSONInputArchive& ar)
    {
    }
}

CEREAL_REGISTER_TYPE(purity::ecs::PRendererComponent)
CEREAL_REGISTER_POLYMORPHIC_RELATION(purity::ecs::PComponent, purity::ecs::PRendererComponent)