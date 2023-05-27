#pragma once

#include "GameObject.h"

class Scene
{
public:
	Scene(const std::wstring& name);
	virtual ~Scene() = default;

public:
	GameObject* CreateGameObject(const std::wstring& name, const std::wstring& tag);
	GameObject* CreateCamera(const std::wstring& name);

	GameObject* FindGameObject(const std::wstring& name);
	GameObject* FindGameObjectWithTag(const std::wstring& tag);
	template<typename T>
	T* FindComponent();

public:
	std::size_t GetRootCount() const;
	std::vector<GameObject*> GetRootGameObjects();

private:
	std::wstring mName;
	std::vector<std::unique_ptr<GameObject>> mGameObjects;
	std::vector<std::unique_ptr<GameObject>> mUnactiveGameObjects;
};

template<typename T>
inline T* Scene::FindComponent()
{
	for (auto& gameObject : mGameObjects)
	{
		if (auto component = gameObject->GetComponent<T>())
		{
			return component;
		}
	}

	return nullptr;
}
