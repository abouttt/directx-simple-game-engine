#include "pch.h"
#include "GameBehaviourComponent.h"
#include "GameBehaviourEventManager.h"
#include "GameObject.h"

std::vector<GameBehaviourComponent*> GameBehaviourEventManager::mGameBehaviours;
std::queue<GameBehaviourComponent*> GameBehaviourEventManager::mOnEnableQueue;
std::queue<GameBehaviourComponent*> GameBehaviourEventManager::mStartQueue;
std::queue<GameBehaviourComponent*> GameBehaviourEventManager::mOnDisableQueue;
std::queue<GameBehaviourComponent*> GameBehaviourEventManager::mOnDestroyQueue;

void GameBehaviourEventManager::AddGameBehaviour(GameBehaviourComponent* const gb)
{
	assert(gb);

	mGameBehaviours.emplace_back(gb);
	mOnEnableQueue.emplace(gb);
	mStartQueue.emplace(gb);
}

void GameBehaviourEventManager::AddOnEnable(GameBehaviourComponent* const gb)
{
	assert(gb);

	mOnEnableQueue.emplace(gb);
}

void GameBehaviourEventManager::AddOnDisable(GameBehaviourComponent* const gb)
{
	assert(gb);

	mOnDisableQueue.emplace(gb);
}

void GameBehaviourEventManager::AddOnDestroy(GameBehaviourComponent* const gb)
{
	assert(gb);

	mOnDestroyQueue.emplace(gb);
}

void GameBehaviourEventManager::RemoveGameBehaviour(GameBehaviourComponent* const gb)
{
	assert(gb);

	auto it = std::find(mGameBehaviours.begin(), mGameBehaviours.end(), gb);
	if (it != mGameBehaviours.end())
	{
		mGameBehaviours.erase(it);
	}
}

void GameBehaviourEventManager::onEnable()
{
	while (!mOnDisableQueue.empty())
	{
		mOnEnableQueue.front()->Start();
		mOnEnableQueue.pop();
	}
}

void GameBehaviourEventManager::onStart()
{
	while (!mStartQueue.empty())
	{
		mStartQueue.front()->Start();
		mStartQueue.pop();
	}
}

void GameBehaviourEventManager::onUpate()
{
	for (auto gb : mGameBehaviours)
	{
		if (gb->IsActiveAndEnabled())
		{
			gb->Update();
		}
	}
}

void GameBehaviourEventManager::onLateUpdate()
{
	for (auto gb : mGameBehaviours)
	{
		if (gb->IsActiveAndEnabled())
		{
			gb->LateUpdate();
		}
	}
}

void GameBehaviourEventManager::onDisable()
{
	while (!mOnDisableQueue.empty())
	{
		mOnDisableQueue.front()->Start();
		mOnDisableQueue.pop();
	}
}

void GameBehaviourEventManager::onDestory()
{
	while (!mOnDestroyQueue.empty())
	{
		mOnDestroyQueue.front()->Start();
		mOnDestroyQueue.pop();
	}
}