#include "pch.h"
#include "GameEngine.h"
#include "InputManager.h"
#include "RenderEngine.h"
#include "TimeManager.h"

bool GameEngine::mbInit = false;

bool GameEngine::Init(const HINSTANCE hInstance, const HWND hWnd, const int width, const int height, const bool bWindowed)
{
	if (mbInit)
	{
		return false;
	}

	if (!RenderEngine::init(hWnd, width, height, bWindowed) ||
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

	RenderEngine::release();
	InputManager::release();

	mbInit = false;
}

void GameEngine::OnTick()
{
	if (!mbInit)
	{
		::MessageBox(nullptr, _T("GameEngine/OnTick : GameEngine is not initialized"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	// 성능 측정 시작.
	TimeManager::beginTick();

	// Initialization.
	// 
	// Input Event.
	InputManager::update();

	// Game Logic.

	// Scene Rendering.
	RenderEngine::preRender();
	RenderEngine::render();
	RenderEngine::postRender();

	// Decommissioning.

	// 성능 측정 종료.
	TimeManager::endTick();
}
