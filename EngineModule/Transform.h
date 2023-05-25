#pragma once

#include "Vector.h"

struct Matrix;
struct Quaternion;

class Transform
{
public:
	Transform();
	Transform(const Vector& positon, const Vector& euler, const Vector& scale);
	
public:
	Vector GetPosition() const;
	Quaternion GetRotation() const;
	Vector GetEulerAngles() const;
	Vector GetScale() const;
	Vector GetXAxis() const;
	Vector GetYAxis() const;
	Vector GetZAxis() const;
	Matrix GetMatrix() const;

	void SetPosition(const Vector& position);
	void SetRotation(const Quaternion& rotation);
	void SetRotation(const Vector& euler);
	void SetScale(const Vector& scale);

	void AddPosition(const Vector& position);
	void AddRotation(const Quaternion& rotation);
	void AddRotation(const Vector& euler);
	void AddSacle(const Vector& scale);
	void AddRotationX(const float degree);
	void AddRotationY(const float degree);
	void AddRotationZ(const float degree);

	void Translate(const Vector& translation);

	Transform Inverse() const;
	Transform LocalToWorld(const Transform& parentWorldTransform) const;
	Transform WorldToLocal(const Transform& parentWorldTransform) const;

private:
	void clampEuler(Vector& euler);
	float getAxisClampedValue(float rotationValue);

private:
	Vector mPosition = Vector::Zero;
	Vector mEulerAngles = Vector::Zero;
	Vector mScale = Vector::One;
};

