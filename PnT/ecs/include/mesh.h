//
// Created by Eniola Olawale on 5/8/2024.
//

#pragma once

#include <vector>

#include "component.h"
#include "buffer.h"

using namespace pnt::graphics;

namespace pnt::ecs{
    class PMeshComponent : public PComponent{
    public:
        explicit PMeshComponent(PEntity *entity);
        ~PMeshComponent() override { PLog::echoMessage("Destroying mesh"); }

        void update(float deltaTime) override;
        void start() override;

        void initBuffers();

#ifdef HACK_
    inline VertexBuffer* getVBO() { return &m_vertexBuffer; }
    inline ElementBuffer* getEBO() { return &m_elementBuffer; }
#endif //HACK_

    private:
        std::vector<Vector3f> m_vertices = {
                Vector3f(-.5f, -.5f, 0.f),
                Vector3f(-.5f, .5f, 0.f),
                Vector3f(.5f, .5f, 0.f),
                Vector3f(.5f, -.5f, 0.f)
                };
        std::vector<unsigned int> m_indices = {
                0, 1, 2,
                2, 3, 0
        };
        ElementBuffer m_elementBuffer;
        VertexBuffer m_vertexBuffer;
//        VertexBuffer m_colorBuffer;


    };
}
