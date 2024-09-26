#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad.h>
#include <glfw3.h>
#include "shader.h"


//Opens a file successfully, seeks to the end and returns the size of the file
static int getFileSize(const char *filePath)
{
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filePath);
        return -1;
    }
    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    rewind(file);
    fclose(file);
    return fileSize;
}

static void checkCompileErrors(const char *type, unsigned int shader)
{
    int success;
    char infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (strcmp(type, "PROGRAM") != 0)
    {
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            printf("ERROR::SHADER::%s::COMPILATION_FAILED\n%s", type, infoLog);
        }
    }
    else
    {
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            printf("ERROR::SHADER::%s::LINKING_FAILED\n%s", type, infoLog);
        }
    }
}

//Initialising a shader
int Shader_init(Shader** self, const char* vertexPath, const char* fragmentPath)
{
    *self = (Shader*)calloc(1, sizeof(Shader));
    
    //find the sizes of the shaders' source files
    int vertexfileSize = getFileSize(vertexPath);
    int fragmentFileSize = getFileSize(fragmentPath);
    if (vertexfileSize == -1 || fragmentFileSize== -1 )
    {
        printf("SIZE WASN'T ACQUIRED");
        return -1;
    }

    //Set strings large enough to hold the files
    char *vertexCode = (char*)calloc(vertexfileSize+1, sizeof(char));
    char *fragmentCode = (char*)calloc(fragmentFileSize+1, sizeof(char));
    if (vertexCode == NULL || fragmentCode == NULL)
    {
        printf("POINTERS  WEREN'T SET");
        return -1;
    }
    
    //Open the files and read them in
    FILE *vertexFile = fopen(vertexPath, "rb");
    FILE *fragmentFile = fopen(fragmentPath, "rb");
    if (vertexFile == NULL || fragmentFile == NULL)
    {
        printf("FILES WEREN'T OPENED");
        return -1;
    }

    size_t bytesReadv = fread(vertexCode, 1, vertexfileSize, vertexFile);
    size_t bytesReadf = fread(fragmentCode, 1, fragmentFileSize, fragmentFile);
    if (bytesReadv != vertexfileSize || bytesReadf != fragmentFileSize)
    {
        printf("FILES WERE READ INCORRECTLY");
        return -1;
    }
    
    vertexCode[vertexfileSize] = '\0';
    fragmentCode[fragmentFileSize] = '\0';

    //Set the strings with code to const char* variants
    const char* vShaderCode = vertexCode;
    const char* fShaderCode = fragmentCode;
    
    //Close the files
    fclose(vertexFile);
    fclose(fragmentFile);

    //----------------------------------------------------
    /*
    Compiling of the shader
    */
    unsigned int vertex, fragment;

    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // print compile errors if any
    checkCompileErrors("VERTEX", vertex);

    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // print compile errors if any
    checkCompileErrors("FRAGMENT", fragment);
    
    //Set the struct ID attribute to refer to the compiled shader
    (*self)->ID = glCreateProgram();
    glAttachShader((*self)->ID, vertex);
    glAttachShader((*self)->ID, fragment);
    glLinkProgram((*self)->ID);
    // print linking errors if any
    checkCompileErrors("PROGRAM", (*self)->ID);

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    //deallocate the strings in the heap
    free(vertexCode);
    free(fragmentCode);

    return 1;
}

void Shader_use(Shader *self)
{
    glUseProgram(self->ID);
}

void Shader_release(Shader **self)
{
    free(*self);
}

void Shader_setInt(Shader **self, const char *name, int value)
{
    glUniform1i(glGetUniformLocation((*self)->ID, name), value);
}

void Shader_setFloat(Shader **self, const char *name, float value)
{
    glUniform1f(glGetUniformLocation((*self)->ID, name), value);
}
