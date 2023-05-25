#pragma once

struct Quaternion;

struct Matrix
{
	Matrix() = default;
	Matrix(const Matrix& m);
	Matrix(float _11, float _12, float _13, float _14,
		float _21, float _22, float _23, float _24,
		float _31, float _32, float _33, float _34,
		float _41, float _42, float _43, float _44);

	// �����Լ�
	float GetDeterminant() const;
	Matrix GetTranspose() const;
	Matrix GetInverse() const;
	void SetIdentity();
	std::vector<tstring> ToString() const;

	// ������
	Matrix operator+(const Matrix& m) const;
	Matrix operator-(const Matrix& m) const;
	Matrix operator*(const Matrix& m) const;
	Matrix operator*(const float scalar) const;
	Matrix operator/(const float scalar) const;

	Matrix& operator+=(const Matrix& m);
	Matrix& operator-=(const Matrix& m);
	Matrix& operator*=(const Matrix& m);
	Matrix& operator*=(const float scalar);
	Matrix& operator/=(const float scalar);

	bool operator==(const Matrix& m) const;
	bool operator!=(const Matrix& m) const;

	// ����������� 
	static const Matrix Identity;

	// ������� 
	float M[4][4]{};
};

