#pragma once

struct Vector;

struct Quaternion
{
	// ������
	Quaternion();
	Quaternion(float x, float y, float z, float w);

	// ��������Լ�
	static float Dot(const Quaternion& q1, const Quaternion& q2);
	static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);

	// ����Լ�
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

	// ������
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

	// �����������
	static const Quaternion Identity;

	// �������
	float X;
	float Y;
	float Z;
	float W;
};

