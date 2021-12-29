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
    if(!InitGlfwWindow())
    {
        return -1;
    }


    MeshBuilder* meshBuilder = new MeshBuilder();
    meshBuilder->uniformGrid(1, 10);
    Mesh* mesh = meshBuilder->getResult();
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->vbuffLen()*sizeof(float), mesh->vbuff(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->ibuffLen()*sizeof(unsigned int), mesh->ibuff(), GL_STATIC_DRAW);

    // position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    // // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);
    // // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    Shader shader("Shaders/basic.vert", "Shaders/phong.frag");
    shader.Bind();
    glm::mat4 view = glm::mat4(1);
    view = glm::rotate(view, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // view = glm::translate(view, glm::vec3(0.0, 0.0, -2.0));
    shader.SetMat4("uModelViewMatrix", view);
    // shader.SetMat4("uProjectionMatrix", glm::perspective((float)glm::radians(45.0f), 1.778f, 0.1f, 1000.0f));
    while (!glfwWindowShouldClose(window))
    {
        ClearWindow();
        shader.Bind();
        glBindVertexArray(VAO);
        // glEnableVertexAttribArray(0);
        glDrawElements(GL_TRIANGLES, mesh->ibuffLen(), GL_UNSIGNED_INT, 0);
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
