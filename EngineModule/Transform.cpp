#include "pch.h"
#include "MathUtil.h"
#include "Transform.h"
#include "Matrix.h"
#include "Quaternion.h"

Transform::Transform()
	: mPosition(Vector::Zero)
	, mEulerAngles(Vector::Zero)
	, mScale(Vector::One)
{
}

Transform::Transform(const Vector& positon, const Vector& euler, const Vector& scale)
	: mPosition(positon)
	, mEulerAngles(euler)
	, mScale(scale)
{
}

Vector Transform::GetPosition() const
{
	return mPosition;
}

Quaternion Transform::GetRotation() const
{
	return mEulerAngles.ToQuaternion();
}

Vector Transform::GetEulerAngles() const
{
	return mEulerAngles;
}

Vector Transform::GetScale() const
{
	return mScale;
}

Vector Transform::GetAxisX() const
{
	Quaternion rotation = mEulerAngles.ToQuaternion();
	rotation.Normalize();
	return rotation.GetAxisX();
}

Vector Transform::GetAxisY() const
{
	Quaternion rotation = mEulerAngles.ToQuaternion();
	rotation.Normalize();
	return rotation.GetAxisY();
}

Vector Transform::GetAxisZ() const
{
	Quaternion rotation = mEulerAngles.ToQuaternion();
	rotation.Normalize();
	return rotation.GetAxisZ();
}

Matrix Transform::GetMatrix() const
{
	D3DXMATRIX dr = GetD3DXMatrix();
	Matrix result;
	memcpy(&result.M, &dr.m, sizeof(Matrix));
	return result;
}

D3DXMATRIX Transform::GetD3DXMatrix() const
{
	D3DXMATRIX matPos;
	D3DXMatrixTranslation(&matPos, mPosition.X, mPosition.Y, mPosition.Z);

	D3DXMATRIX matRot;
	D3DXQUATERNION rotation;
	Vector euler = D3DXToRadian(mEulerAngles);
	D3DXQuaternionRotationYawPitchRoll(&rotation, euler.Y, euler.X, euler.Z);
	D3DXMatrixRotationQuaternion(&matRot, &rotation);

	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, mScale.X, mScale.Y, mScale.Z);

	return matScale * matRot * matPos;
}

void Transform::SetPosition(const Vector& position)
{
	mPosition = position;
}

void Transform::SetRotation(const Quaternion& rotation)
{
	mEulerAngles = rotation.ToEuler();
}

void Transform::SetRotation(const Vector& euler)
{
	mEulerAngles = euler;
}

void Transform::SetScale(const Vector& scale)
{
	mScale = scale;
}

void Transform::AddPosition(const Vector& position)
{
	mPosition += position;
}

void Transform::AddRotation(const Quaternion& rotation)
{
	Vector euler = rotation.ToEuler();
	mEulerAngles += euler;
}

void Transform::AddRotation(const Vector& euler)
{
	mEulerAngles += euler;
}

void Transform::AddSacle(const Vector& scale)
{
	mScale += scale;
}

void Transform::AddRotationX(const float degree)
{
	mEulerAngles.X += degree;
}

void Transform::AddRotationY(const float degree)
{
	mEulerAngles.Y += degree;
}

void Transform::AddRotationZ(const float degree)
{
	mEulerAngles.Z += degree;
}

void Transform::Translate(const Vector& translation)
{
	Vector right = GetAxisX();
	Vector up = GetAxisY();
	Vector look = GetAxisZ();

	Vector posX = Vector(right.X, right.Y, right.Z) * translation.X;
	Vector posY = Vector(up.X, up.Y, up.Z) * translation.Y;
	Vector posZ = Vector(look.X, look.Y, look.Z) * translation.Z;

	mPosition += posX + posY + posZ;
}

Transform Transform::Inverse() const
{
	// 로컬 정보만 남기기 위한 트랜스폼 ( 역행렬 )
	Vector reciprocalScale = Vector::Zero;
	if (!Math::EqualsInTolerance(mScale.X, 0.f))
	{
		reciprocalScale.X = 1.f / mScale.X;
	}
	if (!Math::EqualsInTolerance(mScale.Y, 0.f))
	{
		reciprocalScale.Y = 1.f / mScale.Y;
	}
	if (!Math::EqualsInTolerance(mScale.Z, 0.f))
	{
		reciprocalScale.Z = 1.f / mScale.Z;
	}

	Transform result;
	result.SetScale(reciprocalScale);
	result.SetRotation(mEulerAngles.ToQuaternion().Inverse());
	result.SetPosition(result.GetScale() * (result.GetRotation() * -GetPosition()));
	return result;
}

Transform Transform::LocalToWorld(const Transform& parentWorldTransform) const
{
	Transform result;
	result.SetScale(parentWorldTransform.GetScale() * GetScale());
	result.SetRotation(parentWorldTransform.GetRotation() * GetRotation());
	result.SetPosition(parentWorldTransform.GetPosition() + parentWorldTransform.GetRotation() * (parentWorldTransform.GetScale() * GetPosition()));
	return result;
}

Transform Transform::WorldToLocal(const Transform& parentWorldTransform) const
{
	Transform invParent = parentWorldTransform.Inverse();

	Transform result;
	result.SetScale(invParent.GetScale() * GetScale());
	result.SetRotation(invParent.GetRotation() * GetRotation());
	result.SetPosition(invParent.GetPosition() + (invParent.GetScale() * (invParent.GetRotation() * GetPosition())));
	return result;
}

void Transform::clampEuler(Vector& euler)
{
	euler.X = getAxisClampedValue(euler.X);
	euler.Y = getAxisClampedValue(euler.Y);
	euler.Z = getAxisClampedValue(euler.Z);
}

float Transform::getAxisClampedValue(float rotationValue)
{
	float angle = Math::FMod(rotationValue, 360.f);
	if (angle < 0.f)
	{
		angle += 360.f;
	}

	return angle;
}