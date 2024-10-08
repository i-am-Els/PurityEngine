//
// Created by Eniola Olawale on 1/8/2024.
//

#include "vertex_array.h"
#include "glad/glad.h"
#include "log.h"

namespace pnt::graphics{
    unsigned int VertexArray::vaoCount = 0;
    VertexArray::~VertexArray() {
        PLog::echoMessage("Destroying Vertex Array.");
    }

    void VertexArray::init()  {
        vaoID = vaoCount++;
        glGenVertexArrays(1, &vaoID);
        bindVAO();
        attribCount = 0;
    }


    void VertexArray::addAttribute(unsigned int index, int countPerVertex, int sizePerVertex, const void* stridePtr, bool transpose){
        if (transpose) {
            glVertexAttribPointer(index, countPerVertex, GL_FLOAT, GL_TRUE, sizePerVertex, stridePtr);
        }
        else{
            glVertexAttribPointer(index, countPerVertex, GL_FLOAT, GL_FALSE, sizePerVertex, stridePtr);
        }
        enableAttributes(index);
        attribCount++;
    }

    void VertexArray::bindVAO() const{
        glBindVertexArray(vaoID);
//        PLog::echoMessage("VAO Bound");
    }

    void VertexArray::unbindVAO(){
        glBindVertexArray(0);
    }

    void VertexArray::enableAttributes(unsigned int index) {
        glEnableVertexAttribArray(index);
    }

}