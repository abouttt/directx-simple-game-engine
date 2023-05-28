#pragma once

class Time
{
public:
	friend class GameEngine;

public:
	Time() = delete;
	Time(const Time&) = delete;
	Time& operator=(Time&&) = delete;
	~Time() = delete;

public:
	static float GetElapsedTime();
	static float GetDeltaTime();
	static float GetFPS();

private:
	static void beginTick();
	static void endTick();
	static bool init();
	static void clear();
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

