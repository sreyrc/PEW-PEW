#include "WorldVariables.h"

unsigned int WorldVariables::bulletCount = 0;
unsigned int WorldVariables::enemyCount = 0;
unsigned int WorldVariables::heartCount = 0;
unsigned int WorldVariables::beamAmmoCount = 0;

float WorldVariables::t = 0.0f;

float WorldVariables::timeTillCanShootBullet = 0.5f;
float WorldVariables::timeTillCanShootBeam = 2.0f;
float WorldVariables::timeBetweenSmallEnemyGen = 3.0f;
float WorldVariables::timeBetweenBigEnemyGen = 10.0f;
float WorldVariables::timeBetweenHeartGen = 20.0f;
float WorldVariables::timeBetweenBeamAmmoGen = 25.0f;