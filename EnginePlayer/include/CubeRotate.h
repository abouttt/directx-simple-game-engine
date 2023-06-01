#pragma once

#include "GameBehaviourComponent.h"
#include "Debug.h"

class CubeRotate : public GameBehaviourComponent
{
public:
	void Update() override
	{
		float speed = 50 * Time::GetDeltaTime();
		GetTransform()->AddLocalRotation(D3DXVECTOR3(speed, speed, speed));
	}

	void Start() override
	{
		Debug::Log(_T("Start"));
	}

	void OnEnable() override
	{
		Debug::Log(_T("OnEnable"));
	}

	void OnDisable() override
	{
		Debug::Log(_T("OnDisable"));
	}

	void OnDestroy() override
	{
		Debug::Log(_T("OnDestroy"));
	}
};

