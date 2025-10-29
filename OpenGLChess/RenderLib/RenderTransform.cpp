#include "pch.h"
#include "RenderTransform.h"

RenderTransform::RenderTransform()
{
	GetWindowRect(hDesktop, &desktop);

    proj = glm::ortho(0.0f, (float)desktop.right, 0.0f, (float)desktop.bottom, -1.0f, 1.0f);
    view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    translation = glm::vec3(600, 600, 0);
    model = glm::translate(glm::mat4(1.0f), translation);
    mvp = proj * view * model;
}
