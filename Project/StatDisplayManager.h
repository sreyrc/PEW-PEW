#pragma once

#include "Component.h"
#include "EventManager.h"

class StatDisplayManager : public Component
{
public:
	StatDisplayManager(); 
	~StatDisplayManager() {}

	void HandleEvent(Event* pEvent);

private:
	std::vector <GameObject*> heartImages, ammoImages;
	float heartImageDisplayPosX, ammoImageDisplayPosX;
};

