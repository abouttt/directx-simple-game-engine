#include "pch.h"
#include "TimeManager.h"

bool TimeManager::mbInit = false;
long long TimeManager::mStartTimeStamp = 0;
long long TimeManager::mFrameTimeStamp = 0;
long TimeManager::mFrameCount = 0;
float TimeManager::mCyclesPerMilliSeconds;
float TimeManager::mFrameTime = -1.f;
float TimeManager::mElapsedTime = 0.f;
float TimeManager::mAverageFPS = 0.f;
float TimeManager::mFPS = 0.f;

bool TimeManager::init()
{
	if (mbInit)
	{
		return false;
	}

	mCyclesPerMilliSeconds = getCyclesPerMilliSeconds();

	mbInit = true;
	return true;
}

float TimeManager::GetElapsedTime()
{
	return mElapsedTime;
}

float TimeManager::GetDeltaTime()
{
	return mFrameTime / 1000.f;
}

float TimeManager::GetFPS()
{
	return mFPS;
}

void TimeManager::beginTick()
{
	mFrameTimeStamp = getCurrentTimeStamp();
	if (mFrameCount == 0)
	{
		mStartTimeStamp = mFrameTimeStamp;
	}
}

void TimeManager::endTick()
{
	mFrameCount++;
	INT64 currentTimeStamp = getCurrentTimeStamp();
	INT64 frameCycles = currentTimeStamp - mFrameTimeStamp;
	INT64 elapsedCycles = currentTimeStamp - mStartTimeStamp;
	mFrameTime = frameCycles / mCyclesPerMilliSeconds;
	mElapsedTime = elapsedCycles / mCyclesPerMilliSeconds;
	mFPS = mFrameTime == 0.f ? 0.f : 1000.f / mFrameTime;
	mAverageFPS = mElapsedTime == 0.f ? 0.f : 1000.f / mElapsedTime * mFrameCount;
}

float TimeManager::getCyclesPerMilliSeconds()
{
	LARGE_INTEGER frequency;
	if (!QueryPerformanceFrequency(&frequency))
	{
		return 0.f;
	}

	return static_cast<float>(frequency.QuadPart / 1000.f);
}

long long TimeManager::getCurrentTimeStamp()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	return currentTime.QuadPart;
}
