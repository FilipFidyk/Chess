#ifndef SHADER_H
#define SHADER_H

typedef struct 
{
    unsigned int ID;

} Shader;

static int getFileSize(const char *);
int Shader_init(Shader**, const char*, const char*);
void Shader_use(Shader*);
void Shader_release(Shader**);
void Shader_setInt(Shader**, const char*, int);   
void Shader_setFloat(Shader**, const char*, float);

#endif //SHADER_H