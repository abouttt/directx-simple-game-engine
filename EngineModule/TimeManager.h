#pragma once

class TimeManager
{
public:
	friend class GameEngine;

public:
	TimeManager() = delete;
	TimeManager(const TimeManager&) = delete;
	TimeManager& operator=(TimeManager&&) = delete;
	~TimeManager() = delete;

public:
	static float GetElapsedTime();
	static float GetDeltaTime();
	static float GetFPS();

private:
	static bool init();
	static void beginTick();
	static void endTick();
	static void reset();
	static float getCyclesPerMilliSeconds();
	static long long getCurrentTimeStamp();

public:
	static bool mbInit;
	static long long mStartTimeStamp;
	static long long mFrameTimeStamp;
	static long mFrameCount;
	static float mCyclesPerMilliSeconds;
	static float mFrameTime;
	static float mElapsedTime;
	static float mAverageFPS;
	static float mFPS;
};

