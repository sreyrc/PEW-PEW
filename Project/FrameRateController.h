#pragma once


class FrameRateController {
public:
	FrameRateController(unsigned int MaxFrameRate);
	~FrameRateController();

	void FrameStart();
	void FrameEnd();
	unsigned int GetFrameTime();
	float GetDeltaTime();
public:


private:
	unsigned int mTickStart;
	unsigned int mTickEnd;
	unsigned int mMaxFrameRate;
	unsigned int mTicksPerFrame;
	unsigned int mFrameTime;
	float mDeltaTime;
private:

};
