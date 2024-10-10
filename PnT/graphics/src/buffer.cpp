//
// Created by Eniola Olawale on 12/4/2023.
//

#include "buffer.h"

namespace pnt::graphics{
    unsigned int VertexBuffer::s_count = 0;

    VertexBuffer::~VertexBuffer() {
        PLog::echoMessage("Destroying Vertex Buffer.");
    }

    VertexBuffer::VertexBuffer(std::vector<Vector3f> &data, unsigned int vertexCount) : Buffer() {
        this->m_data = data;
        this->m_itemCount = vertexCount;
        m_bufferID = ++s_count;
        PLog::echoMessage("VertexBuffer Created");
    }

    void VertexBuffer::initBuffer() {
        glGenBuffers(1, &m_bufferID);
        bindBuffer();
        glBufferData(GL_ARRAY_BUFFER, (long long)(m_itemCount * sizeof(Vector3f)), m_data.data(), GL_DYNAMIC_DRAW);
//        glBufferData(GL_ARRAY_BUFFER, (long long)(m_itemCount * sizeof(Vector3f)), nullptr, GL_DYNAMIC_DRAW);
    }

    void VertexBuffer::updateBuffer() {
        bindBuffer();
        glBufferData(GL_ARRAY_BUFFER, (long long)(m_itemCount * sizeof(Vector3f)), m_data.data(), GL_DYNAMIC_DRAW);
    }

    void VertexBuffer::bindBuffer() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
    }

    void VertexBuffer::unbindBuffer() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    unsigned int ElementBuffer::s_count = 0;

    ElementBuffer::~ElementBuffer() {
        PLog::echoMessage("Destroying Element Buffer.");
    }

    ElementBuffer::ElementBuffer(std::vector<unsigned int> &data, unsigned int vertexCount) : Buffer() {
        this->m_data = data;
        this->m_itemCount = vertexCount;
        m_bufferID = ++s_count;
        PLog::echoMessage("ElementBuffer Created");
    }

    void ElementBuffer::initBuffer() {
        glGenBuffers(1, &m_bufferID);
        bindBuffer();
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (long long)(m_itemCount * sizeof(unsigned int)), nullptr, GL_DYNAMIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (long long)(m_itemCount * sizeof(unsigned int)), m_data.data(), GL_DYNAMIC_DRAW);
    }

    void ElementBuffer::updateBuffer() {
        bindBuffer();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (long long)(m_itemCount * sizeof(unsigned int)), m_data.data(), GL_DYNAMIC_DRAW);
    }

    void ElementBuffer::bindBuffer() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
    }

    void ElementBuffer::unbindBuffer() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}