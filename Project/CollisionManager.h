#pragma once

#include "GameObjectManager.h"
#include "EventManager.h"
#include "Transform.h"

#include <unordered_map> 

extern GameObjectManager* gpGameObjectManager;
extern EventManager* gpEventManager;

class CollisionManager
{

public:
	CollisionManager();
	~CollisionManager() {};

	void Update();
	void StopTimers();

private:
	void CheckForCollisionAndHandle(
		std::vector<GameObject*>* pGameObjectList,
		GameObject* pGameObject,
		std::string eventType,
		std::string pGameObject0Type,
		std::string pGameObject1Type,
		std::string collisionDisableTimerType,
		float timeTillCollisionEnabled);

private:
	std::unordered_map<std::string, float> mCollisionDisableTimers;
	bool mTimersWontDecrement;
	
};

