#include "pch.h"
#include "BehaviourComponent.h"
#include "GameBehaviourEventManager.h"
#include "EngineUtil.h"
#include "GameEngine.h"
#include "InputManager.h"
#include "LightComponent.h"
#include "MeshComponent.h"
#include "RenderingEngine.h"
#include "ResourceManager.h"
#include "Scene.h"
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

	SceneManager::release();
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

	// ���� ���� ����.
	TimeManager::beginTick();

	// Initialization.

	// Input Event.
	InputManager::update();
	GameBehaviourEventManager::onEnable();
	GameBehaviourEventManager::onStart();

	// Game Logic.
	GameBehaviourEventManager::onUpate();
	GameBehaviourEventManager::onLateUpdate();

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
	GameBehaviourEventManager::onDisable();
	GameBehaviourEventManager::onDestory();

	SceneManager::cleanup();

	// ���� ���� ����.
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
