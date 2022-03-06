#pragma once

class WorldVariables {

public:

	static unsigned int bulletCount, enemyCount, heartCount, beamAmmoCount;
	
	static float t;

	static float timeTillCanShootBullet, timeTillCanShootBeam, timeBetweenSmallEnemyGen,
		timeBetweenBigEnemyGen, timeBetweenHeartGen, timeBetweenBeamAmmoGen;
};
