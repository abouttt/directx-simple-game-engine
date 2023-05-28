#include "pch.h"
#include "Time.h"

bool Time::mbInit = false;
long long Time::mStartTimeStamp = 0;
long long Time::mFrameTimeStamp = 0;
long Time::mFrameCount = 0;
float Time::mCyclesPerMilliSeconds;
float Time::mFrameTime = -1.f;
float Time::mElapsedTime = 0.f;
float Time::mAverageFPS = 0.f;
float Time::mFPS = 0.f;

float Time::GetElapsedTime()
{
	return mElapsedTime;
}

float Time::GetDeltaTime()
{
	return mFrameTime / 1000.f;
}

float Time::GetFPS()
{
	return mFPS;
}

void Time::beginTick()
{
	mFrameTimeStamp = getCurrentTimeStamp();
	if (mFrameCount == 0)
	{
		mStartTimeStamp = mFrameTimeStamp;
	}
}

void Time::endTick()
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

bool Time::init()
{
	if (mbInit)
	{
		return false;
	}

	mCyclesPerMilliSeconds = getCyclesPerMilliSeconds();

	mbInit = true;
	return true;
}

void Time::clear()
{
	mStartTimeStamp = 0;
	mFrameTimeStamp = 0;
	mFrameCount = 0;
	mFrameTime = -1.f;
	mElapsedTime = 0.f;
	mAverageFPS = 0.f;
	mFPS = 0.f;
}

float Time::getCyclesPerMilliSeconds()
{
	LARGE_INTEGER frequency;
	if (!QueryPerformanceFrequency(&frequency))
	{
		return 0.f;
	}

	return static_cast<float>(frequency.QuadPart / 1000.f);
}

long long Time::getCurrentTimeStamp()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	return currentTime.QuadPart;
}
