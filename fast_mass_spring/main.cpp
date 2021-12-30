/*
 * @Author: ImGili
 * @Description: 
 */
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/gtc/matrix_transform.hpp>
#include"Mesh.h"
#include"Shader.h"
#include"RenderAttach.h"
// settings
static uint32_t SCR_WIDTH = 800;
static uint32_t SCR_HEIGHT = 600;

static GLFWwindow* window;

Mesh* mesh;
static ProgramInput* g_render_target; // vertex, normal, texutre, index

// Init Window
static bool InitGlfwWindow();
static void Terminate();
static void ClearWindow();

static void UpdateRenderTarget();

// callback function

int main()
{
    if(!InitGlfwWindow())
    {
        return -1;
    }


    MeshBuilder* meshBuilder = new MeshBuilder();
    meshBuilder->uniformGrid(1, 10);
    mesh = meshBuilder->getResult();
    g_render_target = new ProgramInput();
    UpdateRenderTarget();
    
    Shader shader("Shaders/basic.vert", "Shaders/phong.frag");
    shader.Bind();
    glm::mat4 view = glm::mat4(1);
    
    shader.SetMat4("uModelViewMatrix", view);
    while (!glfwWindowShouldClose(window))
    {
        ClearWindow();
        shader.Bind();
        glBindVertexArray(*g_render_target);
        glEnableVertexAttribArray(0);
        *(mesh->vbuff()) += 0.001f;
        *(mesh->vbuff()+1) -= 0.001f;
        *(mesh->vbuff()+2) += 0.001f;
        // glDrawElements(GL_TRIANGLES, mesh->ibuffLen(), GL_UNSIGNED_INT, 0);
        
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        shader.setFloat("line_mode", 0.0f);
        shader.setVec3("mesh_color", 0.2, 0.2, 0.5);
        glDrawElements(GL_TRIANGLES, mesh->ibuffLen(), GL_UNSIGNED_INT, 0);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(1.0f);
        shader.setVec3("line_color", 0.1, 0.1, 0.1);
        shader.setFloat("line_mode", 1.0f);
        glDrawElements(GL_TRIANGLES, mesh->ibuffLen(), GL_UNSIGNED_INT, 0);

        glDisable(GL_POLYGON_OFFSET_FILL);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        UpdateRenderTarget();
    }
    Terminate();
    return 0;
}



static bool InitGlfwWindow()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    return true;
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

static void Terminate()
{
    glfwTerminate();
}

static void ClearWindow()
{
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

static void UpdateRenderTarget()
{
    g_render_target->setPositionData(mesh->vbuff(), mesh->vbuffLen());
    g_render_target->setIndexData(mesh->ibuff(), mesh->ibuffLen());
}