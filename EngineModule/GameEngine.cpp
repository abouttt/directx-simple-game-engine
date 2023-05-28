#include "pch.h"
#include "BehaviourComponent.h"
#include "GameBehaviourEventManager.h"
#include "EngineUtil.h"
#include "GameEngine.h"
#include "Input.h"
#include "LightComponent.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "Resources.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Time.h"

bool GameEngine::mbInit = false;

bool GameEngine::Init(const HINSTANCE hInstance, const HWND hWnd, const int width, const int height, const bool bWindowed)
{
	if (mbInit)
	{
		return false;
	}

	if (!Renderer::init(hWnd, width, height, bWindowed) ||
		!Input::init(hInstance, hWnd))
	{
		return false;
	}

	Resources::init();
	Time::init();

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
	Input::release();
	Renderer::release();

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
	Time::beginTick();

	// Initialization.

	// Input Event.
	Input::update();
	GameBehaviourEventManager::onEnable();
	GameBehaviourEventManager::onStart();

	// Game Logic.
	GameBehaviourEventManager::onUpate();
	GameBehaviourEventManager::onLateUpdate();

	// Load Scene.
	if (SceneManager::isReserved())
	{
		Input::clear();
		Renderer::clear();
		Time::clear();
		SceneManager::loadScene();
		return;
	}

	// Scene Rendering.
	Renderer::preRender();
	Renderer::render();
	Renderer::postRender();

	// Decommissioning.
	GameBehaviourEventManager::onDisable();
	GameBehaviourEventManager::onDestory();

	SceneManager::cleanup();

	// 성능 측정 종료.
	Time::endTick();
}

void GameEngine::loadResources()
{
	// Mesh
	Resources::AddNativeMesh(_T("Cube"), GetCubeMesh());
	Resources::AddNativeMesh(_T("Sphere"), GetSphereMesh());
	Resources::AddNativeMesh(_T("Quad"), GetQuadMesh());

	// Texture
	Resources::LoadNativeTexture(_T("Crate"), _T("Textures/crate.jpg"));
	Resources::LoadNativeTexture(_T("DoomGuy"), _T("Textures/doomguy.png"));

	// Material
	Resources::AddMaterial(_T("Default-Material"), eRenderingMode::Opaque, WHITE_MTRL, nullptr);
	Resources::AddMaterial(_T("Crate"), eRenderingMode::Opaque, WHITE_MTRL, Resources::GetTexture(_T("Crate")));
}
