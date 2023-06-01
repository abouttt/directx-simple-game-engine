#include "pch.h"
#include "GameBehaviourComponent.h"
#include "SceneManager.h"

GameBehaviourComponent::GameBehaviourComponent()
	: mbStarted(false)
{
	GetScene()->addGameBehaviourComponent(this);
}

GameBehaviourComponent::~GameBehaviourComponent()
{
	GetScene()->removeGameBehaviourComponent(this);
}

Scene* GameBehaviourComponent::GetScene()
{
	return SceneManager::GetActiveScene();
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
