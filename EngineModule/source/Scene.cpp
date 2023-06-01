#include "pch.h"
#include "Scene.h"

#include "GameObject.h"

#include "CameraComponent.h"
#include "GameBehaviourComponent.h"
#include "ImageComponent.h"
#include "LightComponent.h"
#include "MeshComponent.h"
#include "TextComponent.h"
#include "Resources.h"

Scene::Scene(const std::wstring& name)
	: mName(name)
	, mGameObjects()
	, mGameBehaviourComponents()
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

GameObject* Scene::CreateGameObject(const std::wstring& name, const std::wstring& tag)
{
	auto newGameObject = std::make_unique<GameObject>(name, tag);
	mGameObjects.emplace_back(std::move(newGameObject));
	return mGameObjects.back().get();
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

GameObject* Scene::CreateImage(const std::wstring& name)
{
	auto newGameObject = CreateGameObject(name);
	newGameObject->AddComponent<ImageComponent>();
	return newGameObject;
}

GameObject* Scene::CreateText(const std::wstring& name)
{
	auto newGameObject = CreateGameObject(name);
	newGameObject->AddComponent<TextComponent>();
	return newGameObject;
}

void Scene::RemoveGameObject(GameObject* const gameObject)
{
	if (!gameObject)
	{
		return;
	}

	if (gameObject->mState == GameObject::eState::Destroyed)
	{
		return;
	}

	for (auto it = mGameObjects.begin(); it != mGameObjects.end(); ++it)
	{
		if (it->get() == gameObject)
		{
			(*it)->SetActive(false);
			(*it)->mState = GameObject::eState::Destroyed;
			break;
		}
	}
}

GameObject* Scene::FindGameObject(const std::wstring& name)
{
	auto it = std::find_if(mGameObjects.begin(), mGameObjects.end(),
		[&name](auto& gameObject)
		{
			if (!gameObject->IsActive())
			{
				return false;
			}

			return gameObject->GetName() == name;
		});

	return it != mGameObjects.end() ? it->get() : nullptr;
}

GameObject* Scene::FindGameObjectWithTag(const std::wstring& tag)
{
	auto it = std::find_if(mGameObjects.begin(), mGameObjects.end(),
		[&tag](auto& gameObject)
		{
			if (!gameObject->IsActive())
			{
				return false;
			}

			return gameObject->GetTag() == tag;
		});

	return it != mGameObjects.end() ? it->get() : nullptr;
}

void Scene::Update()
{
	for (auto gb : mGameBehaviourComponents)
	{
		if (!gb->mbStarted)
		{
			gb->OnEnable();
		}

		if (gb->IsActiveAndEnabled())
		{
			if (!gb->mbStarted)
			{
				gb->Start();
				gb->mbStarted = true;
			}

			gb->Update();
		}
	}
}

void Scene::LateUpdate()
{
	for (auto gb : mGameBehaviourComponents)
	{
		if (gb->IsActiveAndEnabled())
		{
			gb->LateUpdate();
		}
	}
}

void Scene::addGameBehaviourComponent(GameBehaviourComponent* gb)
{
	auto it = std::find(mGameBehaviourComponents.begin(), mGameBehaviourComponents.end(), gb);
	if (it == mGameBehaviourComponents.end())
	{
		mGameBehaviourComponents.emplace_back(gb);
	}
}

void Scene::removeGameBehaviourComponent(GameBehaviourComponent* gb)
{
	auto it = std::find(mGameBehaviourComponents.begin(), mGameBehaviourComponents.end(), gb);
	if (it != mGameBehaviourComponents.end())
	{
		mGameBehaviourComponents.erase(it);
	}
}

GameObject* Scene::createGameObjectWithMesh(const std::wstring& name, const std::wstring& meshName)
{
	auto newGameObject = CreateGameObject(name);
	newGameObject->AddComponent<MeshComponent>(Resources::GetMesh(meshName));
	return newGameObject;
}

void Scene::cleanup()
{
	for (auto it = mGameObjects.begin(); it != mGameObjects.end(); ++it)
	{
		if ((*it)->mState == GameObject::eState::Destroyed)
		{
			mGameObjects.erase(it--);
		}
		else
		{
			(*it)->cleanup();
		}
	}
}

void Scene::release()
{
	mGameObjects.clear();
}
