#include "pch.h"
#include "EngineUtil.h"
#include "GameEngine.h"
#include "InputManager.h"
#include "RenderingEngine.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TimeManager.h"

bool GameEngine::mbInit = false;

bool GameEngine::Init(const HINSTANCE hInstance, const HWND hWnd, const int width, const int height, const bool bWindowed)
{
	if (mbInit)
	{
		return false;
	}

	if (!RenderingEngine::init(hWnd, width, height, bWindowed) ||
		!InputManager::init(hInstance, hWnd))
	{
		return false;
	}

	ResourceManager::init();
	TimeManager::init();

	loadResources();

	mbInit = true;
	return true;
}

void GameEngine::Release()
{
	if (!mbInit)
	{
		return;
	}

	InputManager::release();
	RenderingEngine::release();

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
	
	// Input Event.
	InputManager::update();

	// Game Logic.

	// Load Scene.
	if (SceneManager::isReserved())
	{
		InputManager::clear();
		RenderingEngine::clear();
		TimeManager::clear();
		SceneManager::loadScene();
		return;
	}

	// Scene Rendering.
	RenderingEngine::preRender();
	RenderingEngine::render();
	RenderingEngine::postRender();

	// Decommissioning.

	// 성능 측정 종료.
	TimeManager::endTick();
}

void GameEngine::loadResources()
{
	// Mesh
	ResourceManager::AddNativeMesh(_T("Cube"), GetCubeMesh());
	ResourceManager::AddNativeMesh(_T("Sphere"), GetSphereMesh());
	ResourceManager::AddNativeMesh(_T("Quad"), GetQuadMesh());

	// Texture
	ResourceManager::LoadNativeTexture(_T("Crate"), _T("Textures/crate.jpg"));
	ResourceManager::LoadNativeTexture(_T("DoomGuy"), _T("Textures/doomguy.png"));

	// Material
	ResourceManager::AddMaterial(_T("Default-Material"), eRenderingMode::Opaque, WHITE_MTRL, nullptr);
	ResourceManager::AddMaterial(_T("Crate"), eRenderingMode::Opaque, WHITE_MTRL, ResourceManager::GetTexture(_T("Crate")));
}
