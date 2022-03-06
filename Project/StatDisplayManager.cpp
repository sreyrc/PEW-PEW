#include "StatDisplayManager.h"
#include "GameObjectFactory.h"
#include "GameObjectManager.h"

extern GameObjectFactory* gpGameObjectFactory;
extern GameObjectManager* gpGameObjectManager;

StatDisplayManager::StatDisplayManager()
	: heartImageDisplayPosX(50.0f), ammoImageDisplayPosX(350.0f)
{
	for (int i = 0; i < 3; i++) {

		GameObject* newHeartImage = gpGameObjectFactory->BuildObject("Heart Image.json");
		newHeartImage->GetComponent<Transform>()->mPos = glm::vec2(heartImageDisplayPosX, 30.0f);
		heartImageDisplayPosX += newHeartImage->GetComponent<Transform>()->mScale.x + 1.0f;
		heartImages.push_back(newHeartImage);

		GameObject* newAmmoImage = gpGameObjectFactory->BuildObject("Beam Ammo Image.json");
		newAmmoImage->GetComponent<Transform>()->mPos = glm::vec2(ammoImageDisplayPosX, 30.0f);
		ammoImageDisplayPosX -= newAmmoImage->GetComponent<Transform>()->mScale.x + 1.0f;
		ammoImages.push_back(newAmmoImage);
	}
}

void StatDisplayManager::HandleEvent(Event* pEvent)
{
	if (pEvent->mEventType == "PLAYER GETS HEART") {
		GameObject* newHeartImage = gpGameObjectFactory->BuildObject("Heart Image.json");
		newHeartImage->GetComponent<Transform>()->mPos = glm::vec2(heartImageDisplayPosX, 30.0f);
		heartImageDisplayPosX += newHeartImage->GetComponent<Transform>()->mScale.x + 1.0f;
		heartImages.push_back(newHeartImage);
	}

	if (pEvent->mEventType == "PLAYER HIT ENEMY!" || 
		pEvent->mEventType == "ENEMY BULLET HITS PLAYER" || 
		pEvent->mEventType == "ENEMY HITS RED LINE" &&
		!heartImages.empty()) {

		GameObject* heartImageToBeDestroyed = heartImages[heartImages.size() - 1];
		heartImageDisplayPosX -= heartImageToBeDestroyed->GetComponent<Transform>()->mScale.x + 5.0f;
		heartImages.pop_back();
		heartImageToBeDestroyed->mDestroyed = true;
	}

	if (pEvent->mEventType == "PLAYER GETS BEAM AMMO") {
		GameObject* newAmmoImage = gpGameObjectFactory->BuildObject("Beam Ammo Image.json");
		newAmmoImage->GetComponent<Transform>()->mPos = glm::vec2(ammoImageDisplayPosX, 30.0f);
		ammoImageDisplayPosX -= newAmmoImage->GetComponent<Transform>()->mScale.x - 1.0f;
		ammoImages.push_back(newAmmoImage);
	}

	if (pEvent->mEventType == "PLAYER SHOOTS BEAM") {

		if (gpGameObjectManager->GetGameObject("Player")->GetComponent<BeamAmmo>()->mAmmo >= 0) {
			GameObject* ammoImageToBeDestroyed = ammoImages[ammoImages.size() - 1];
			ammoImageDisplayPosX += (ammoImageToBeDestroyed->GetComponent<Transform>()->mScale.x + 5.0f);
			ammoImages.pop_back();
			ammoImageToBeDestroyed->mDestroyed = true;
		}
	}
}
