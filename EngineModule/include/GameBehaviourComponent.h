#pragma once

#include "BehaviourComponent.h"
#include "TransformComponent.h"

#include "GameObject.h"
#include "Input.h"
#include "Resources.h"
#include "Scene.h"
#include "Time.h"

#include "MathUtil.h"
#include "Vector3.h"
#include "Transform.h"
#include "Quaternion.h"

class GameBehaviourComponent : public BehaviourComponent
{
public:
	friend class GameObject;
	friend class Scene;

public:
	GameBehaviourComponent();
	~GameBehaviourComponent();

public:
	Scene* GetScene();

protected:	// Game Logic Event.
	virtual void OnEnable() override;
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void OnDisable() override;
	virtual void OnDestroy();

private:
	bool mbStarted;
};

