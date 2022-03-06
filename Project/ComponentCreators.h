#pragma once

#include "Sprite.h"
#include "Transform.h"
#include "Controller.h"
#include "Health.h"
#include "BeamAmmo.h"
#include "BigEnemyPowers.h"
#include "StatDisplayManager.h"

class SpriteCreator {

public:
	Sprite* Create() { return new Sprite(); }
};


class TransformCreator {

public:
	Transform* Create() { return new Transform(); }
};


class ControllerCreator {

public:
	Controller* Create() { return new Controller(); }
};


class HealthCreator {

public:
	Health* Create() { return new Health(); }
};


class BeamAmmoCreator {

public:
	BeamAmmo* Create() { return new BeamAmmo(); }
};


class BigEnemyPowersCreator {

public:
	BigEnemyPowers* Create() { return new BigEnemyPowers(); }
};


class StatDisplayManagerCreator {

public:
	StatDisplayManager* Create() { return new StatDisplayManager(); }
};





