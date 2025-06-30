#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#pragma region Docs
// Really Good Documentation Website for OpenGL
//https://docs.gl/
#pragma endregion

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //TODO: Error Handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id,length,&length,message);
        std::cout << "Failed to compile"<<(type==GL_VERTEX_SHADER ? "Vertex":"Fragement") << "shader: ";
        std::cout << message<<std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

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

#pragma region Vertex_Buffer
    
    float positions[6] = {
        -0.5f,-0.5f,
        0.0f,0.5f,
        0.5f,-0.5f};

    unsigned int buffer;
    glGenBuffers(1, &buffer); // Creates the buffer and assigns the value to a varaible, this number is used to reference an object as an ID
    glBindBuffer(GL_ARRAY_BUFFER, buffer); // binds the buffer to a target in this case an array of memory
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float),positions,GL_STATIC_DRAW);

#pragma region Vertex_Attributes
    // You have to enable the array for Vertex sorting
    glEnableVertexAttribArray(0);

    // the last attribute had no offset since all data is evened out vertices if an offset is needed we use a cast like (const void*)8
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); 
#pragma endregion 

#pragma region Shader

    std::string vertexShader = 
        "#version 330 core\n"
        "\n"
        "layout(location=0) in vec2 position;"
        "\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(position.xy,0.0,1.0);\n"
        "}\n";
    std::string fragmentShader =
        "#version 330 core\n"
        "\n"
        "layout(location=0) out vec4 color;"
        "\n"
        "void main()\n"
        "{\n"
        "color=vec4(1.0,0.0,0.0,1.0);\n"
        "}\n";
    unsigned int shader = CreateShader(vertexShader,fragmentShader);
    glUseProgram(shader);
#pragma endregion 

    glBindBuffer(GL_ARRAY_BUFFER, 0);
#pragma endregion


#pragma endregion
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);// This alone has the potential to display a drawing if the driver has a default shader built in

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}