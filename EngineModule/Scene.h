#pragma once

#include "GameObject.h"

class Scene
{
public:
	friend class SceneManager;

public:
	Scene();
	virtual ~Scene() = default;

public:
	const std::wstring& GetName() const;
	std::size_t GetRootCount() const;
	std::vector<GameObject*> GetRootGameObjects();

	GameObject* CreateGameObject(const std::wstring& name, const std::wstring& tag);
	GameObject* CreateCube(const std::wstring& name);
	GameObject* CreateSphere(const std::wstring& name);
	GameObject* CreateQuad(const std::wstring& name);
	GameObject* CreateCamera(const std::wstring& name);
	GameObject* CreateLight(const std::wstring& name, const D3DLIGHTTYPE lightType);
	void RemoveGameObject(GameObject* const gameObject);

	GameObject* FindGameObject(const std::wstring& name);
	GameObject* FindGameObjectWithTag(const std::wstring& tag);
	template<typename T>
	T* FindComponent();

protected:
	virtual void init() abstract;

private:
	GameObject* createGameObjectWithMesh(const std::wstring& name, const std::wstring& meshName);
	void cleanup();
	void release();

private:
	std::wstring mName;
	std::vector<std::unique_ptr<GameObject>> mGameObjects;
};

template<typename T>
inline T* Scene::FindComponent()
{
	for (auto& gameObject : mGameObjects)
	{
		if (!gameObject->IsActive())
		{
			continue;
		}

		if (auto component = gameObject->GetComponent<T>())
		{
			return component;
		}
	}

	return nullptr;
}
