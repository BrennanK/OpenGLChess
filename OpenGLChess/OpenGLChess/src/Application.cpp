#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#pragma region Docs
// Really Good Documentation Website for OpenGL
//https://docs.gl/
#pragma endregion

#define ASSERT(x) if(!(x)) __debugbreak(); // macros to make glGetError Easier
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x, __FILE__,__LINE__))
static void GLClearError() // method to invoke and get all GL error flags
{
    while (glGetError() != GL_NO_ERROR)
    {

    }
}
static bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGl error] (" << error << ")" << function <<"in " <<file << "on line " << line << std::endl;
        return false;
    }
    return true;
}
struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);

    enum class Shadertype
    {
        NONE = -1, VERTEX=0, FRAGMENT=1
    };

    std::string line;
    std::stringstream ss[2];
    Shadertype type = Shadertype::NONE;
    while (getline(stream,line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = Shadertype::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = Shadertype::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }
    return {ss[0].str(),ss[1].str()};
}

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
    
    float positions[] = {
        -0.5f,-0.5f, //0
        0.5f,-0.5f,  //1
        0.5f,0.5f,   //2
        -0.5f,0.5f}; //3

    unsigned int indices[] = // array of indices points such that we can draw multiple triangles without having to store duplicate positions
    {
        0,1,2,
        2,3,0
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer); // Creates the buffer and assigns the value to a varaible, this number is used to reference an object as an ID
    glBindBuffer(GL_ARRAY_BUFFER, buffer); // binds the buffer to a target in this case an array of memory
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float),positions,GL_STATIC_DRAW);
#pragma endregion Creates a section of data for our shape data and binds that data to a GPU buffer 

#pragma region Vertex_Attributes
    // You have to enable the array for Vertex sorting
    glEnableVertexAttribArray(0);

    // the last attribute had no offset since all data is evened out vertices if an offset is needed we use a cast like (const void*)8
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); 
#pragma endregion Specifies a sorting structure for the data being passed in

#pragma region Index_Buffer
    unsigned int ibo;
    glGenBuffers(1, &ibo); // Creates the buffer and assigns the value to a varaible, this number is used to reference an object as an ID
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // binds the buffer to a target in this case an array of memory
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
#pragma endregion Used to indicate Triangles without duplicating vertices


#pragma region Shader

    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
   // std::cout << "Vertex Source: " << std::endl;
   // std::cout << source.VertexSource << std::endl;
   // std::cout << "Fragment Source: " << std::endl;
    //std::cout <<source.FragmentSource<< std::endl;
    unsigned int shader = CreateShader(source.VertexSource,source.FragmentSource);
    glUseProgram(shader);

    // Start of Uniforms section
    GLCall(int location = glGetUniformLocation(shader, "u_Color"));
    ASSERT(location != -1);
    GLCall(glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f));
#pragma endregion Responsible for Passing programs to the GPU for utilizing GPU resources

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    float r = 0.0f;
    float increment = 0.05f;

#pragma endregion
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));

        if (r > 1.0f)
        {
            increment = -0.05f;
        }
        else if (r<0.0f)
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

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}