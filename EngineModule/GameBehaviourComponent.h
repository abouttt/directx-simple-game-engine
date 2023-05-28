#pragma once

#include "BehaviourComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "TransformComponent.h"

#include "Transform.h"
#include "Vector.h"
#include "Quaternion.h"

class GameBehaviourComponent : public BehaviourComponent
{
public:
	friend class GameBehaviourEventManager;

public:
	GameBehaviourComponent();
	~GameBehaviourComponent();

public:
	void SetEnable(bool bEnable) override;

public:	// Game Logic Event.
	virtual void OnEnable();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void OnDisable();
	virtual void OnDestroy();
};

