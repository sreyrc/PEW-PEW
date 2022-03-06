#pragma once

#include "GameObject.h"
#include "ComponentCreators.h"
#include "ResourceManager.h"
#include "GameObjectManager.h"

class GameObjectFactory {

public:

	GameObjectFactory();
	
	GameObject* BuildObject(std::string dataFilePath);
	void LevelLoad(std::string dataFilePath);

public:
	std::unordered_map< std::string, void* >mComponentCreators;
};
