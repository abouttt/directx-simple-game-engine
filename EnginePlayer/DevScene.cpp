#include "pch.h"
#include "DevScene.h"
#include "GameEngine.h"

#include "Renderer.h"
#include "Input.h"
#include "Resources.h"
#include "Time.h"

#include "CameraComponent.h"
#include "GameObject.h"
#include "MeshComponent.h"
#include "TransformComponent.h"

#include "CameraController.h"

DevScene::DevScene()
{
}

DevScene::~DevScene()
{
}

void DevScene::init()
{
	auto camera = CreateCamera(_T("Main Camera"));
	camera->GetTransform()->SetPosition(D3DXVECTOR3(0.f, 0.f, -10.f));
	camera->AddComponent<CameraController>();

	auto light = CreateLight(_T("Directional Light"), D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL);
	light->GetTransform()->SetRotation(D3DXVECTOR3(10, -10, 10));

	auto cube = CreateCube(_T("Cube"));
	cube->GetTransform()->SetPosition(D3DXVECTOR3(0, 0, 0));
	cube->GetComponent<MeshComponent>()->SetMaterial(Resources::GetMaterial(_T("Crate")));
}
