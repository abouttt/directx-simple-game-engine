#include "pch.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "MeshComponent.h"
#include "ResourceManager.h"
#include "Scene.h"

Scene::Scene()
	: mGameObjects()
{
}

const std::wstring& Scene::GetName() const
{
	return mName;
}

std::size_t Scene::GetRootCount() const
{
	return mGameObjects.size();
}

std::vector<GameObject*> Scene::GetRootGameObjects()
{
	std::vector<GameObject*> result(mGameObjects.size());
	for (auto& gameObject : mGameObjects)
	{
		result.emplace_back(gameObject.get());
	}
	return result;
}

GameObject* Scene::CreateGameObject(const std::wstring& name, const std::wstring& tag = _T("UnTagged"))
{
	auto newGameObject = std::make_unique<GameObject>(name, tag);
	return mGameObjects.emplace_back(std::move(newGameObject)).get();
}

GameObject* Scene::CreateCube(const std::wstring& name)
{
	return createGameObjectWithMesh(name, _T("Cube"));
}

GameObject* Scene::CreateSphere(const std::wstring& name)
{
	return createGameObjectWithMesh(name, _T("Sphere"));
}

GameObject* Scene::CreateQuad(const std::wstring& name)
{
	return createGameObjectWithMesh(name, _T("Quad"));
}

GameObject* Scene::CreateCamera(const std::wstring& name)
{
	auto newGameObject = CreateGameObject(name);
	newGameObject->AddComponent<CameraComponent>();
	if (!CameraComponent::GetMainCamera())
	{
		newGameObject->SetTag(_T("MainCamera"));
	}

	return newGameObject;
}

GameObject* Scene::CreateLight(const std::wstring& name, const D3DLIGHTTYPE lightType)
{
	auto newGameObject = CreateGameObject(name);
	newGameObject->AddComponent<LightComponent>(lightType);
	return newGameObject;
}

bool Scene::RemoveGameObject(GameObject* const gameObject)
{
	auto it = std::find_if(mGameObjects.begin(), mGameObjects.end(),
		[&](auto& unique)
		{
			return unique.get() == gameObject;
		});

	if (it != mGameObjects.end())
	{
		mGameObjects.erase(it);
		return true;
	}

	return false;
}

GameObject* Scene::FindGameObject(const std::wstring& name)
{
	auto it = std::find_if(mGameObjects.begin(), mGameObjects.end(),
		[&](auto& gameObject)
		{
			return gameObject->GetName() == name;
		});

	return it != mGameObjects.end() ? it->get() : nullptr;
}

GameObject* Scene::FindGameObjectWithTag(const std::wstring& tag)
{
	auto it = std::find_if(mGameObjects.begin(), mGameObjects.end(),
		[&](auto& gameObject)
		{
			return gameObject->GetTag() == tag;
		});

	return it != mGameObjects.end() ? it->get() : nullptr;
}

void Scene::release()
{
	mGameObjects.clear();
}

GameObject* Scene::createGameObjectWithMesh(const std::wstring& name, const std::wstring& meshName)
{
	auto newGameObject = CreateGameObject(name);
	newGameObject->AddComponent<MeshComponent>(ResourceManager::GetMesh(meshName));
	return newGameObject;
}
