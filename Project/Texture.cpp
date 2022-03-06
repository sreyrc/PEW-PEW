#include "Texture.h"

#include <glad/glad.h>
#include <iostream>

Texture::Texture(SDL_Surface* pImageSurface, float width, float height) : mTextureId(0), mWidth(width), mHeight(height)
{
   mData = pImageSurface->pixels;

   glGenTextures(1, &mTextureId);
   glBindTexture(GL_TEXTURE_2D, mTextureId);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mData);
   glGenerateMipmap(GL_TEXTURE_2D);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::Bind(GLuint programID, std::string shaderTexName)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureId);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUniform1i(glGetUniformLocation(programID, shaderTexName.c_str()), 0);
}

// Unbind a texture from a texture unit whne no longer needed.
void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
