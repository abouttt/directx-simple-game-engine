#include "pch.h"
#include "GameBehaviourComponent.h"
#include "GameBehaviourEventManager.h"

GameBehaviourComponent::GameBehaviourComponent()
{
	GameBehaviourEventManager::AddGameBehaviour(this);
}

GameBehaviourComponent::~GameBehaviourComponent()
{
	GameBehaviourEventManager::RemoveGameBehaviour(this);
}

void GameBehaviourComponent::SetEnable(bool bEnable)
{
	if (IsEnabled() == bEnable)
	{
		return;
	}

	BehaviourComponent::SetEnable(bEnable);

	if (bEnable)
	{
		GameBehaviourEventManager::AddOnEnable(this);
	}
	else
	{
		GameBehaviourEventManager::AddOnDisable(this);
	}
}

void GameBehaviourComponent::OnEnable()
{
}

void GameBehaviourComponent::Start()
{
}

void GameBehaviourComponent::Update()
{
}

void GameBehaviourComponent::LateUpdate()
{
}

void GameBehaviourComponent::OnDisable()
{
}

void GameBehaviourComponent::OnDestroy()
{
}
