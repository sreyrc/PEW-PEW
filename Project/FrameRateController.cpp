#include "FrameRateController.h"
#include "limits.h"
#include <SDL_timer.h>

FrameRateController::FrameRateController(unsigned int MaxFrameRate) {
	if (MaxFrameRate == 0)
		MaxFrameRate = UINT_MAX;

	mMaxFrameRate = MaxFrameRate;
	mTicksPerFrame = 1000 / mMaxFrameRate;
	mTickStart = 0;
	mTickEnd = 0;
	mFrameTime = 0;
	mDeltaTime = 0.0f;
}

FrameRateController::~FrameRateController() {}

void FrameRateController::FrameStart() {
	mTickStart = SDL_GetTicks();
}

void FrameRateController::FrameEnd() {
	mTickEnd = SDL_GetTicks();
	while (mTickEnd - mTickStart < mTicksPerFrame)
		mTickEnd = SDL_GetTicks();

	mFrameTime = mTickEnd - mTickStart;
	mDeltaTime = (float) mFrameTime / 1000;
}

unsigned int FrameRateController::GetFrameTime() {
	return mFrameTime;
}

float FrameRateController::GetDeltaTime() {
	return mDeltaTime;
}
