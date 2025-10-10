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
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include "Tests/TestClearColor.h"
#include "Tests/TestScaleTexture.h"
#include "Tests/TextureTest.h"
#include "RenderLib.cpp"
#include <stb_image/stb_image.h>
#include <wtypes.h>
#pragma region Docs
// Really Good Documentation Website for OpenGL
//https://docs.gl/
#pragma endregion

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow* window;
int main(void)
{
    //GLFWwindow* window;
   

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    RECT desktop;
    HWND hDesktop=GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);

    window = glfwCreateWindow(desktop.right, desktop.bottom, "Chess", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    GLFWimage windowImage;
    windowImage.pixels = stbi_load("res/WindowIcon/Gold Pawn.png", &windowImage.width, &windowImage.height, 0, 4);
    glfwSetWindowIcon(window, 1, &windowImage);
    if (windowImage.pixels)
    {
        std::cout << "We have an icon image" << std::endl;
    }

    stbi_image_free(windowImage.pixels);

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
            -150.0f,-150.0f, 0.0f,0.0f,//0
            150.0f,-150.0f, 1.0f, 0.0f, //1
            150.0f,150.0f,  1.0f,1.0f, //2
            -150.0f,150.0f, 0.0f,1.0f}; //3


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
       // positions[8] = 150.0f; positions[9] = 150.0f;
       
        
        test::TestScaleTexture scaleTest(positions,16);
        VertexArray va2;
        VertexBuffer vb2(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout2;
        layout2.Push<float>(2);
        layout2.Push<float>(2);
        //scaleTest.OnUpdate(0.0f, vao, &va2, &vb2, layout2, positions, 16);
        va2.AddBuffer(vb2, layout2);
        //glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(float), nullptr, GL_STREAM_DRAW);
        //glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * 4 * sizeof(float), positions2);
        //scaleTest.OnUpdate(0.0f, vao, &va2, &vb2, layout2, positions, 16);

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
        glm::mat4 proj = glm::ortho(0.0f, (float)desktop.right, 0.0f, (float)desktop.bottom, -1.0f, 1.0f);
        glm::mat4 view=glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        glm::vec3 translationA = glm::vec3(200, 200, 0);
        glm::vec3 scaleTranslation = glm::vec3(0, 0, 0);
        
#pragma endregion

#pragma region Shader

        Shader so("res/shaders/Basic.shader");
        so.Bind();// We must bind before setting the uniform
        so.SetUniform4f("u_Color",0.8f, 0.3f, 0.8f, 1.0f);
        
       
#pragma endregion Responsible for Passing programs to the GPU for utilizing GPU resources
      
#pragma region Texture
        Texture texture("res/textures/kh3_box_art.jpg");
        texture.Bind();
        so.Bind();
        so.SetUniform1i("u_Texture", 0);
#pragma endregion
       // va.Unbind();
       // vb.Unbind();
        

        Renderer renderer;

       
#pragma region ImGui
        //initialization (after renderer )
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui::StyleColorsDark();
        ImGui_ImplOpenGL3_Init((char*)glGetString(330));

        // set up values
            bool show_demo_window = false;
        bool show_another_window = false;
       // ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

       
       


#pragma endregion

#pragma endregion

        test::TestClearColor test;
      //  test::TestScaleTexture scaleTest;
       // test::TextureTest texTest;
        
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();
          

            // Inside while befor edrraw
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

           
            
            //so.Bind();
            //va.Bind();
            //ib.Bind();
            so.Bind();
            
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
                glm::mat4 mvp = proj * view * model;
                so.SetUniformMat4f("u_MVP", mvp);
               // renderer.Draw(va2, ib, so);
                // test.OnUpdate(0.0f);
               
                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 25.0f)); // 10px horizontal, 5px vertical
                // Your widgets here

                ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

                test.onRenderer();
                test.OnImGuiRenderer();
               
                scaleTest.OnUpdate(0.0f, positions, 16);
              // scaleTest.onRenderer(renderer, va2, ib, so);
                scaleTest.OnImGuiRenderer();
                
                ImGui::SliderFloat3("Translation", &translationA.x, 0.0f, 1280.0f);
               // texTest.OnImGuiRenderer(texture);
                renderer.Draw(va2, ib, so);
                ImGui::PopStyleVar();
                
               // ImGui::ShowDemoWindow();

             // Begin a window with the ImGuiWindowFlags_AlwaysAutoResize flag
                ImGui::Begin("Auto-Resizing Window", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

                // Add content to the window
                ImGui::Text("This window automatically resizes to fit its content.");
                //ImGui::SliderFloat("Float Value", &myFloat, 0.0f, 1.0f);
                if (ImGui::Button("Click Me"))
                {
                    // Do something
                }

                // End the window
                ImGui::End();
           
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
           
            
            GLClearError();
           // GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)); // We use nullptr since the indices is bound to GL_ELEMENT_ARRAY_BUFFER
            // above should be GL_UNSIGNED_INT

            //glDrawArrays(GL_TRIANGLES, 0, 6);// This alone has the potential to display a drawing if the driver has a default shader built in

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
        // After while loop cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        //glDeleteProgram(shader);
    }
    glfwTerminate();
    return 0;
}