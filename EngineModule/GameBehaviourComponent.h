#pragma once

#include "BehaviourComponent.h"
#include "TransformComponent.h"

#include "GameObject.h"
#include "Input.h"
#include "Resources.h"
#include "Time.h"

#include "MathUtil.h"
#include "Vector3.h"
#include "Transform.h"
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

