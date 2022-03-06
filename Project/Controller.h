#pragma once

//#include "Component.h"
//#include "InputManager.h"
//#include "FrameRateController.h"

#include "Component.h"

class Controller : public Component {

public:
	Controller() = default;
	~Controller() {};
	void Update() override;
	void HandleEvent(Event* pEvent) {};
};
