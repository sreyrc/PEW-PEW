#pragma once

#include "rapidjson/document.h"

#include "EventManager.h"

class GameObject;

class Component {

public:
	Component() : mpGameObjectOwner(nullptr) {}
	virtual ~Component() {}

	virtual void Update() {};
	virtual void HandleEvent(Event* pEvent) {};


public:
	GameObject* mpGameObjectOwner;
};