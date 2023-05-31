#include "pch.h"
#include "CameraComponent.h"
#include "Renderer.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TransformComponent.h"

CameraComponent::CameraComponent()
	: mFov(60)
	, mNear(0.3f)
	, mFar(1000.f)
	, mViewMatrix()
	, mProjMatrix()
{
	Renderer::AddCameraComponent(this);
}

CameraComponent::~CameraComponent()
{
	Renderer::RemoveCameraComponent(this);
}

CameraComponent* CameraComponent::GetCurrentCamera()
{
	return Renderer::GetCurrentCamera();
}

CameraComponent* CameraComponent::GetMainCamera()
{
	auto scene = SceneManager::GetActiveScene();
	auto mainCamera = scene->FindGameObjectWithTag(_T("MainCamera"));
	if (!mainCamera)
	{
		return nullptr;
	}

	return mainCamera->GetComponent<CameraComponent>();
}

int CameraComponent::GetFieldOfView() const
{
	return mFov;
}

float CameraComponent::GetNear() const
{
	return mNear;
}

float CameraComponent::GetFar() const
{
	return mFar;
}

void CameraComponent::SetNear(const float value)
{
	mNear = value;
}

void CameraComponent::SetFar(const float value)
{
	mFar = value;
}

void CameraComponent::SetFieldOfView(const int value)
{
	mFov = value;
}

void CameraComponent::SetEnable(const bool bEnable)
{
	if (IsEnabled() == bEnable)
	{
		return;
	}

	BehaviourComponent::SetEnable(bEnable);
}

const D3DXMATRIX& CameraComponent::getViewMatrix()
{
	D3DXVECTOR3 right = GetTransform()->GetLocalAxisX();
	D3DXVECTOR3 up = GetTransform()->GetLocalAxisY();
	D3DXVECTOR3 look = GetTransform()->GetLocalAxisZ();

	D3DXVECTOR3 pos = GetTransform()->GetPosition();
	float x = -D3DXVec3Dot(&right, &pos);
	float y = -D3DXVec3Dot(&up, &pos);
	float z = -D3DXVec3Dot(&look, &pos);

	mViewMatrix(0, 0) = right.x; mViewMatrix(0, 1) = up.x; mViewMatrix(0, 2) = look.x; mViewMatrix(0, 3) = 0.f;
	mViewMatrix(1, 0) = right.y; mViewMatrix(1, 1) = up.y; mViewMatrix(1, 2) = look.y; mViewMatrix(1, 3) = 0.f;
	mViewMatrix(2, 0) = right.z; mViewMatrix(2, 1) = up.z; mViewMatrix(2, 2) = look.z; mViewMatrix(2, 3) = 0.f;
	mViewMatrix(3, 0) = x;       mViewMatrix(3, 1) = y;    mViewMatrix(3, 2) = z;      mViewMatrix(3, 3) = 1.f;

	return mViewMatrix;
}

const D3DXMATRIX& CameraComponent::getProjectionMatrix(const int width, const int height)
{
	D3DXMatrixPerspectiveFovLH(
		&mProjMatrix,
		D3DXToRadian(mFov),
		static_cast<float>(width) / static_cast<float>(height),
		mNear,
		mFar);

	return mProjMatrix;
}