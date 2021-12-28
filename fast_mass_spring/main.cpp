/*
 * @Author: ImGili
 * @Description: 
 */
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"Mesh.h"

// settings
static uint32_t SCR_WIDTH = 800;
static uint32_t SCR_HEIGHT = 600;

static GLFWwindow* window;

// Init Window
static bool InitGlfwWindow();
static void Terminate();
static void ClearWindow();

// callback function


int main()
{
    MeshBuilder meshbuilder;
    meshbuilder.uniformGrid(5,5);
    Mesh* mesh = meshbuilder.getResult();
    if(!InitGlfwWindow())
    {
        return -1;
    }

    while (!glfwWindowShouldClose(window))
    {
        ClearWindow();
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
}
