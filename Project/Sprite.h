#pragma once

#include "Component.h"
#include "ResourceManager.h"

#include <SDL.h>
#include "Texture.h"

class Sprite : public Component {

public:
	Sprite() { mpImageSurface = nullptr; mpTexture = nullptr; }
	~Sprite() {};

	void Update() override;
	void Deserialize (rapidjson::GenericObject<false, rapidjson::Value::ValueType> spriteObj);
	void HandleEvent(Event* pEvent) {};

public:
	SDL_Surface* mpImageSurface;
	Texture* mpTexture;
	//float mWidth, mHeight;
};