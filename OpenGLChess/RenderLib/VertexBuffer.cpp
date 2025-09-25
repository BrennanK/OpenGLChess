#include "pch.h"
#include "VertexBuffer.h"
#include "Renderer.h"
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &m_RendererID); // Creates the buffer and assigns the value to a varaible, this number is used to reference an object as an ID
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); // binds the buffer to a target in this case an array of memory
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
   // std::cout << "Vertex Buffer deleted";
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); // binds the buffer to a target in this case an array of memory
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0); // binds the buffer to a target in this case an array of memory
}

void VertexBuffer::DeleteBuffer() const
{
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::ChangeData(const void* data, unsigned int size)
{
   // DeleteBuffer();
    //glGenBuffers(1, &m_RendererID); // Creates the buffer and assigns the value to a varaible, this number is used to reference an object as an ID
    //glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); // binds the buffer to a target in this case an array of memory
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
   // glBufferData(GL_ARRAY_BUFFER, size, data, GL_STREAM_DRAW);
    
}