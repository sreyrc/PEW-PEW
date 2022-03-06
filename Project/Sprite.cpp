#include "Sprite.h"
#include "GameObject.h"
#include "Transform.h"
#include "Texture.h"

extern SDL_Window* pWindow;
extern ResourceManager* gpResourceManager;

void Sprite::Update()
{
	SDL_Rect destRect;
	destRect.x = mpGameObjectOwner->GetComponent<Transform>()->mPos.x;
	destRect.y = mpGameObjectOwner->GetComponent<Transform>()->mPos.y;
	SDL_BlitSurface(mpImageSurface, NULL, SDL_GetWindowSurface(pWindow), &destRect);
}

void Sprite::Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> spriteObj)
{
	mpImageSurface = gpResourceManager->LoadSurface((spriteObj.FindMember("Image Path")->value.GetString()), 
		spriteObj.FindMember("Image Width")->value.GetInt(),
		spriteObj.FindMember("Image Height")->value.GetInt());

	mpTexture = gpResourceManager->LoadTexture((spriteObj.FindMember("Image Path")->value.GetString()));

	//mpTexture->mWidth = spriteObj.FindMember("Image Width")->value.GetInt();
	//mpTexture->mHeight = spriteObj.FindMember("Image Height")->value.GetInt();
	//mHeight = spriteObj.FindMember("Image Height")->value.GetInt();
}
