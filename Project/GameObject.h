#pragma once

#include "Component.h"
#include "EventManager.h"

#include <string>
#include <unordered_map>
#include <typeindex>
#include <map>

class GameObject {

public:
	GameObject() : mDestroyed(false) {}
	~GameObject() {

		for (auto it = mComponentMap.begin(); it != mComponentMap.end();) {
			Component* compToBeDeleted = it->second;
			it = mComponentMap.erase(it);
			delete compToBeDeleted;
		}
	};

	template <typename T>
	void AddComponent(Component* comp) {
		comp->mpGameObjectOwner = this;
		mComponentMap[std::type_index(typeid(T))] = comp;
	}

	template <typename T>
	T* GetComponent() {
		if (mComponentMap.find(std::type_index(typeid(T))) != mComponentMap.end()) {
			return static_cast<T*>(mComponentMap[std::type_index(typeid(T))]);
		}
		else {
			return nullptr;
		}
	}

	void Update() {
		for (auto const& [key, val] : mComponentMap) {
			val->Update();
		}
	};

	void HandleEvent(Event* pEvent) {
		for (auto const& [key, val] : mComponentMap) {
			val->HandleEvent(pEvent);
		}
	}

public:
	std::string mType, mName, mColor="";
	bool mTexLoaded, mDestroyed;

private:
	std::unordered_map<std::type_index, Component*> mComponentMap;
};



