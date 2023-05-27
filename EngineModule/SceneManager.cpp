#include "pch.h"
#include "Scene.h"
#include "SceneManager.h"

std::vector<std::unique_ptr<Scene>> SceneManager::mScenes;
std::size_t SceneManager::mCurrentSceneIndex = 0;

std::size_t SceneManager::GetSceneCount()
{
	return mScenes.size();
}

Scene* SceneManager::GetActiveScene()
{
	return mScenes[mCurrentSceneIndex].get();
}

Scene* SceneManager::GetSceneAt(std::size_t index)
{
	if (index < 0 || index >= mScenes.size())
	{
		return nullptr;
	}

	return mScenes[index].get();
}

void SceneManager::LoadScene(std::size_t index)
{
	
}

void SceneManager::LoadScene(const std::wstring name)
{
}
