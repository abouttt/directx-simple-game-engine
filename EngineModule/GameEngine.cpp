#include "pch.h"
#include "DXContext.h"
#include "GameEngine.h"
#include "TimeManager.h"

bool GameEngine::mbInit = false;

bool GameEngine::Init(const HINSTANCE hInstance, const HWND hWnd, const int width, const int height, const bool bWindowed)
{
	if (mbInit)
	{
		return false;
	}

	if (!DXContext::init(hWnd, width, height, bWindowed))
	{
		return false;
	}

	TimeManager::init();

	mbInit = true;
    return true;
}

void GameEngine::Release()
{
	if (!mbInit)
	{
		return;
	}

	DXContext::release();

	mbInit = false;
}

void GameEngine::Tick()
{
	TimeManager::beginTick();

	TimeManager::endTick();
}
