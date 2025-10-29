#include "pch.h"
#include "TextureObject.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
//#include "../OpenGLChess/res/textures/"
TextureObject::TextureObject()
{
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
    

    texture.Bind();
    so.Bind();
    so.SetUniform1i("u_Texture", 0);
    so.SetUniformMat4f("u_MVP", rt.returnMVP());
}
