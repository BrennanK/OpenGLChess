#include "pch.h"
#include "IndexBuffer.h"
#include "Renderer.h"
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count):m_Count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    glGenBuffers(1, &m_RendererID); // Creates the buffer and assigns the value to a varaible, this number is used to reference an object as an ID
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); // binds the buffer to a target in this case an array of memory
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); // binds the buffer to a target in this case an array of memory
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // binds the buffer to a target in this case an array of memory
}