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

	// 벰버함수
	float GetDeterminant() const;
	Matrix GetTranspose() const;
	Matrix GetInverse() const;
	void SetIdentity();
	std::vector<tstring> ToString() const;

	// 연산자
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

	// 정적멤버변수 
	static const Matrix Identity;

	// 멤버변수 
	float M[4][4]{};
};

