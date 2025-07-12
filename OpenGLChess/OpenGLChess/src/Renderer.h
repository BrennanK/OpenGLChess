#pragma once
#include <GL/glew.h>


#define ASSERT(x) if(!(x)) __debugbreak(); // macros to make glGetError Easier
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x, __FILE__,__LINE__))
void GLClearError(); // method to invoke and get all GL error flags
bool GLLogCall(const char* function, const char* file, int line);