#include "Transform.h"
#include "BigEnemyPowers.h"
#include "GameObject.h"
#include "FrameRateController.h"
#include "WorldVariables.h"

#include <SDL.h>
#include <stdio.h>

extern FrameRateController* gpFrameRateController;

void Transform::Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> transformObj)
{
	mPos.x = (transformObj.FindMember("posX"))->value.GetFloat();
	mPos.y = (transformObj.FindMember("posY"))->value.GetFloat();

	mScale.x = (transformObj.FindMember("scaleX"))->value.GetFloat();
	mScale.y = (transformObj.FindMember("scaleY"))->value.GetFloat();
}

void Transform::Update() {

	if (mpGameObjectOwner->mType == "Bullet") {
		if (mPos.y < 0.0f) {
			mpGameObjectOwner->mDestroyed = true;
		}
	}

	if (mpGameObjectOwner->mType == "Enemy" || mpGameObjectOwner->mType == "Heart") {
		if (mPos.y > 600.0f) {
			mpGameObjectOwner->mDestroyed = true;
		}
	}

	if (mpGameObjectOwner->mType == "Enemy Bullet") {
		if (mPos.y > 650.0f) {
			mpGameObjectOwner->mDestroyed = true;
		}
	}

	if ( (mpGameObjectOwner->mType == "Enemy" && mpGameObjectOwner->GetComponent<BigEnemyPowers>() == nullptr)
		|| mpGameObjectOwner->mType == "Heart" || mpGameObjectOwner->mType == "Beam Ammo") {
		mPos.y += (50.0f * (1.0f - WorldVariables::t) + 150.0f * WorldVariables::t) * gpFrameRateController->GetDeltaTime();
	}

	if (mpGameObjectOwner->mType == "Bullet") {
		mPos += glm::vec2(500 * std::sinf(mRotation * 3.14 / 180) *
			gpFrameRateController->GetDeltaTime(), -500 * std::cosf(mRotation * 3.14 / 180) * gpFrameRateController->GetDeltaTime());
	}

	if (mpGameObjectOwner->mType == "Enemy Bullet") {
		mPos += glm::vec2(0.0f, 300.0f * gpFrameRateController->GetDeltaTime());
	}

	if (mpGameObjectOwner->mType == "Beam") {
		mScale += glm::vec2(500.0f, 0.0f) * gpFrameRateController->GetDeltaTime();
		mPos += glm::vec2(0, -150.0f) * gpFrameRateController->GetDeltaTime();

		if (mScale.x > 1000.0f &&
			mScale.y > 1000.0f) {

			mpGameObjectOwner->mDestroyed = true;
		}
	}

	if (mpGameObjectOwner->mType == "Player") {

		if (mPos.x > 350.0f) { mPos.x = 350.0f; }
		if (mPos.x < 50.0f) { mPos.x = 50.0f; }
		if (mPos.y > 550.0f) { mPos.y = 550.0f; }
		if (mPos.y < 450.0f) { mPos.y = 450.0f; }
	}
}

void Transform::HandleEvent(Event* pEvent)
{
	if(mpGameObjectOwner->mType == "Bullet" ||
		mpGameObjectOwner->mType == "Heart" ||
		mpGameObjectOwner->mType == "Beam Ammo") {

		mpGameObjectOwner->mDestroyed = true;
	}
}
