#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include "Renderer.h"
class Shader
{
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    std::unordered_map<std::string, int> m_UniformLocationCache;
    // caching for uniform
public: 
	Shader(const std::string& filepath);
	~Shader();


	void Bind() const;
	void Unbind() const;

    void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);


private:
    unsigned int GetUniformLocation(const std::string& name);
    
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
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };

        std::string line;
        std::stringstream ss[2];
        Shadertype type = Shadertype::NONE;
        while (getline(stream, line))
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
        return { ss[0].str(),ss[1].str() };
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
            glGetShaderInfoLog(id, length, &length, message);
            std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragement") << "shader: ";
            std::cout << message << std::endl;

            glDeleteShader(id);
            return 0;
        }

        return id;
    }
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        unsigned int program = glCreateProgram();
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }
};

