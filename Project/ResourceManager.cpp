#include "ResourceManager.h"
#include <SDL_surface.h>
#include <SDL_image.h>

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {
	for (auto &pSurface : mSurfaces)
		SDL_FreeSurface(pSurface.second);

	mSurfaces.clear();
}

SDL_Surface* ResourceManager::LoadSurface(const char* pFilePath, float width, float height) {

	SDL_Surface* pSurface = mSurfaces[pFilePath];
	if (pSurface)
		return pSurface;

	pSurface = IMG_Load(pFilePath);
	
	if (pSurface)
	{
		mSurfaces[pFilePath] = pSurface;

		Texture* pNewTexture = new Texture(pSurface, width, height);
		mTextures[pFilePath] = pNewTexture;
	}

	return pSurface;
}

Texture* ResourceManager::LoadTexture(const char* pFilePath)
{
	return mTextures[pFilePath];
}
