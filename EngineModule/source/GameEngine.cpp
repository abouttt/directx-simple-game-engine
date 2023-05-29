#include "pch.h"
#include "EngineUtil.h"
#include "GameBehaviourEventManager.h"
#include "GameEngine.h"
#include "Input.h"
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

	SceneManager::GetActiveScene()->release();
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
	GameBehaviourEventManager::onEnable();
	GameBehaviourEventManager::onStart();

	// Input Event.
	Input::update();

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
	Renderer::drawUI();
	Renderer::postRender();

	// Decommissioning.
	GameBehaviourEventManager::onDisable();
	GameBehaviourEventManager::onDestory();

	SceneManager::GetActiveScene()->cleanup();

	// 성능 측정 종료.
	Time::endTick();
}

void GameEngine::loadResources()
{
	// Mesh
	Resources::AddNativeMesh(_T("Cube"), GetCubeMesh(Renderer::getDevice()));
	Resources::AddNativeMesh(_T("Sphere"), GetSphereMesh(Renderer::getDevice()));
	Resources::AddNativeMesh(_T("Quad"), GetQuadMesh(Renderer::getDevice()));

	// Texture
	Resources::LoadNativeTexture(_T("Crate"), _T("Textures/crate.jpg"));
	Resources::LoadNativeTexture(_T("DoomGuy"), _T("Textures/doomguy.png"));
	Resources::LoadNativeTexture(_T("Cacodoom"), _T("Textures/cacodoom.png"));
	Resources::LoadNativeTexture(_T("Fire"), _T("Textures/fire.jpg"));
	Resources::LoadNativeTexture(_T("Ice"), _T("Textures/ice.jpg"));

	// Material
	Resources::AddMaterial(_T("Default-Material"), eRenderingMode::Opaque, WHITE_MTRL, nullptr);
	Resources::AddMaterial(_T("Crate"), eRenderingMode::Opaque, WHITE_MTRL, Resources::GetTexture(_T("Crate")));
	Resources::AddMaterial(_T("DoomGuy"), eRenderingMode::Cutout, WHITE_MTRL, Resources::GetTexture(_T("DoomGuy")));
	Resources::AddMaterial(_T("Cacodoom"), eRenderingMode::Cutout, WHITE_MTRL, Resources::GetTexture(_T("Cacodoom")));
	Resources::AddMaterial(_T("Fire"), eRenderingMode::Opaque, WHITE_MTRL, Resources::GetTexture(_T("Fire")));
	Resources::AddMaterial(_T("Ice"), eRenderingMode::Opaque, WHITE_MTRL, Resources::GetTexture(_T("Ice")));
}
