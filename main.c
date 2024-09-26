#include <glad/glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "shader.h"
#include "chessPieces.h"
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void genVAO(unsigned int *VAO, float *vertices, unsigned long long verticesSize, unsigned int *indices, unsigned long long indicesSize, int texturesVAO);

int main()
{
    //instantiating the glfw window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //Create the window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Chess", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //Initialise GLAD to handle GLFW function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return -1;
    }  
  
    //Set the size of the rendering window via a viewport
    glViewport(0, 0, 800, 600);

    //Register a callback function for resizing the window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    Shader *shaderBoard;
    Shader_init(&shaderBoard, "shaders/vShader.txt", "shaders/fShader.txt");

    float *vertices = createBoardVertices();
    unsigned int *indices = createBoardIndices();
    unsigned int boardVAO;
    genVAO(&boardVAO, vertices, 3*81*sizeof(float), indices, 3*64*sizeof(unsigned int), 0);
    free(vertices);
    free(indices);

    unsigned int **chessPieces = initChessBoard();

    //Polling loop to keep the window running
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.9f, 0.9f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderBoard->ID);
        glBindVertexArray(boardVAO);
        glDrawElements(GL_TRIANGLES, 3*64, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
    //glDeleteProgram(shaderProgram);

    glfwTerminate(); 
    return 0;
}


/*
//Input processing example function
void processInput(GLFWwindow *window)
{
    //Every frame is checked if a button is in the pressed position, escape in this case
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }
}
*/

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void genVAO(unsigned int *VAO, float *vertices, unsigned long long verticesSize, unsigned int *indices, unsigned long long indicesSize, int texturesVAO)
{
    unsigned int VBO, EBO;
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    if (texturesVAO)
    {
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    glBindVertexArray(0);
}