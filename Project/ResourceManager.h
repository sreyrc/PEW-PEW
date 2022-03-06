#pragma once

#include <unordered_map>
#include "Texture.h"

class SDL_Surface;


class ResourceManager {
public:
	ResourceManager();
	~ResourceManager();
	
	SDL_Surface* LoadSurface(const char* pFilePath, float width, float height);
	Texture* LoadTexture(const char* pFilePath);

public:


private:
	std::unordered_map<std::string, SDL_Surface*> mSurfaces;
	std::unordered_map<std::string, Texture*> mTextures;

};
