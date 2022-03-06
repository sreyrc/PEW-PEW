#include "BigEnemyPowers.h"
#include "GameObjectFactory.h"
#include "FrameRateController.h"

extern GameObjectFactory* gpGameObjectFactory;
extern FrameRateController* gpFrameRateController;

BigEnemyPowers::BigEnemyPowers()
	: mTimeTillCanShoot(2), mpOwnTransform(nullptr), moveDirection(1)
{
}

void BigEnemyPowers::Initialize()
{
	mpOwnTransform = mpGameObjectOwner->GetComponent<Transform>();

	int randSpawnPos;
	if (rand() % 2 == 0) { randSpawnPos = -50.0f; moveDirection = 1; }
	else { randSpawnPos = 450.0f; moveDirection = -1; }

	mpOwnTransform->mPos = glm::vec2(randSpawnPos, 100.0f);
}

void BigEnemyPowers::Update()
{
	mTimeTillCanShoot -= gpFrameRateController->GetDeltaTime();

	if (mTimeTillCanShoot <= 0.0f) {
		GameObject* newEnemyBullet = gpGameObjectFactory->BuildObject("Enemy Bullet.json");
		newEnemyBullet->GetComponent<Transform>()->mPos = mpOwnTransform->mPos;
		mTimeTillCanShoot = 2.0f;
	}

	mpOwnTransform->mPos += glm::vec2(50.0f * moveDirection * gpFrameRateController->GetDeltaTime(), 0.0f);

	if (moveDirection == 1) {
		if (mpOwnTransform->mPos.x >= 350.0f) { moveDirection = -1; }
	}
	else { if (mpOwnTransform->mPos.x <= 50.0f) { moveDirection = 1; } }
}
