#include "pch.h"
#include "DevScene.h"
#include "GameEngine.h"

#include "Renderer.h"
#include "Input.h"
#include "Resources.h"
#include "Time.h"

#include "CameraComponent.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "TextComponent.h"

#include "CameraController.h"
#include "CubeRotate.h"

DevScene::DevScene(const std::wstring& name)
	: Scene(name)
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

	auto cacodoom = CreateQuad(_T("Caco Doom"));
	cacodoom->GetTransform()->SetPosition(D3DXVECTOR3(2, 0, 0));
	cacodoom->GetComponent<MeshComponent>()->SetMaterial(Resources::GetMaterial(_T("Cacodoom")));

	auto cube = CreateCube(_T("Cube"));
	cube->GetTransform()->SetPosition(D3DXVECTOR3(0, 0, 0));
	cube->GetComponent<MeshComponent>()->SetMaterial(Resources::GetMaterial(_T("Crate")));
	cube->AddComponent<CubeRotate>();

	auto cube2 = CreateCube(_T("Cube2"));
	cube2->GetTransform()->SetPosition(D3DXVECTOR3(3, 0, 0));
	cube2->GetTransform()->SetParent(cube->GetTransform());

	auto fire = CreateSphere(_T("Fire"));
	fire->GetTransform()->SetPosition(D3DXVECTOR3(-2, 0, 0));
	fire->GetComponent<MeshComponent>()->SetMaterial(Resources::GetMaterial(_T("Fire")));

	auto ice = CreateSphere(_T("Ice"));
	ice->GetTransform()->SetPosition(D3DXVECTOR3(-4, 0, 0));
	ice->GetComponent<MeshComponent>()->SetMaterial(Resources::GetMaterial(_T("Ice")));

	

	auto doomguy = CreateQuad(_T("Doom Guy"));
	doomguy->GetTransform()->SetPosition(D3DXVECTOR3(2, 0, 5));
	doomguy->GetComponent<MeshComponent>()->SetMaterial(Resources::GetMaterial(_T("DoomGuy")));

	auto image = CreateImage(_T("DoomGuy Image"));
	image->GetTransform()->SetPosition(D3DXVECTOR3(10, 50, 0));
	image->GetTransform()->SetScale(D3DXVECTOR3(0.1f, 0.1f, 0.f));
	image->GetComponent<ImageComponent>()->SetTexture(Resources::GetTexture(_T("DoomGuy")));

	auto text = CreateText(_T("Text"));
	text->GetComponent<TextComponent>()->SetText(_T("Text!!!"));
	text->GetTransform()->SetPosition(D3DXVECTOR3(10, 10, 0));
}
