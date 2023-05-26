#pragma once

struct Quaternion;

struct Vector
{
	// ������
	Vector();
	Vector(float x, float y, float z);

	// ��������Լ�
	static float Angle(const Vector& v1, const Vector& v2);
	static Vector Cross(const Vector& v1, const Vector& v2);
	static float Distance(const Vector& v1, const Vector& v2);
	static float DistanceSq(const Vector& v1, const Vector& v2);
	static float Dot(const Vector& v1, const Vector& v2);
	static Vector Lerp(const Vector& v1, const Vector& v2, float t);

	// ����Լ�
	Vector GetAbs() const;
	float GetSize() const;
	float GetSizeSq() const;
	float GetMax() const;
	float GetMin() const;
	Vector GetNormalize() const;
	void Normalize();
	void Set(float x, float y, float z);
	tstring ToString();

	// ������
	Vector operator+(const Vector& v) const;
	Vector operator+(const float bias) const;
	Vector operator-() const;
	Vector operator-(const Vector& v) const;
	Vector operator-(const float bias) const;
	Vector operator*(const float scale) const;
	Vector operator*(const Vector& v) const;
	Vector operator*(const Quaternion& q) const;
	Vector operator/(const float scale) const;
	Vector operator/(const Vector& v) const;
	Vector operator+=(const Vector& v);
	Vector operator-=(const Vector& v);
	Vector operator*=(const float scale);
	Vector operator*=(const Vector& v);
	Vector operator/=(const float scale);
	Vector operator/=(const Vector& v);
	bool operator==(const Vector& v) const;
	bool operator!=(const Vector& v) const;

	// �����������
	static const Vector Backward;
	static const Vector Down;
	static const Vector Forward;
	static const Vector Left;
	static const Vector One;
	static const Vector Right;
	static const Vector Up;
	static const Vector Zero;

	// �������
	float X;
	float Y;
	float Z;
};

