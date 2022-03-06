#pragma once

#include "EventManager.h"
#include <iostream>

class BeamAmmo : public Component
{
public:
	BeamAmmo() : mAmmo(3) {};
	~BeamAmmo() {}

	void HandleEvent(Event* pEvent) {

		if (pEvent->mEventType == "PLAYER GETS BEAM AMMO") {
			mAmmo++;
			//std::cout << "Picked up ammo: Now ammo = " << mAmmo << std::endl;
		}
		
		if (pEvent->mEventType == "PLAYER SHOOTS BEAM") {
			mAmmo--;
			//std::cout << "Shot a beam: Now ammo = " << mAmmo << std::endl;
		}

	}

public:
	unsigned int mAmmo;
};

