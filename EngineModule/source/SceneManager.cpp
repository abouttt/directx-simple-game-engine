#include "pch.h"
#include "Scene.h"
#include "SceneManager.h"

bool SceneManager::mbReserve = false;
std::vector<std::unique_ptr<Scene>> SceneManager::mScenes;
std::size_t SceneManager::mCurrentSceneIndex = 0;
std::size_t SceneManager::mNextSceneIndex = -1;

std::size_t SceneManager::GetSceneCount()
{
	return mScenes.size();
}

Scene* SceneManager::GetActiveScene()
{
	return mScenes[mCurrentSceneIndex].get();
}

Scene* SceneManager::GetSceneAt(const std::size_t index)
{
	assert(index >= 0 && index < mScenes.size());

	return mScenes[index].get();
}

void SceneManager::LoadScene(const std::size_t index)
{
	assert(!mScenes.empty());
	assert(index >= 0 && index < mScenes.size());

	mNextSceneIndex = index;
	mbReserve = true;
}

void SceneManager::LoadScene(const std::wstring& name)
{
	assert(!mScenes.empty());

	for (std::size_t i = 0; i < mScenes.size(); i++)
	{
		if (mScenes[i]->GetName() == name)
		{
			LoadScene(i);
			break;
		}
	}
}

bool SceneManager::isReserved()
{
	return mbReserve;
}

void SceneManager::loadScene()
{
	mScenes[mCurrentSceneIndex]->mGameObjects.clear();
	mScenes[mNextSceneIndex]->init();
	mCurrentSceneIndex = mNextSceneIndex;
	mNextSceneIndex = -1;
	mbReserve = false;
}
