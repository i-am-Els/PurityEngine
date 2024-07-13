//
// Created by Eniola Olawale on 12/4/2023.
//

#include "buffer.h"

namespace pnt::graphics{
    unsigned int VertexBuffer::s_count = 0;

    VertexBuffer::~VertexBuffer() = default;

    VertexBuffer::VertexBuffer(std::vector<Vector3f> &data, unsigned int vertexCount) : Buffer() {
        this->m_data = data;
        this->m_itemCount = vertexCount;
        m_bufferID = ++s_count;
        PLog::echoMessage("VertexBuffer Created");
    }

    void VertexBuffer::initBuffer() {
        glGenBuffers(1, &m_bufferID);
        bindBuffer();
        glBufferData(GL_ARRAY_BUFFER, (long long)(m_itemCount * 3 * sizeof(float)), m_data.data(), GL_STATIC_DRAW);
    }

    void VertexBuffer::bindBuffer() const { glBindBuffer(GL_ARRAY_BUFFER, m_bufferID); }

    void VertexBuffer::unbindBuffer() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    unsigned int ElementBuffer::s_count = 0;

    ElementBuffer::~ElementBuffer() = default;

    ElementBuffer::ElementBuffer(std::vector<unsigned int> &data, unsigned int vertexCount) : Buffer() {
        this->m_data = data;
        this->m_itemCount = vertexCount;
        m_bufferID = ++s_count;
        PLog::echoMessage("ElementBuffer Created");
    }

    void ElementBuffer::initBuffer() {
        glGenBuffers(1, &m_bufferID);
        bindBuffer();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (long long)(m_itemCount * sizeof(unsigned int)), m_data.data(), GL_STATIC_DRAW);
    }

    void ElementBuffer::bindBuffer() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID); }

    void ElementBuffer::unbindBuffer() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
}