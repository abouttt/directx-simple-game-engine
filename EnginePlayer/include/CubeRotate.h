#pragma once

#include "GameBehaviourComponent.h"

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
		//::MessageBox(nullptr, L"Rotator Start", L"!", MB_ICONEXCLAMATION | MB_OK);
	}

	void OnEnable() override
	{
		//GetTransform()->AddPosition(D3DXVECTOR3(1, 0, 0));
		//::MessageBox(nullptr, L"Rotator OnEnable", L"!", MB_ICONEXCLAMATION | MB_OK);
	}

	void OnDisable() override
	{
		//::MessageBox(nullptr, L"Rotator OnDisable", L"!", MB_ICONEXCLAMATION | MB_OK);
	}

	void OnDestroy() override
	{
		//::MessageBox(nullptr, L"Rotator OnDestroy", L"!", MB_ICONEXCLAMATION | MB_OK);
	}
};

