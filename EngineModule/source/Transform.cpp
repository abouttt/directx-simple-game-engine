#include "pch.h"
#include "Transform.h"
#include "Vector3.h"
#include "Quaternion.h"

Transform::Transform()
	: mPosition(VECTOR3_ZERO)
	, mEulerAngles(VECTOR3_ZERO)
	, mScale(VECTOR3_ONE)
{
}

Transform::Transform(const D3DXVECTOR3& position)
	: mPosition(position)
	, mEulerAngles(VECTOR3_ZERO)
	, mScale(VECTOR3_ONE)
{
}

Transform::Transform(const D3DXVECTOR3& position, const D3DXQUATERNION& rotation)
	: mPosition(position)
	, mEulerAngles(QuaternionToEuler(rotation))
	, mScale(VECTOR3_ONE)
{
}

Transform::Transform(const D3DXVECTOR3& position, const D3DXVECTOR3& euler)
	: mPosition(position)
	, mEulerAngles(euler)
	, mScale(VECTOR3_ONE)
{
}

Transform::Transform(const D3DXVECTOR3& position, const D3DXQUATERNION& rotation, const D3DXVECTOR3& scale)
	: mPosition(position)
	, mEulerAngles(QuaternionToEuler(rotation))
	, mScale(scale)
{
}

Transform::Transform(const D3DXVECTOR3& position, const D3DXVECTOR3& euler, const D3DXVECTOR3& scale)
	: mPosition(position)
	, mEulerAngles(euler)
	, mScale(scale)
{
}

D3DXVECTOR3 Transform::GetPosition() const
{
	return mPosition;
}

D3DXQUATERNION Transform::GetRotation() const
{
	return EulerToQuaternion(mEulerAngles);
}

D3DXVECTOR3 Transform::GetEulerAngles() const
{
	return mEulerAngles;
}

D3DXVECTOR3 Transform::GetScale() const
{
	return mScale;
}

D3DXVECTOR3 Transform::GetAxisX() const
{
	D3DXQUATERNION rotation = EulerToQuaternion(mEulerAngles);
	D3DXQuaternionNormalize(&rotation, &rotation);
	return rotation * VECTOR3_RIGHT;
}

D3DXVECTOR3 Transform::GetAxisY() const
{
	D3DXQUATERNION rotation = EulerToQuaternion(mEulerAngles);
	D3DXQuaternionNormalize(&rotation, &rotation);
	return rotation * VECTOR3_UP;
}

D3DXVECTOR3 Transform::GetAxisZ() const
{
	D3DXQUATERNION rotation = EulerToQuaternion(mEulerAngles);
	D3DXQuaternionNormalize(&rotation, &rotation);
	return rotation * VECTOR3_FORWARD;
}

D3DXMATRIX Transform::GetMatrix() const
{
	D3DXMATRIX matPos;
	D3DXMATRIX matRot;
	D3DXMATRIX matScale;
	D3DXQUATERNION rotation;
	D3DXVECTOR3 euler = D3DXToRadian(mEulerAngles);

	D3DXMatrixTranslation(&matPos, mPosition.x, mPosition.y, mPosition.z);
	D3DXQuaternionRotationYawPitchRoll(&rotation, euler.y, euler.x, euler.z);
	D3DXMatrixRotationQuaternion(&matRot, &rotation);
	D3DXMatrixScaling(&matScale, mScale.x, mScale.y, mScale.z);

	return matScale * matRot * matPos;
}

void Transform::SetPosition(const D3DXVECTOR3& position)
{
	mPosition = position;
}

void Transform::SetRotation(const D3DXQUATERNION& rotation)
{
	mEulerAngles = QuaternionToEuler(rotation);
}

void Transform::SetRotation(const D3DXVECTOR3& euler)
{
	mEulerAngles = euler;
}

void Transform::SetScale(const D3DXVECTOR3& scale)
{
	mScale = scale;
}

void Transform::AddPosition(const D3DXVECTOR3& position)
{
	mPosition += position;
}

void Transform::AddRotation(const D3DXQUATERNION& rotation)
{
	D3DXVECTOR3 euler = QuaternionToEuler(rotation);
	mEulerAngles += euler;
}

void Transform::AddRotation(const D3DXVECTOR3& euler)
{
	mEulerAngles += euler;
}

void Transform::AddScale(const D3DXVECTOR3& scale)
{
	mScale += scale;
}

void Transform::AddRotationX(const float degree)
{
	mEulerAngles.x += degree;
}

void Transform::AddRotationY(const float degree)
{
	mEulerAngles.y += degree;
}

void Transform::AddRotationZ(const float degree)
{
	mEulerAngles.z += degree;
}

void Transform::Translate(const D3DXVECTOR3& translation)
{
	D3DXVECTOR3 right = GetAxisX();
	D3DXVECTOR3 up = GetAxisY();
	D3DXVECTOR3 look = GetAxisZ();

	D3DXVECTOR3 posX = D3DXVECTOR3(right.x, right.y, right.z) * translation.x;
	D3DXVECTOR3 posY = D3DXVECTOR3(up.x, up.y, up.z) * translation.y;
	D3DXVECTOR3 posZ = D3DXVECTOR3(look.x, look.y, look.z) * translation.z;

	mPosition += posX + posY + posZ;
}

Transform Transform::Inverse() const
{
	// 로컬 정보만 남기기 위한 트랜스폼 ( 역행렬 )
	D3DXVECTOR3 reciprocalScale = VECTOR3_ZERO;
	if (!Math::EqualsInTolerance(mScale.x, 0.f))
	{
		reciprocalScale.x = 1.f / mScale.x;
	}
	if (!Math::EqualsInTolerance(mScale.y, 0.f))
	{
		reciprocalScale.y = 1.f / mScale.y;
	}
	if (!Math::EqualsInTolerance(mScale.z, 0.f))
	{
		reciprocalScale.z = 1.f / mScale.z;
	}

	Transform result;
	result.SetScale(reciprocalScale);
	D3DXQUATERNION rot = EulerToQuaternion(mEulerAngles);
	D3DXQuaternionConjugate(&rot, &rot);
	result.SetRotation(rot);
	result.SetPosition(result.GetScale() * (result.GetRotation() * -mPosition));
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

void Transform::clampEuler(D3DXVECTOR3& euler)
{
	euler.x = getAxisClampedValue(euler.x);
	euler.y = getAxisClampedValue(euler.y);
	euler.z = getAxisClampedValue(euler.z);
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