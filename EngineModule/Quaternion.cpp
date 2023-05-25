#include "pch.h"
#include "MathUtil.h"
#include "Quaternion.h"
#include "Vector.h"

const Quaternion Quaternion::Identity = Quaternion(0.f, 0.f, 0.f, 1.f);

Quaternion::Quaternion()
	: X(0.f)
	, Y(0.f)
	, Z(0.f)
	, W(1.f)
{
}

Quaternion::Quaternion(float x, float y, float z, float w)
	: X(x)
	, Y(y)
	, Z(z)
	, W(w)
{
}

Quaternion::Quaternion(const Quaternion& q)
	: X(q.X)
	, Y(q.Y)
	, Z(q.Z)
	, W(q.X)
{
}

Quaternion Quaternion::Slerp(const Quaternion& q1, const Quaternion& q2, float slerp)
{
	D3DXQUATERNION result;
	D3DXQUATERNION dq1(q1.X, q1.Y, q1.Z, q1.W);
	D3DXQUATERNION dq2(q2.X, q2.Y, q2.Z, q2.W);
	D3DXQuaternionSlerp(&result, &dq1, &dq2, slerp);
	return Quaternion(result.x, result.y, result.z, result.w);
}

Vector Quaternion::ToEuler() const
{
	D3DXVECTOR3 result;
	D3DXMATRIX mat;
	D3DXQUATERNION quat(X, Y, Z, W);
	D3DXMatrixRotationQuaternion(&mat, &quat);
	D3DXMatrixDecompose(&result, nullptr, nullptr, &mat);
	return Vector(result.x, result.y, result.z);
}

Vector Quaternion::GetAxisX() const
{
	D3DXVECTOR3 axisX;
	D3DXMATRIX mat;
	D3DXQUATERNION quat(X, Y, Z, W);
	D3DXMatrixRotationQuaternion(&mat, &quat);
	axisX.x = mat._11;
	axisX.y = mat._21;
	axisX.z = mat._31;
	return Vector(axisX.x, axisX.y, axisX.z);
}

Vector Quaternion::GetAxisY() const
{
	D3DXVECTOR3 axisY;
	D3DXMATRIX mat;
	D3DXQUATERNION quat(X, Y, Z, W);
	D3DXMatrixRotationQuaternion(&mat, &quat);
	axisY.x = mat._12;
	axisY.y = mat._22;
	axisY.z = mat._32;
	return Vector(axisY.x, axisY.y, axisY.z);
}

Vector Quaternion::GetAxisZ() const
{
	D3DXVECTOR3 axisZ;
	D3DXMATRIX mat;
	D3DXQUATERNION quat(X, Y, Z, W);
	D3DXMatrixRotationQuaternion(&mat, &quat);
	axisZ.x = mat._13;
	axisZ.y = mat._23;
	axisZ.z = mat._33;
	return Vector(axisZ.x, axisZ.y, axisZ.z);
}

void Quaternion::Normalize()
{
	*this = GetNormalize();
}

Quaternion Quaternion::GetNormalize() const
{
	D3DXQUATERNION result;
	D3DXQUATERNION dq(X, Y, Z, W);
	D3DXQuaternionNormalize(&result, &dq);
	return Quaternion(result.x, result.y, result.z, result.w);
}

Quaternion Quaternion::Inverse()
{
	return Quaternion(-X, -Y, -Z, W);
}

float Quaternion::Size() const
{
	D3DXQUATERNION result(X, Y, Z, W);
	return D3DXQuaternionLength(&result);
}

float Quaternion::SizeSq() const
{
	D3DXQUATERNION result(X, Y, Z, W);
	return D3DXQuaternionLengthSq(&result);
}

tstring Quaternion::ToString() const
{
	TCHAR result[64]{};
	Vector euler = ToEuler();
	_sntprintf(result, sizeof(result), _T("(%.3f, %.3f, %.3f)"), euler.X, euler.Y, euler.Z);
	return result;
}

Quaternion Quaternion::operator+(const Quaternion& q) const
{
	return Quaternion(*this) += q;
}

Quaternion Quaternion::operator-() const
{
	return Quaternion(-X, -Y, -Z, -W);
}

Quaternion Quaternion::operator-(const Quaternion& q) const
{
	return Quaternion(*this) -= q;
}

Quaternion Quaternion::operator*(const Quaternion& q) const
{
	return Quaternion(*this) *= q;
}

Vector Quaternion::operator*(const Vector& v) const
{
	D3DXVECTOR3 result;
	D3DXMATRIX mat;
	D3DXQUATERNION dq(X, Y, Z, W);
	D3DXVECTOR3 dv(v.X, v.Y, v.Z);
	D3DXMatrixRotationQuaternion(&mat, &dq);
	D3DXVec3TransformCoord(&result, &dv, &mat);
	return Vector(result.x, result.y, result.z);
}

Quaternion Quaternion::operator/(const float scalar) const
{
	return Quaternion(*this) /= scalar;
}

Quaternion Quaternion::operator+=(const Quaternion& q)
{
	X += q.X;
	Y += q.Y;
	Z += q.Z;
	W += q.W;
	return *this;
}

Quaternion Quaternion::operator-=(const Quaternion& q)
{
	X -= q.X;
	Y -= q.Y;
	Z -= q.Z;
	W -= q.W;
	return *this;
}

Quaternion Quaternion::operator*=(const Quaternion& q)
{
	D3DXQUATERNION result;
	D3DXQUATERNION q1(X, Y, Z, W);
	D3DXQUATERNION q2(q.X, q.Y, q.Z, q.W);
	D3DXQuaternionMultiply(&result, &q1, &q2);
	X = result.x;
	Y = result.y;
	Z = result.z;
	W = result.w;
	return *this;
}

Quaternion Quaternion::operator/=(const float scalar)
{
	D3DXQUATERNION result(X, Y, Z, W);
	result /= scalar;
	X = result.x;
	Y = result.y;
	Z = result.z;
	W = result.w;
	return *this;
}

bool Quaternion::operator==(const Quaternion& q)
{
	float xAbs = Math::Abs(X - q.X);
	float yAbs = Math::Abs(Y - q.Y);
	float zAbs = Math::Abs(Z - q.Z);
	float wAbs = Math::Abs(Z - q.Z);
	return (xAbs <= FLT_EPSILON && yAbs <= FLT_EPSILON && zAbs <= FLT_EPSILON && wAbs <= FLT_EPSILON);
}

bool Quaternion::operator!=(const Quaternion& q)
{
	return !(*this == q);
}
