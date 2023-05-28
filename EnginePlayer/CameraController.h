#pragma once

#include "CameraComponent.h"
#include "GameBehaviourComponent.h"
#include "Vector.h"

class CameraController : public GameBehaviourComponent
{
public:
	void Start() override
	{
		mCameraPtr = CameraComponent::GetCurrentCamera();
	}

	void Update() override
	{
		if (InputManager::GetKey(DIK_W))
		{
			mCameraPtr->GetTransform()->Translate(Vector(0, 0, mSpeed * TimeManager::GetDeltaTime()));
		}
		if (InputManager::GetKey(DIK_S))
		{
			mCameraPtr->GetTransform()->Translate(Vector(0, 0, -mSpeed * TimeManager::GetDeltaTime()));
		}
		if (InputManager::GetKey(DIK_A))
		{
			mCameraPtr->GetTransform()->Translate(Vector(-mSpeed * TimeManager::GetDeltaTime(), 0, 0));
		}
		if (InputManager::GetKey(DIK_D))
		{
			mCameraPtr->GetTransform()->Translate(Vector(mSpeed * TimeManager::GetDeltaTime(), 0, 0));
		}
		if (InputManager::GetKey(DIK_R))
		{
			mCameraPtr->GetTransform()->AddPosition(Vector(0, mSpeed * TimeManager::GetDeltaTime(), 0));
		}
		if (InputManager::GetKey(DIK_F))
		{
			mCameraPtr->GetTransform()->AddPosition(Vector(0, -mSpeed * TimeManager::GetDeltaTime(), 0));
		}

		float x = InputManager::GetAxisMouseY() * 0.2f;
		float y = InputManager::GetAxisMouseX() * 0.2f;
		mCameraPtr->GetTransform()->AddRotationX(InputManager::GetAxisMouseY() * 0.2f);
		mCameraPtr->GetTransform()->AddRotationY(InputManager::GetAxisMouseX() * 0.2f);
	}

private:
	CameraComponent* mCameraPtr = nullptr;
	float mSpeed = 50;
};

