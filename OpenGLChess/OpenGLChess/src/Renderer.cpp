#include "Renderer.h"
#include <iostream>

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

