#include "pch.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "Vector.h"

CameraComponent::CameraComponent()
	: mFov(60)
	, mNear(0.3f)
	, mFar(1000.f)
	, mViewMatrix()
	, mProjMatrix()
{
}

CameraComponent::~CameraComponent()
{
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

void CameraComponent::SetActive(bool bActive)
{
	if (IsActive() == bActive)
	{
		return;
	}

	Object::SetActive(bActive);
}

const D3DXMATRIX& CameraComponent::getViewMatrix()
{
	Vector right = GetTransform()->GetLocalAxisX();
	Vector up = GetTransform()->GetLocalAxisY();
	Vector look = GetTransform()->GetLocalAxisZ();

	Vector pos = GetTransform()->GetPosition();

	float x = -Vector::Dot(right, pos);
	float y = -Vector::Dot(up, pos);
	float z = -Vector::Dot(look, pos);

	mViewMatrix(0, 0) = right.X; mViewMatrix(0, 1) = up.X; mViewMatrix(0, 2) = look.X; mViewMatrix(0, 3) = 0.f;
	mViewMatrix(1, 0) = right.Y; mViewMatrix(1, 1) = up.Y; mViewMatrix(1, 2) = look.Y; mViewMatrix(1, 3) = 0.f;
	mViewMatrix(2, 0) = right.Z; mViewMatrix(2, 1) = up.Z; mViewMatrix(2, 2) = look.Z; mViewMatrix(2, 3) = 0.f;
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