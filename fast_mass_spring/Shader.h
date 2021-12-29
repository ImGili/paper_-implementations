/*
 * @Author: ImGili
 * @Description: 
 */
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<string>
class Shader
{
public:
    Shader() = default;
    ~Shader();

    Shader(const char* vertexPath, const char* fragmentPath);
private:
    void checkCompileErrors(unsigned int shader, std::string type);
private:
    uint32_t RendererID;
};