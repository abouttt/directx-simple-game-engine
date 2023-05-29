#pragma once

#include "CameraComponent.h"
#include "GameBehaviourComponent.h"
#include "Debug.h"

class CameraController : public GameBehaviourComponent
{
public:
	void Start() override
	{
		mCameraPtr = CameraComponent::GetCurrentCamera();
	}

	void Update() override
	{
		if (Input::GetKey(DIK_W))
		{
			mCameraPtr->GetTransform()->Translate(D3DXVECTOR3(0, 0, mSpeed * Time::GetDeltaTime()));
		}
		if (Input::GetKey(DIK_S))
		{
			mCameraPtr->GetTransform()->Translate(D3DXVECTOR3(0, 0, -mSpeed * Time::GetDeltaTime()));
		}
		if (Input::GetKey(DIK_A))
		{
			mCameraPtr->GetTransform()->Translate(D3DXVECTOR3(-mSpeed * Time::GetDeltaTime(), 0, 0));
		}
		if (Input::GetKey(DIK_D))
		{
			mCameraPtr->GetTransform()->Translate(D3DXVECTOR3(mSpeed * Time::GetDeltaTime(), 0, 0));
		}
		if (Input::GetKey(DIK_R))
		{
			mCameraPtr->GetTransform()->AddPosition(D3DXVECTOR3(0, mSpeed * Time::GetDeltaTime(), 0));
		}
		if (Input::GetKey(DIK_F))
		{
			mCameraPtr->GetTransform()->AddPosition(D3DXVECTOR3(0, -mSpeed * Time::GetDeltaTime(), 0));
		}

		float x = Input::GetAxisMouseY() * 0.2f;
		float y = Input::GetAxisMouseX() * 0.2f;
		mCameraPtr->GetTransform()->AddRotationX(Input::GetAxisMouseY() * 0.2f);
		mCameraPtr->GetTransform()->AddRotationY(Input::GetAxisMouseX() * 0.2f);
	}

	void LateUpdate() override
	{
		Debug::Log(GetTransform()->GetPosition());
	}

private:
	CameraComponent* mCameraPtr = nullptr;
	float mSpeed = 50;
};

