#include "stdafx.h"
#include "Timing.h"
#include <iostream>

Timing* Timing::s_pInstance = 0;

Timing::Timing() : _maxFPS(999.0f)
{
}


Timing::~Timing()
{
}

void Timing::begin() {
	_startTicks = SDL_GetTicks();
}
void Timing::end() {
	_frameTicks = SDL_GetTicks() - _startTicks;
	_delta = _frameTicks / (1000.0f / 60.0f);
	if (_frameTicks < 1000.0f / _maxFPS) SDL_Delay((int)(1000.0f / _maxFPS - _frameTicks));
}

void Timing::calculateFPS()
{
	static const int NUM_SAMPLES = 100;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();
	float currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	prevTicks = currentTicks;

	int count;

	if (currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	}
	else
	{
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
	{
		_fps = 1000.0f / frameTimeAverage;
	}
	else
	{
		_fps = _maxFPS;
	}
	std::cout << _fps << std::endl;
	currentFrame++;
}