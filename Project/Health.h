#pragma once

#include "Component.h"

class Health : public Component 
{
public:
	Health() : mHealth(1) {};
	~Health() {};

	void HandleEvent(Event* pEvent);

public:
	unsigned int mHealth;
};
