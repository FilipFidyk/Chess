#include <glad/glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "board.h"
#include "shader.h"
#include "chessPieces.h"
#include "stb_image.h"
#include "textures.h"

GLFWwindow* initGLFW();
void processInput(GLFWwindow *window, unsigned int pieceVAO, unsigned int pieceVBO, unsigned int pieceEBO, unsigned int boardVAO, unsigned int boardVBO, unsigned int boardEBO);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void genVAO(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO, float *vertices, unsigned long long verticesSize, unsigned int *indices, unsigned long long indicesSize, int texturesVAO, unsigned int strideSize);
void subVAO(unsigned int VAO, unsigned int VBO, unsigned int EBO, float *vertices, unsigned long long verticesSize, unsigned int *indices, unsigned long long indicesSize);

unsigned int screenWidth = 800;
unsigned int screenHeight = 800;

int **board;
int previousMouseState = GLFW_RELEASE;
int *firstClickCoords;

int main()
{
    //---------------------------------------------------------------------------------
    //Initialise GLFW and GLAD
    GLFWwindow *window = initGLFW();
    if (window == NULL)
    {
        return -1;
    }
    
    //---------------------------------------------------------------------------------
    //Create shaders
    Shader *shaderBoard;
    Shader_init(&shaderBoard, "shaders/vShader.txt", "shaders/fShader.txt");

    board = initChessBoard();

    float *vertices = createBoardVertices(board);
    unsigned int *indices = createBoardIndices();
    unsigned int boardVAO, boardVBO, boardEBO;
    genVAO(&boardVAO, &boardVBO, &boardEBO, vertices, BOARD_VERTICES_NUMBER*sizeof(float), indices, BOARD_INDICES_NUMBER*sizeof(unsigned int), 0, 4);
    free(vertices);
    free(indices);

    Shader *shaderPieces;
    Shader_init(&shaderPieces, "shaders/vPieceShader.txt", "shaders/fPieceShader.txt");

    vertices = createPieceVertices(board);
    indices = createPieceIndices(board);
    unsigned int pieceVAO, pieceVBO, pieceEBO;
    genVAO(&pieceVAO, &pieceVBO, &pieceEBO, vertices, PIECE_VERTICES_NUMBER*sizeof(float), indices, PIECE_INDICES_NUMBER*sizeof(unsigned int), 1, 6);
    free(vertices);
    free(indices);
    glUseProgram(shaderPieces->ID);
    
    //---------------------------------------------------------------------------------
    //Load all textures
    loadAllTextures(&shaderPieces);

    //---------------------------------------------------------------------------------
    //Other necessary set up
    firstClickCoords = (int*)calloc(2,sizeof(int));

    //Polling loop to keep the window running
    while(!glfwWindowShouldClose(window))
    {
        processInput(window, pieceVAO, pieceVBO, pieceEBO, boardVAO, boardVBO, boardEBO);
        
        glClearColor(0.9f, 0.9f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glUseProgram(shaderBoard->ID);
        glBindVertexArray(boardVAO);
        glDrawElements(GL_TRIANGLES, BOARD_INDICES_NUMBER, GL_UNSIGNED_INT, 0);


        glUseProgram(shaderPieces->ID);
        glBindVertexArray(pieceVAO);
        glDrawElements(GL_TRIANGLES, PIECE_INDICES_NUMBER, GL_UNSIGNED_INT, 0);


        glDisable(GL_BLEND);

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
GLFWwindow* initGLFW()
{
    //instantiating the glfw window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //Create the window
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Chess", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);

    //Initialise GLAD to handle GLFW function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return NULL;
    }  
  
    //Set the size of the rendering window via a viewport
    glViewport(0, 0, screenWidth, screenHeight);

    //Register a callback function for resizing the window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    //Flip the verticality of an image
    //Images expect the 0.0 y position to be on the top, opengl expects that on the bottom
    stbi_set_flip_vertically_on_load(1);
    return window;
}

unsigned int firstClick = 1;

//The function that allows for moving pieces around the board
void processInput(GLFWwindow *window, unsigned int pieceVAO, unsigned int pieceVBO, unsigned int pieceEBO, unsigned int boardVAO, unsigned int boardVBO, unsigned int boardEBO)
{
    //input debouncing so that a mouse input isn't processed multiple times
    int currentMouseState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (previousMouseState == GLFW_RELEASE && currentMouseState == GLFW_PRESS)
    {  
        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            //glfwGetCursorPos returns the pixel location of the cursor in doubles
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            
            //The firstClick global flag the function on whether a piece has been selected or not 
            if (firstClick)
            {
                //FindPiece finds the coordinates of where the user clicks and if a piece exists there
                //it flips the flag
                FindPiece(board, firstClickCoords, xpos, ypos);
                if (firstClickCoords[0] != -1)
                {
                    firstClick = 0;
                }
                for (int i =0; i<8; i++)
                {
                    printf("%d %d %d %d %d %d %d %d\n", board[i][0], board[i][1], board[i][2], board[i][3], board[i][4], board[i][5], board[i][6], board[i][6]);
                } 
                subVAO(boardVAO, boardVBO, boardEBO, createBoardVertices(board), BOARD_VERTICES_NUMBER*sizeof(float), createBoardIndices(board), BOARD_INDICES_NUMBER*sizeof(unsigned int));
            }
            else
            {
                //When the flag is a 0 we move the piece to where the user click --TODO-- this is where take rules inhabit
                MovePiece(board, xpos, ypos, firstClickCoords[0], firstClickCoords[1]);
                firstClick = 1;

                //This then requires modifying the buffers of the pieceVAO so that a correct state of the board can be rendered
                subVAO(pieceVAO, pieceVBO, pieceEBO, createPieceVertices(board), PIECE_VERTICES_NUMBER*sizeof(float), createPieceIndices(board), PIECE_INDICES_NUMBER*sizeof(unsigned int));
            }
        }
    }
    previousMouseState = currentMouseState;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions
    screenWidth = width;
    screenHeight = height;
    glViewport(0, 0, width, height);
}

//Very basic setup of VAOs, VBOs and EBOs, all data is passed in
void genVAO(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO, float *vertices, unsigned long long verticesSize, unsigned int *indices, unsigned long long indicesSize, int modVAO, unsigned int strideSize)
{
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);

    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, strideSize * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    if (modVAO == 0)
    {
        glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, strideSize * sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    else if (modVAO == 1)
    {
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, strideSize * sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, strideSize * sizeof(float), (void*)(5*sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    glBindVertexArray(0);
}

void subVAO(unsigned int VAO, unsigned int VBO, unsigned int EBO, float *vertices, unsigned long long verticesSize, unsigned int *indices, unsigned long long indicesSize)
{
    glBindVertexArray(VAO);
                
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, verticesSize, vertices);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indicesSize, indices);

    glBindVertexArray(0);
}