#pragma once

#include "MathUtil.h"

class Transform
{
public:
	Transform();
	Transform(const D3DXVECTOR3& position);
	Transform(const D3DXVECTOR3& position, const D3DXQUATERNION& rotation);
	Transform(const D3DXVECTOR3& position, const D3DXVECTOR3& euler);
	Transform(const D3DXVECTOR3& position, const D3DXQUATERNION& rotation, const D3DXVECTOR3& scale);
	Transform(const D3DXVECTOR3& position, const D3DXVECTOR3& euler, const D3DXVECTOR3& scale);

public:
	D3DXVECTOR3 GetPosition() const;
	D3DXQUATERNION GetRotation() const;
	D3DXVECTOR3 GetEulerAngles() const;
	D3DXVECTOR3 GetScale() const;
	D3DXVECTOR3 GetAxisX() const;
	D3DXVECTOR3 GetAxisY() const;
	D3DXVECTOR3 GetAxisZ() const;
	D3DXMATRIX GetMatrix() const;

	void SetPosition(const D3DXVECTOR3& position);
	void SetRotation(const D3DXQUATERNION& rotation);
	void SetRotation(const D3DXVECTOR3& euler);
	void SetScale(const D3DXVECTOR3& scale);

	void AddPosition(const D3DXVECTOR3& position);
	void AddRotation(const D3DXQUATERNION& rotation);
	void AddRotation(const D3DXVECTOR3& euler);
	void AddScale(const D3DXVECTOR3& scale);
	void AddRotationX(const float degree);
	void AddRotationY(const float degree);
	void AddRotationZ(const float degree);

	void Translate(const D3DXVECTOR3& translation);

	Transform Inverse() const;
	Transform LocalToWorld(const Transform& parentWorldTransform) const;
	Transform WorldToLocal(const Transform& parentWorldTransform) const;

private:
	void clampEuler(D3DXVECTOR3& euler);
	float getAxisClampedValue(float rotationValue);

private:
	D3DXVECTOR3 mPosition;
	D3DXVECTOR3 mEulerAngles;
	D3DXVECTOR3 mScale;
};
