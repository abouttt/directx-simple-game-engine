#pragma once

struct Vector;

struct Quaternion
{
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(const Quaternion& q);

	// ��������Լ�
	static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float slerp);

	// ����Լ�
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

	// ������
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

	// �����������
	static const Quaternion Identity;

	// �������
	float X;
	float Y;
	float Z;
	float W;
};

