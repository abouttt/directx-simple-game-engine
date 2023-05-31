#pragma once

#include "CameraComponent.h"
#include "GameBehaviourComponent.h"
#include "Debug.h"

class CubeRotate : public GameBehaviourComponent
{
public:
	void Start() override
	{
		mCameraPtr = CameraComponent::GetCurrentCamera();
	}

	void Update() override
	{
		float speed = 50 * Time::GetDeltaTime();
		//GetTransform()->AddLocalRotation(D3DXVECTOR3(speed, speed, speed));

		if (Input::GetKeyDown(DIK_UPARROW))
		{
			mCameraPtr->SetEnable(!mCameraPtr->IsEnabled());
			//GetTransform()->AddPosition(D3DXVECTOR3(0, 0, speed));
		}
		if (Input::GetKey(DIK_DOWNARROW))
		{
			//GetTransform()->AddPosition(D3DXVECTOR3(0, 0, -speed));
		}
		if (Input::GetKey(DIK_RIGHTARROW))
		{
			//GetTransform()->GetChild(0)->AddPosition(D3DXVECTOR3(0, 0, speed));
			//GetTransform()->Translate(D3DXVECTOR3(0, 0, speed));
		}
		if (Input::GetKey(DIK_LEFTARROW))
		{
			//GetTransform()->GetChild(0)->AddPosition(D3DXVECTOR3(0, 0, -speed));
			//GetTransform()->Translate(D3DXVECTOR3(0, 0, -speed));
		}
	}

	void LateUpdate()
	{
		Debug::Log(GetTransform()->GetChild(0)->GetLocalPosition());
	}

private:
	CameraComponent* mCameraPtr = nullptr;
};

