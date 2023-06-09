#pragma once

#include "GameObject.h"

class GameBehaviourComponent;

class Scene
{
public:
	friend class GameEngine;
	friend class SceneManager;
	friend class GameBehaviourComponent;

public:
	Scene(const std::wstring& name);
	virtual ~Scene() = default;

public:
	const std::wstring& GetName() const;
	std::size_t GetRootCount() const;
	std::vector<GameObject*> GetRootGameObjects();

	GameObject* CreateGameObject(const std::wstring& name, const std::wstring& tag = _T("UnTagged"));
	GameObject* CreateCube(const std::wstring& name);
	GameObject* CreateSphere(const std::wstring& name);
	GameObject* CreateQuad(const std::wstring& name);
	GameObject* CreateCamera(const std::wstring& name);
	GameObject* CreateLight(const std::wstring& name, const D3DLIGHTTYPE lightType);
	GameObject* CreateImage(const std::wstring& name);
	GameObject* CreateText(const std::wstring& name);
	void RemoveGameObject(GameObject* const gameObject);

	GameObject* FindGameObject(const std::wstring& name);
	GameObject* FindGameObjectWithTag(const std::wstring& tag);
	template<typename T>
	T* FindComponent();

protected:
	void Update();
	void LateUpdate();

	virtual void Init() abstract;

private:
	void addGameBehaviourComponent(GameBehaviourComponent* gb);
	void removeGameBehaviourComponent(GameBehaviourComponent* gb);
	GameObject* createGameObjectWithMesh(const std::wstring& name, const std::wstring& meshName);
	void cleanup();
	void release();

private:
	std::wstring mName;
	std::vector<std::unique_ptr<GameObject>> mGameObjects;
	std::vector<GameBehaviourComponent*> mGameBehaviourComponents;
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
