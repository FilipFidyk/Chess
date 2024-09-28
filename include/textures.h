#ifndef TEXTURES_H
#define TEXTURES_H

void loadAllTextures(Shader *shader);
void loadTexture(Shader *shader, GLenum activateTexture, const char* path, const char* uniformName, int uniformVal);

#endif //TEXTURES_H