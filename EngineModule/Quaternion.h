#pragma once

struct Vector;

struct Quaternion
{
	// 생성자
	Quaternion();
	Quaternion(float x, float y, float z, float w);

	// 정적멤버함수
	static float Dot(const Quaternion& q1, const Quaternion& q2);
	static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);

	// 멤버함수
	float GetAngle() const;
	Vector GetAxisX() const;
	Vector GetAxisY() const;
	Vector GetAxisZ() const;
	float GetSize() const;
	float GetSizeSq() const;
	Quaternion GetNormalize() const;
	void Normalize();
	Quaternion GetInverse() const;
	void Set(float x, float y, float z, float w);
	void GetAxisAndAngle(Vector* const outAxis, float* const outAngle) const;
	Vector ToEuler() const;
	std::wstring ToString() const;

	// 연산자
	Quaternion operator+(const Quaternion& q) const;
	Quaternion operator-(const Quaternion& q) const;
	Quaternion operator*(const float scale) const;
	Quaternion operator*(const Quaternion& q) const;
	Vector operator*(const Vector& v) const;
	Quaternion operator/(const float scale) const;
	Quaternion operator+=(const Quaternion& q);
	Quaternion operator-=(const Quaternion& q);
	Quaternion operator*=(const Quaternion& q);
	Quaternion operator/=(const float scale);
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

