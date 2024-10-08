#ifndef TEXTURES_H
#define TEXTURES_H

void loadAllTextures(Shader **shader);
unsigned int loadTexture(Shader **shader, const char* path, const char* uniformName, int uniformVal);

#endif //TEXTURES_H