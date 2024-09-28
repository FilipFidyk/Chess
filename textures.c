#include <glad/glad.h>
#include <glfw3.h>
#include "shader.h"
#include "stb_image.h"
#include "textures.h"

//Function that contains all the information about all the textures and loads them individually
void loadAllTextures(Shader **shader)
{   unsigned int texture1, texture2;
    texture1 = loadTexture(shader, GL_TEXTURE0, "images/chess-pawn.png", "texture1", 0);
    texture2 = loadTexture(shader, GL_TEXTURE1, "images/chess-rook.png", "texture2", 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
}

unsigned int loadTexture(Shader **shader, GLenum activateTexture, const char* path, const char* uniformName, int uniformVal)
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

