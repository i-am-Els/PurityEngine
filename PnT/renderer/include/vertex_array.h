//
// Created by Eniola Olawale on 1/8/2024.
//

#pragma once

namespace pnt::graphics{

    struct VertexArray {
        VertexArray() = default;
        ~VertexArray();
        void init();
        void bindVAO() const;
        void addAttribute(unsigned int index, int countPerVertex, int sizePerVertex, const void* stridePtr, bool transpose=false);
        static void enableAttributes(unsigned int index);
        static void unbindVAO();
    private:
        unsigned int vaoID;
        static unsigned int vaoCount;
        unsigned int attribCount;

    };
}

