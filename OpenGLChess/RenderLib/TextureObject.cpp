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

    glm::mat4 proj = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    glm::vec3 translationA = glm::vec3(600, 600, 0);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
    glm::mat4 mvp = proj * view * model;
    so.SetUniformMat4f("u_MVP", mvp);
}
