#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

#include "CameraComponent.h"

Scene::Scene(const std::wstring& name)
	: mName(name)
	, mGameObjects()
{
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

GameObject* Scene::CreateCamera(const std::wstring& name)
{
	auto newGameObject = CreateGameObject(name);
	newGameObject->AddComponent<CameraComponent>();
	return newGameObject;
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
