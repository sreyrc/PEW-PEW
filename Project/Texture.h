#pragma once

#include <SDL.h>
#include <glad/glad.h>
#include <string>

class Texture
{
public:
    Texture(SDL_Surface* pImageSurface, float width, float height);

    void Bind(GLuint programID, std::string shaderTexName);
    void Unbind();

public:
    GLuint mTextureId;
    float mWidth, mHeight;
    void* mData;
};
