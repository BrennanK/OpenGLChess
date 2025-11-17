#include "pch.h"
#include "TextureObject.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
//#include "../OpenGLChess/res/textures/"
TextureObject::TextureObject()
{
   // texture= Texture("../OpenGLChess/res/textures/kh3_box_art.jpg");
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
    

    texture.Bind();
    so.Bind();
    so.SetUniform1i("u_Texture", 0);
    so.SetUniformMat4f("u_MVP", rt.returnMVP());
    
}

void TextureObject::updateTransform(glm::vec3 newTranslation)
{
    rt.UpdateTranslation(newTranslation);
    so.Bind();
    so.SetUniformMat4f("u_MVP", rt.returnMVP());
}

void TextureObject::updateTexture(std::string& filePath, unsigned int slot)
{
    texture.changeTexture(filePath,slot);
}
