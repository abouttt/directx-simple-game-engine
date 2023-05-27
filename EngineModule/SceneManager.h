#pragma once

class Scene;

class SceneManager
{
public:
	SceneManager() = delete;
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(SceneManager&&) = delete;
	~SceneManager() = delete;

public:
	template<typename T>
	static void CreateScene();
	static std::size_t GetSceneCount();
	static Scene* GetActiveScene();
	static Scene* GetSceneAt(std::size_t index);
	static void LoadScene(std::size_t index);
	static void LoadScene(const std::wstring name);

private:
	static std::vector<std::unique_ptr<Scene>> mScenes;
	static std::size_t mCurrentSceneIndex;
};

template<typename T>
inline void SceneManager::CreateScene()
{
	auto newScene = std::make_unique<T>();
	mScenes.emplace_back(std::move(newScene));
}
