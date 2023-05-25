#pragma once

struct Vector;

struct Quaternion
{
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(const Quaternion& q);

	// 정적멤버함수
	static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float slerp);

	// 멤버함수
	Vector ToEuler() const;
	Vector GetAxisX() const;
	Vector GetAxisY() const;
	Vector GetAxisZ() const;
	void Normalize();
	Quaternion GetNormalize() const;
	Quaternion Inverse();
	float Size() const;
	float SizeSq() const;
	tstring ToString() const;

	// 연산자
	Quaternion operator+(const Quaternion& q) const;
	Quaternion operator-() const;
	Quaternion operator-(const Quaternion& q) const;
	Quaternion operator*(const Quaternion& q) const;
	Vector operator*(const Vector& v) const;
	Quaternion operator/(const float scalar) const;

	Quaternion operator+=(const Quaternion& q);
	Quaternion operator-=(const Quaternion& q);
	Quaternion operator*=(const Quaternion& q);
	Quaternion operator/=(const float scalar);

	bool operator==(const Quaternion& q);
	bool operator!=(const Quaternion& q);

	// 정적멤버변수
	static const Quaternion Identity;

	// 멤버변수
	float X;
	float Y;
	float Z;
	float W;
};

