#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
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
            -0.5f,-0.5f, //0
            0.5f,-0.5f,  //1
            0.5f,0.5f,   //2
            -0.5f,0.5f }; //3

        unsigned int indices[] = // array of indices points such that we can draw multiple triangles without having to store duplicate positions
        {
            0,1,2,
            2,3,0
        };

        unsigned int vao;
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));
        VertexBufferLayout layout;
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


#pragma region Shader

        Shader so("res/shaders/Basic.shader");
        so.Bind();// We must bind before setting the uniform
        so.SetUniform4f("u_Color",0.8f, 0.3f, 0.8f, 1.0f);
       
#pragma endregion Responsible for Passing programs to the GPU for utilizing GPU resources
      
        
        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        so.Unbind();
        float r = 0.0f;
        float increment = 0.05f;

#pragma endregion

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            so.Bind();
            va.Bind();
            ib.Bind();

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
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)); // We use nullptr since the indices is bound to GL_ELEMENT_ARRAY_BUFFER
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