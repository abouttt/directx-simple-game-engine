#pragma once

class Scene;

class SceneManager
{
public:
	friend class GameEngine;

public:
	SceneManager() = delete;
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(SceneManager&&) = delete;
	~SceneManager() = delete;

public:
	template<typename T>
	static void CreateScene(const std::wstring& name);
	static std::size_t GetSceneCount();
	static Scene* GetActiveScene();
	static Scene* GetSceneAt(const std::size_t index);
	static void LoadScene(const std::size_t index);
	static void LoadScene(const std::wstring& name);

private:
	static bool isReserved();
	static void loadScene();
	static void cleanup();
	static void release();

private:
	static bool mbReserve;
	static std::vector<std::unique_ptr<Scene>> mScenes;
	static std::size_t mCurrentSceneIndex;
	static std::size_t mNextSceneIndex;
};

template<typename T>
inline void SceneManager::CreateScene(const std::wstring& name)
{
	auto newScene = std::make_unique<T>();
	newScene->mName = name;
	mScenes.emplace_back(std::move(newScene));
}
