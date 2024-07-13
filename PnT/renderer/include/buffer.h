//
// Created by Eniola Olawale on 6/30/2024.
//

#pragma once

#include <vector>
#include "islemath.h"
#include "glew.h"
#include "log.h"

using namespace isle_engine::math;

namespace pnt::graphics{
    enum class BufferType{
        ElementBuffer, VertexBuffer
    };

    class Buffer{
    public:

        virtual void initBuffer() = 0;
        virtual void bindBuffer() const = 0;
        virtual void unbindBuffer() const = 0;


        Buffer(){
            PLog::echoMessage("Buffer Created");
        }

        inline void destroyBuffer() {
            glDeleteBuffers(1, &m_bufferID);
        }

        inline static void destroyBuffer(unsigned int ID) {
            glDeleteBuffers(1, &ID);
        }

        [[nodiscard]] inline unsigned int getBufferID() const {
            return m_bufferID;
        }

    protected:
        unsigned int m_bufferID{};
        unsigned int m_itemCount{};

    };

    class VertexBuffer : public Buffer {
    public:
        VertexBuffer() = default;
        VertexBuffer(std::vector<Vector3f> &data, unsigned int vertexCount);
        ~VertexBuffer();
        void initBuffer() override;
        void bindBuffer() const override;
        void unbindBuffer() const override;

        inline std::vector<Vector3f> getBufferData() {
            return m_data;
        }

        [[nodiscard]] inline unsigned int getItemCount() const {
            return m_data.size();
        }

    private:
        std::vector<Vector3f> m_data;
        static unsigned int s_count;
    };

    class ElementBuffer : public Buffer {
    public:
        ElementBuffer() = default;
        ElementBuffer(std::vector<unsigned int> &data, unsigned int vertexCount);
        ~ElementBuffer();
        void initBuffer() override;
        void bindBuffer() const override;
        void unbindBuffer() const override;

        inline std::vector<unsigned int > getBufferData() {
            return m_data;
        }

        [[nodiscard]] inline unsigned int getItemCount() const {
            return m_data.size();
        }
    private:
        std::vector<unsigned int > m_data;
        static unsigned int s_count;

    };
}
