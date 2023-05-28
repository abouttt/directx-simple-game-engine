#pragma once

class GameBehaviourComponent;

class GameBehaviourEventManager
{
public:
	friend class GameEngine;

public:
	GameBehaviourEventManager() = delete;
	GameBehaviourEventManager(const GameBehaviourEventManager&) = delete;
	GameBehaviourEventManager& operator=(GameBehaviourEventManager&&) = delete;
	~GameBehaviourEventManager() = delete;

public:
	static void AddGameBehaviour(GameBehaviourComponent* const gb);
	static void AddOnEnable(GameBehaviourComponent* const gb);
	static void AddOnDisable(GameBehaviourComponent* const gb);
	static void AddOnDestroy(GameBehaviourComponent* const gb);

	static void RemoveGameBehaviour(GameBehaviourComponent* const gb);

private:
	static void onEnable();
	static void onStart();
	static void onUpate();
	static void onLateUpdate();
	static void onDisable();
	static void onDestory();

private:
	static std::vector<GameBehaviourComponent*> mGameBehaviours;
	static std::queue<GameBehaviourComponent*> mOnEnableQueue;
	static std::queue<GameBehaviourComponent*> mStartQueue;
	static std::queue<GameBehaviourComponent*> mOnDisableQueue;
	static std::queue<GameBehaviourComponent*> mOnDestroyQueue;
};

