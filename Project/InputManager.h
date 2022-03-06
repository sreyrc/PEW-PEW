#pragma once

#include "SDL_stdinc.h"
#include <glm/glm.hpp>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void Update();
	bool isLeftMouseButtonTriggered();
	bool IsKeyPressed(unsigned int KeyScanCode);
	bool IsKeyTriggered(unsigned int KeyScanCode);
	bool IsKeyReleased(unsigned int KeyScanCode);

	glm::vec2 GetMousePos() { return mMousePos; }
public:



private:
private:
	Uint8 mCurrentState[512];
	Uint8 mPreviousState[512];

	Uint32 mCurrentMouseState;
	Uint32 mPreviousMouseState;

	glm::ivec2 mMousePos;

};
