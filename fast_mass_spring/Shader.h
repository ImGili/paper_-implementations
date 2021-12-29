/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<string>
class Shader
{
public:
    Shader() = default;
    ~Shader();

    Shader(const char* vertexPath, const char* fragmentPath);
    void SetMat4(const std::string &name, const glm::mat4& value) const;
    operator GLuint() const{ return RendererID; } // cast to GLuint
private:
    void checkCompileErrors(unsigned int shader, std::string type);
private:
    uint32_t RendererID;
};