#include "pch.h"
#include "TextureObject2.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
//#include "../OpenGLChess/res/textures/"
TextureObject2::TextureObject2()
{
    // texture= Texture("../OpenGLChess/res/textures/kh3_box_art.jpg");
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);


    texture.Bind(1);
    so.Bind();
    so.SetUniform1i("u_Texture", 1);
    so.SetUniformMat4f("u_MVP", rt.returnMVP());

}

void TextureObject2::updateTransform(glm::vec3 newTranslation)
{
    rt.UpdateTranslation(newTranslation);
    so.Bind();
    so.SetUniformMat4f("u_MVP", rt.returnMVP());
}

void TextureObject2::updateTexture(std::string& filePath, unsigned int slot)
{
    texture.changeTexture(filePath, slot);
}