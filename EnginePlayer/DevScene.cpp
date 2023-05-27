#include "pch.h"
#include "DevScene.h"
#include "GameEngine.h"

#include "RenderingEngine.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Time.h"

#include "CameraComponent.h"
#include "GameObject.h"
#include "MeshComponent.h"
#include "TransformComponent.h"

DevScene::DevScene()
{
}

DevScene::~DevScene()
{
}

void DevScene::init()
{
	auto camera = CreateCamera(_T("Main Camera"));
	camera->GetTransform()->SetPosition(Vector(0.f, 0.f, -10.f));

	auto light = CreateLight(_T("Directional Light"), D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL);
	light->GetTransform()->SetRotation(Vector(10, -10, 10));

	auto cube = CreateCube(_T("Cube"));
	cube->GetTransform()->SetPosition(Vector(0, 0, 0));
	cube->GetComponent<MeshComponent>()->SetMaterial(ResourceManager::GetMaterial(_T("Crate")));
}
