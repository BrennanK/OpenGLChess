#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <wtypes.h>
class RenderTransform
{
private:
    glm::mat4 proj;
    glm::mat4 view;
    glm::vec3 translation;
    glm::mat4 model;
    glm::mat4 mvp;

    RECT desktop;
    HWND hDesktop = GetDesktopWindow();
public:
    RenderTransform();

    glm::mat4 returnMVP() { return mvp; }
};