#include "GameObjectSpawner.h"
#include "WorldVariables.h"
#include "GameObjectFactory.h"
#include "FrameRateController.h"

extern FrameRateController* gpFrameRateController;
extern GameObjectFactory* gpGameObjectFactory;

void GameObjectSpawner::SpawnObject()
{
	if (WorldVariables::timeBetweenSmallEnemyGen <= 0.0f) {
		GameObject* newEnemy = gpGameObjectFactory->BuildObject("Enemy.json");
		newEnemy->mName = "Enemy " + std::to_string(++WorldVariables::enemyCount);
		newEnemy->GetComponent<Transform>()->mPos = glm::vec2(rand() % 300 + 50, -50.0f);
		WorldVariables::timeBetweenSmallEnemyGen = 3.0f * (1.0f - WorldVariables::t) + 1.0f * WorldVariables::t;
	}

	if (WorldVariables::timeBetweenBigEnemyGen <= 0.0f) {
		GameObject* newEnemy = gpGameObjectFactory->BuildObject("Big Enemy.json");
		newEnemy->mName = "Enemy " + std::to_string(++WorldVariables::enemyCount);
		newEnemy->GetComponent<BigEnemyPowers>()->Initialize();
		WorldVariables::timeBetweenBigEnemyGen = 20.0f;
	}

	if (WorldVariables::timeBetweenHeartGen <= 0.0f) {
		GameObject* newHeart = gpGameObjectFactory->BuildObject("Heart.json");
		newHeart->mName = "Heart " + std::to_string(++WorldVariables::heartCount);
		newHeart->GetComponent<Transform>()->mPos = glm::vec2(rand() % 300 + 50, -50.0f);
		WorldVariables::timeBetweenHeartGen = rand() % 20 + 10;
	}

	if (WorldVariables::timeBetweenBeamAmmoGen <= 0.0f) {
		GameObject* newBeamAmmo = gpGameObjectFactory->BuildObject("Beam Ammo.json");
		newBeamAmmo->mName = "Beam Ammo " + std::to_string(++WorldVariables::beamAmmoCount);
		newBeamAmmo->GetComponent<Transform>()->mPos = glm::vec2(rand() % 300 + 50, -50.0f);
		WorldVariables::timeBetweenBeamAmmoGen = rand() % 20 + 10;
	}
}

void GameObjectSpawner::UpdateWorldTimers()
{
	WorldVariables::timeTillCanShootBullet -= gpFrameRateController->GetDeltaTime();
	WorldVariables::timeTillCanShootBeam -= gpFrameRateController->GetDeltaTime();
	WorldVariables::timeBetweenSmallEnemyGen -= gpFrameRateController->GetDeltaTime();
	WorldVariables::timeBetweenBigEnemyGen -= gpFrameRateController->GetDeltaTime();
	WorldVariables::timeBetweenHeartGen -= gpFrameRateController->GetDeltaTime();
	WorldVariables::timeBetweenBeamAmmoGen -= gpFrameRateController->GetDeltaTime();
}

void GameObjectSpawner::ResetVariables()
{
	WorldVariables::enemyCount = 0;
	WorldVariables::bulletCount = 0;
	WorldVariables::heartCount = 0;
	WorldVariables::beamAmmoCount = 0;
}
