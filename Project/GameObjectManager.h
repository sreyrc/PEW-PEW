#pragma once

#include "GameObject.h"
#include <vector>
#include <string>
#include <iostream>

class GameObjectManager {

public:
	GameObjectManager() {}

	~GameObjectManager() {
		for (int i = 0; i < mGameObjects.size(); i++) {
			delete mGameObjects[i];			
		}
		mGameObjects.clear();
	};

	void AddGameObject(GameObject* gameObject) {
		mGameObjects.push_back(gameObject);
	}

	void DeleteAllGameObjects() {

		for (int i = 0; i < mGameObjects.size(); i++) {

			GameObject* temp = mGameObjects[i];
			mGameObjects.erase(mGameObjects.begin() + i);
			delete temp;
		}
	}
	void DeleteDestroyedGameObjects() {
		
		for (int i = 0; i < mGameObjects.size(); i++) {

			if(mGameObjects[i]->mDestroyed == true) {

				GameObject* temp = mGameObjects[i];
				mGameObjects.erase(mGameObjects.begin() + i);
				delete temp;
			}
		}
	}

	GameObject* GetGameObject(std::string name) {
		
		for (auto i : mGameObjects) {

			if (i->mName == name) {
				return i;
			}
		}
		return nullptr;
	}

	void DisplayGameObjectList() {
		std::cout << "List of game objects currently active: " << std::endl;
		for (auto i : mGameObjects) {
			std::cout << i->mName << " ";
		}
		std::cout << std::endl;
	}

	void RunUpdates() {
		for (int i = 0; i < mGameObjects.size(); i++) {
			mGameObjects[i]->Update();
		}
	}

	std::vector<GameObject*>* GetGameObjectList() {
		return &mGameObjects;
	}

private:
	std::vector<GameObject*> mGameObjects;
};
