/*
 * @Author: ImGili
 * @Description: 
 */
#include"Shader.h"
#include<sstream>
#include<fstream>
#include<iostream>
#include <glm/gtc/type_ptr.hpp>
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::ifstream gShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();		
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();			
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    unsigned int geometry = 0;

    // shader Program
    RendererID = glCreateProgram();
    glAttachShader(RendererID, vertex);
    glAttachShader(RendererID, fragment);
    
    glLinkProgram(RendererID);
    checkCompileErrors(RendererID, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glDeleteShader(geometry);
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

Shader::~Shader()
{
    glDeleteProgram(RendererID);
}

void Shader::SetMat4(const std::string &name, const glm::mat4& value) const
{
    int flag = glGetUniformLocation(RendererID, name.c_str());
    if (flag != -1)
    {
        glUniformMatrix4fv(flag, 1, GL_FALSE, glm::value_ptr(value)); 
    }
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{ 
    int flag = glGetUniformLocation(RendererID, name.c_str());
    if (flag != -1)
    {
        glUniform3f(glGetUniformLocation(RendererID, name.c_str()), x, y, z); 
    }
    else
    {
        std::cout << "Set Uniform Error!" << std::endl;
    }
}
void Shader::setFloat(const std::string &name, float value) const
{   
    int flag = glGetUniformLocation(RendererID, name.c_str());
    if (flag != -1)
    {
        glUniform1f(glGetUniformLocation(RendererID, name.c_str()), value); 
    }
    else
    {
        std::cout << "Set Uniform Error!" << std::endl;
    }
}