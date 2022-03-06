#pragma once

#include "Component.h"
#include "Transform.h" 

class BigEnemyPowers : public Component
{
public:
	BigEnemyPowers();
	~BigEnemyPowers() {};

	void Initialize();
	void Update();

private:
	float mTimeTillCanShoot;
	int moveDirection;
	Transform* mpOwnTransform;
};

