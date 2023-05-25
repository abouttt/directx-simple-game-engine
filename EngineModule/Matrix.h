#pragma once

struct Quaternion;

struct Matrix
{
	Matrix() = default;

	// �����Լ�
	float GetDeterminant() const;
	Matrix GetTransposed() const;
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

