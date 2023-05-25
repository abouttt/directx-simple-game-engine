#pragma once

struct Quaternion;

struct Vector
{
	// 생성자
	Vector();
	Vector(float x, float y, float z);
	Vector(const Vector& v);

	// 정적멤버함수
	static float Angle(const Vector& v1, const Vector& v2);
	static Vector Cross(const Vector& v1, const Vector& v2);
	static float Distance(const Vector& v1, const Vector& v2);
	static float DistanceSq(const Vector& v1, const Vector& v2);
	static float Dot(const Vector& v1, const Vector& v2);

	// 멤버함수
	bool IsZero() const;
	Vector GetAbs() const;
	float GetSize() const;
	float GetSizeSq() const;
	float GetMax() const;
	float GetMin() const;
	void Normalize();
	Vector GetNormalize() const;
	Quaternion ToQuaternion() const;
	tstring ToString();

	// 연산자
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
	Vector operator*=(const Vector& v);
	Vector operator/=(const Vector& v);
	bool operator==(const Vector& v) const;
	bool operator!=(const Vector& v) const;

	// 정적멤버변수
	static const Vector Backward;
	static const Vector Down;
	static const Vector Forward;
	static const Vector Left;
	static const Vector One;
	static const Vector Right;
	static const Vector Up;
	static const Vector Zero;

	// 멤버변수
	float X;
	float Y;
	float Z;
};

