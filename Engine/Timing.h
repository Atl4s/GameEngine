#pragma once
#include <SDL_timer.h>

class Timing
{
public:
	static Timing* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Timing();
			return s_pInstance;
		}
		return s_pInstance;
	}

	static bool DeleteInstance()
	{
		if (s_pInstance)
		{
			delete s_pInstance;
			s_pInstance = 0;
			return true;
		}
		return false;
	}

	void begin();
	void end();

	void calculateFPS();

	void setMaxFPS(float FPS) { _maxFPS = FPS; }

	float getDelta() { return _delta; }

private:
	float _startTicks = 1.0f, _frameTicks = 1.0f, _fps = 1.0f, _maxFPS, _frameTime = 1.0f, _delta;
protected:

	Timing();
	~Timing();

	static Timing* s_pInstance;
};

