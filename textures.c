#include <glad/glad.h>
#include <glfw3.h>
#include "shader.h"
#include "stb_image.h"
#include "textures.h"

//Function that contains all the information about all the textures and loads them individually
void loadAllTextures(Shader **shader)
{   unsigned int *textures = (unsigned int*)calloc(12, sizeof(unsigned int));
    textures[0] = loadTexture(shader, "images/chess-pawn-white.png", "textureWhitePawn", 0);
    textures[1] = loadTexture(shader, "images/chess-rook-white.png", "textureWhiteRook", 1);
    textures[2] = loadTexture(shader, "images/chess-knight-white.png", "textureWhiteKnight", 2);
    textures[3] = loadTexture(shader, "images/chess-bishop-white.png", "textureWhiteBishop", 3);
    textures[4] = loadTexture(shader, "images/chess-queen-white.png", "textureWhiteQueen", 4);
    textures[5] = loadTexture(shader, "images/chess-king-white.png", "textureWhiteKing", 5);

    textures[6] = loadTexture(shader, "images/chess-pawn-black.png", "textureBlackPawn", 6);
    textures[7] = loadTexture(shader, "images/chess-rook-black.png", "textureBlackRook", 7);
    textures[8] = loadTexture(shader, "images/chess-knight-black.png", "textureBlackKnight", 8);
    textures[9] = loadTexture(shader, "images/chess-bishop-black.png", "textureBlackBishop", 9);
    textures[10] = loadTexture(shader, "images/chess-queen-black.png", "textureBlackQueen", 10);
    textures[11] = loadTexture(shader, "images/chess-king-black.png", "textureBlackKing", 11);

    for (int i = 0; i<12;i++)
    {
        glActiveTexture(GL_TEXTURE0+i);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
    }
}

unsigned int loadTexture(Shader **shader, const char* path, const char* uniformName, int uniformVal)
{
    //Generating the gl texture id
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    //Set the behaviour of the texture sampling in the s,t and r (x,y,z) directions
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);                   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    //Set the the texture filtering method for scaling up and down, respectively
    //Mipmaps can only be used in the scaling down
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    //Loading in the image
    int width1, height1, nrChannels1;
    unsigned char *data1 = stbi_load(path, &width1, &height1, &nrChannels1, STBI_rgb_alpha); 
    
    //Checking for load errors
    if (data1)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
        glGenerateMipmap(GL_TEXTURE_2D);    
    }
    else
    {
        printf("Failed to load texture");
    }
    //Deallocating the image data since it is no longer necessary
    stbi_image_free(data1);
    //Setting the texture to the correct shader uniform 
    Shader_setInt(shader, uniformName, uniformVal);
    return texture;
}

