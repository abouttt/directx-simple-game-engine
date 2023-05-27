#pragma once

#include "GameObject.h"

class Scene
{
public:
	friend class SceneManager;

public:
	Scene(const std::wstring& name);
	virtual ~Scene() = default;

public:
	std::size_t GetRootCount() const;
	std::vector<GameObject*> GetRootGameObjects();

	GameObject* CreateGameObject(const std::wstring& name, const std::wstring& tag);
	GameObject* CreateCamera(const std::wstring& name);

	GameObject* FindGameObject(const std::wstring& name);
	GameObject* FindGameObjectWithTag(const std::wstring& tag);
	template<typename T>
	T* FindComponent();

private:
	virtual void init() abstract;
	virtual void release();

private:
	std::wstring mName;
	std::vector<std::unique_ptr<GameObject>> mGameObjects;
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
