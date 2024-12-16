//
// Created by Eniola Olawale on 5/10/2024.
//

#include "mesh.h"

namespace purity::ecs{
    unsigned int PMeshComponent::s_count = 0;

    PMeshComponent::PMeshComponent(PEntity *entity, SMeshProfile profile) : PComponent(entity) {
        m_MeshProfile = profile;
    }

    void PMeshComponent::update(float deltaTime) {
        PComponent::update(deltaTime);
    }

    void PMeshComponent::start() {
        PComponent::start();
    }

}
