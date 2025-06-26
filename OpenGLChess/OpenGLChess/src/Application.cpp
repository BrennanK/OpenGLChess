#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#pragma region Docs
// Really Good Documentation Website for OpenGL
//https://docs.gl/
#pragma endregion

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;



    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit())
    {
        std::cout << "Error" << std::endl;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;



#pragma region ModernGL

    float positions[6] = {
        -0.5f,-0.5f,
        0.0f,0.5f,
        0.5f,-0.5f};

    unsigned int buffer;
    glGenBuffers(1, &buffer); // Creates the buffer and assigns the value to a varaible, this number is used to reference an object as an ID
    glBindBuffer(GL_ARRAY_BUFFER, buffer); // binds the buffer to a target in this case an array of memory
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float),positions,GL_STATIC_DRAW);
#pragma endregion
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //glBegin(GL_TRIANGLES);
        
        //glVertex2f(-0.5f,-0.5f);
        //glVertex2f(0.0f, 0.5f);
        //glVertex2f(0.5f, -0.5f);
        
        //glEnd();

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}