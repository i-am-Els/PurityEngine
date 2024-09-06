//
// Created by Eniola Olawale on 5/10/2024.
//

#include "mesh.h"

namespace pnt::ecs{
    unsigned int PMeshComponent::s_count = 0;

    PMeshComponent::PMeshComponent(PEntity *entity, SMeshProfile profile) : PComponent(entity),
                                                      m_vertexBuffer(m_vertices, m_vertices.size()),
                                                      m_elementBuffer(m_indices, m_indices.size()) {
        m_id = ++s_count;
        m_MeshProfile = profile;
        // Fetch your Vertex data and register to MeshRenderer Observer
        initBuffers();
    }

    void PMeshComponent::initBuffers() {
        m_vertexBuffer.initBuffer();
        m_elementBuffer.initBuffer();
    }

    void PMeshComponent::update(float deltaTime) {
        PComponent::update(deltaTime);
    }

    void PMeshComponent::start() {
        PComponent::start();
    }

}
