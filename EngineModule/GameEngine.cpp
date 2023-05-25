#include "pch.h"
#include "DXContext.h"
#include "GameEngine.h"
#include "InputManager.h"
#include "TimeManager.h"

bool GameEngine::mbInit = false;

bool GameEngine::Init(const HINSTANCE hInstance, const HWND hWnd, const int width, const int height, const bool bWindowed)
{
	if (mbInit)
	{
		return false;
	}

	if (!DXContext::init(hWnd, width, height, bWindowed) ||
		!InputManager::init(hInstance, hWnd))
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
	InputManager::release();

	mbInit = false;
}

void GameEngine::OnTick()
{
	// 성능 측정 시작.
	TimeManager::beginTick();

	// Input Event.
	InputManager::update();

	// 성능 측정 종료.
	TimeManager::endTick();
}
