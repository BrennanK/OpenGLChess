#include "pch.h"
#include "Renderer.h"
#include <iostream>
#include "Shader.h"
void GLClearError() // method to invoke and get all GL error flags
{
    while (glGetError() != GL_NO_ERROR)
    {

    }
}
bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGl error] (" << error << ")" << function << "in " << file << "on line " << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(VertexArray& va, IndexBuffer& ib, Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

   GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
    //glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}
