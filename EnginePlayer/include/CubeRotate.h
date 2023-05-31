#pragma once

#include "GameBehaviourComponent.h"
#include "Debug.h"

class CubeRotate : public GameBehaviourComponent
{
public:
	void Update() override
	{
		float speed = 50 * Time::GetDeltaTime();
		//GetTransform()->AddLocalRotation(D3DXVECTOR3(speed, speed, speed));

		if (Input::GetKey(DIK_UPARROW))
		{
			GetTransform()->AddPosition(D3DXVECTOR3(0, 0, speed));
		}
		if (Input::GetKey(DIK_DOWNARROW))
		{
			GetTransform()->AddPosition(D3DXVECTOR3(0, 0, -speed));
		}
		if (Input::GetKey(DIK_RIGHTARROW))
		{
			GetTransform()->GetChild(0)->AddPosition(D3DXVECTOR3(0, 0, speed));
			//GetTransform()->Translate(D3DXVECTOR3(0, 0, speed));
		}
		if (Input::GetKey(DIK_LEFTARROW))
		{
			GetTransform()->GetChild(0)->AddPosition(D3DXVECTOR3(0, 0, -speed));
			//GetTransform()->Translate(D3DXVECTOR3(0, 0, -speed));
		}
	}

	void LateUpdate()
	{
		Debug::Log(GetTransform()->GetChild(0)->GetLocalPosition());
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

