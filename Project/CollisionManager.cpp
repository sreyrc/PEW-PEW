#include "CollisionManager.h"
#include "CollisionLib.h"
#include "FrameRateController.h"

extern FrameRateController* gpFrameRateController;

CollisionManager::CollisionManager()
	: mTimersWontDecrement(false)
{
	mCollisionDisableTimers["Time Between Enemies Hitting Red Line"] = 0.0f;
	mCollisionDisableTimers["Time Between Enemy Bullet Hits"] = 0.0f;
	mCollisionDisableTimers["Time Between Beams Hitting Enemy"] = 0.0f;
	mCollisionDisableTimers["Time Between Bullet Hits"] = 0.0f;
	mCollisionDisableTimers["Time Between Enemy Collisions"] = 0.0f;
	mCollisionDisableTimers["Time Between Beam Ammo Grabs"] = 0.0f;
	mCollisionDisableTimers["Time Between Heart Grabs"] = 0.0f;
}

void CollisionManager::Update()
{
	bool breakFromOuterLoop = false;
	auto gameObjectList = gpGameObjectManager->GetGameObjectList();

	for (int i = 0; i < (*gameObjectList).size(); i++) {

		CheckForCollisionAndHandle(
			gameObjectList, gameObjectList->at(i),
			"ENEMY HITS RED LINE", "Red Line", "Enemy",
			"Time Between Enemies Hitting Red Line", 2.0f);

		CheckForCollisionAndHandle(
			gameObjectList, gameObjectList->at(i),
			"ENEMY BULLET HITS PLAYER", "Enemy Bullet", "Player",
			"Time Between Enemy Bullet Hits", 1.0f);

		CheckForCollisionAndHandle(
			gameObjectList, gameObjectList->at(i),
			"BEAM HITS ENEMY", "Beam", "Enemy",
			"Time Between Beams Hitting Enemy", 0.02f);

		CheckForCollisionAndHandle(
			gameObjectList, gameObjectList->at(i),
			"HIT ENEMY ", "Bullet", "Enemy",
			"Time Between Bullet Hits", 0.02f);

		CheckForCollisionAndHandle(
			gameObjectList, gameObjectList->at(i),
			"PLAYER HIT ENEMY!", "Player", "Enemy",
			"Time Between Enemy Collisions", 0.02f);

		CheckForCollisionAndHandle(
			gameObjectList, gameObjectList->at(i),
			"PLAYER GETS BEAM AMMO", "Player", "Beam Ammo",
			"Time Between Beam Ammo Grabs", 3.0f);

		CheckForCollisionAndHandle(
			gameObjectList, gameObjectList->at(i),
			"PLAYER GETS HEART", "Player", "Heart",
			"Time Between Heart Grabs", 3.0f);
	}

	if (!mTimersWontDecrement) {
		for (auto it = mCollisionDisableTimers.begin(); it != mCollisionDisableTimers.end(); it++) {
			it->second -= gpFrameRateController->GetDeltaTime();
		}
	}
}

void CollisionManager::StopTimers()
{
	for (auto it = mCollisionDisableTimers.begin(); it != mCollisionDisableTimers.end(); it++) {
		it->second = 1000.0f;
	}
	mTimersWontDecrement = true;
}

void CollisionManager::CheckForCollisionAndHandle(
	std::vector<GameObject*>* pGameObjectList,
	GameObject* pGameObject,
	std::string eventType,
	std::string pGameObject0Type,
	std::string pGameObject1Type,
	std::string collisionDisableTimerType,
	float timeTillCollisionEnabled)
{
	if (pGameObject->mType == pGameObject0Type) {

		glm::vec2 pos0 = pGameObject->GetComponent<Transform>()->mPos;
		glm::vec2 scale0 = pGameObject->GetComponent<Transform>()->mScale;

		for (int i = 0; i < pGameObjectList->size(); i++) {

			if (pGameObjectList->at(i)->mType == pGameObject1Type) {

				glm::vec2 pos1 = pGameObjectList->at(i)->GetComponent<Transform>()->mPos;
				glm::vec2 scale1 = pGameObjectList->at(i)->GetComponent<Transform>()->mScale;

				if (StaticRectToStaticRect(pos0, scale0, pos1, scale1)
					&& mCollisionDisableTimers[collisionDisableTimerType] <= 0.0f) {

					if (eventType == "HIT ENEMY ") {
						eventType += pGameObjectList->at(i)->mName.back();
					}

					mCollisionDisableTimers[collisionDisableTimerType] = timeTillCollisionEnabled;

					gpEventManager->Subscribe(eventType, pGameObject);
					gpEventManager->Subscribe(eventType, pGameObjectList->at(i));

					//pEventManager->DisplayMap();

					Event newEvent(eventType);
					gpEventManager->BroadcastEventToSubscribers(&newEvent);
				}
			}
		}
	}
}
