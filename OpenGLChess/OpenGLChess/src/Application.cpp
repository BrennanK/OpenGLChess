#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640*2, 720, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(4);

    if (glewInit())
    {
        std::cout << "Error" << std::endl;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;



#pragma region ModernGL

#pragma region Vertex_Buffer
    {
        float positions[] = {
            120.5f,120.5f, 0.0f,0.0f,//0
            240.5f,120.5f, 1.0f, 0.0f, //1
            240.5f,240.5f,  1.0f,1.0f, //2
            120.5f,240.5f, 0.0f,1.0f}; //3

        unsigned int indices[] = // array of indices points such that we can draw multiple triangles without having to store duplicate positions
        {
            0,1,2,
            2,3,0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        unsigned int vao;
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);



#pragma endregion Creates a section of data for our shape data and binds that data to a GPU buffer 

#pragma region Vertex_Attributes
        // You have to enable the array for Vertex sorting
        //GLCall(glEnableVertexAttribArray(0));

        // the last attribute had no offset since all data is evened out vertices if an offset is needed we use a cast like (const void*)8
        //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); // this line is what binds buffer to the vertex array object vao
#pragma endregion Specifies a sorting structure for the data being passed in

#pragma region Index_Buffer

        IndexBuffer ib(indices, 6);
#pragma endregion Used to indicate Triangles without duplicating vertices

#pragma region Projection_Matrix
        glm::mat4 proj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
        glm::mat4 view=glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

        glm::mat4 mvp = proj * view* model;
#pragma endregion

#pragma region Shader

        Shader so("res/shaders/Basic.shader");
        so.Bind();// We must bind before setting the uniform
        so.SetUniform4f("u_Color",0.8f, 0.3f, 0.8f, 1.0f);
        so.SetUniformMat4f("u_MVP", mvp);
       
#pragma endregion Responsible for Passing programs to the GPU for utilizing GPU resources
      
#pragma region Texture
        Texture texture("res/textures/kh3_box_art.jpg");
        texture.Bind();
        so.Bind();
        so.SetUniform1i("u_Texture", 0);
#pragma endregion
        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        so.Unbind();

        Renderer renderer;

        float r = 0.0f;
        float increment = 0.05f;

#pragma endregion

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            //so.Bind();
            //va.Bind();
            //ib.Bind();

            renderer.Draw(va, ib, so);

           GLCall(so.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f));

            if (r > 1.0f)
            {
                increment = -0.05f;
            }
            else if (r < 0.0f)
            {
                increment = 0.05f;
            }
            r += increment;
            GLClearError();
           // GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)); // We use nullptr since the indices is bound to GL_ELEMENT_ARRAY_BUFFER
            // above should be GL_UNSIGNED_INT

            //glDrawArrays(GL_TRIANGLES, 0, 6);// This alone has the potential to display a drawing if the driver has a default shader built in

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        //glDeleteProgram(shader);
    }
    glfwTerminate();
    return 0;
}