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

float Quaternion::Dot(const Quaternion& q1, const Quaternion& q2)
{
	D3DXQUATERNION dq1(q1.X, q1.Y, q1.Z, q1.W);
	D3DXQUATERNION dq2(q2.X, q2.Y, q2.Z, q2.W);
	return D3DXQuaternionDot(&dq1, &dq2);
}

Quaternion Quaternion::Slerp(const Quaternion& q1, const Quaternion& q2, float t)
{
	D3DXQUATERNION result;
	D3DXQUATERNION dq1(q1.X, q1.Y, q1.Z, q1.W);
	D3DXQUATERNION dq2(q2.X, q2.Y, q2.Z, q2.W);
	D3DXQuaternionSlerp(&result, &dq1, &dq2, t);
	return Quaternion(result.x, result.y, result.z, result.w);
}

float Quaternion::GetAngle() const
{
	return 2.f * std::acosf(W);
}

Vector Quaternion::GetAxisX() const
{
	D3DXMATRIX dm;
	D3DXQUATERNION dq(X, Y, Z, W);
	D3DXMatrixRotationQuaternion(&dm, &dq);
	return Vector(dm._11, dm._21, dm._31);
}

Vector Quaternion::GetAxisY() const
{
	D3DXMATRIX dm;
	D3DXQUATERNION dq(X, Y, Z, W);
	D3DXMatrixRotationQuaternion(&dm, &dq);
	return Vector(dm._12, dm._22, dm._32);
}

Vector Quaternion::GetAxisZ() const
{
	D3DXMATRIX dm;
	D3DXQUATERNION dq(X, Y, Z, W);
	D3DXMatrixRotationQuaternion(&dm, &dq);
	return Vector(dm._13, dm._23, dm._33);
}

float Quaternion::GetSize() const
{
	D3DXQUATERNION dq(X, Y, Z, W);
	return D3DXQuaternionLength(&dq);
}

float Quaternion::GetSizeSq() const
{
	D3DXQUATERNION dq(X, Y, Z, W);
	return D3DXQuaternionLengthSq(&dq);
}

Quaternion Quaternion::GetNormalize() const
{
	D3DXQUATERNION result;
	D3DXQUATERNION dq(X, Y, Z, W);
	D3DXQuaternionNormalize(&result, &dq);
	return Quaternion(result.x, result.y, result.z, result.w);
}

void Quaternion::Normalize()
{
	*this = GetNormalize();
}

Quaternion Quaternion::GetInverse() const
{
	return Quaternion(-X, -Y, -Z, W);
}

void Quaternion::Set(float x, float y, float z, float w)
{
	X = x;
	Y = y;
	Z = z;
	W = w;
}

void Quaternion::ToAxisAndAngle(Vector* const outAxis, float* const outAngle) const
{
	D3DXQUATERNION q(X, Y, Z, W);
	D3DXVECTOR3 v;
	D3DXQuaternionToAxisAngle(&q, &v, outAngle);
	outAxis->Set(v.x, v.y, v.z);
}

Vector Quaternion::ToEuler() const
{
	D3DXVECTOR3 result;
	D3DXMATRIX dm;
	D3DXQUATERNION dq(X, Y, Z, W);
	D3DXMatrixRotationQuaternion(&dm, &dq);
	result.x = std::atan2f(dm._32, dm._33);
	result.y = std::asinf(-dm._31);
	result.z = std::atan2f(dm._21, dm._11);
	return Vector(result.x, result.y, result.z);
}

std::wstring Quaternion::ToString() const
{
	TCHAR result[64]{};
	Vector euler = ToEuler();
	_sntprintf(result, sizeof(result), _T("(%.3f, %.3f, %.3f)"), euler.X, euler.Y, euler.Z);
	return result;
}

Quaternion Quaternion::operator+(const Quaternion& q) const
{
	return Quaternion(X + q.X, Y + q.Y, Z + q.Z, W + q.W);
}

Quaternion Quaternion::operator-(const Quaternion& q) const
{
	return Quaternion(X - q.X, Y - q.Y, Z - q.Z, W - q.W);
}

Quaternion Quaternion::operator*(const float scale) const
{
	return Quaternion(X * scale, Y * scale, Z * scale, W * scale);
}

Quaternion Quaternion::operator*(const Quaternion& q) const
{
	D3DXQUATERNION result;
	D3DXQUATERNION dq1(X, Y, Z, W);
	D3DXQUATERNION dq2(q.X, q.Y, q.Z, q.W);
	D3DXQuaternionMultiply(&result, &dq1, &dq2);
	return Quaternion(result.x, result.y, result.z, result.w);
}

Vector Quaternion::operator*(const Vector& v) const
{
	D3DXVECTOR3 result;
	D3DXMATRIX dm;
	D3DXQUATERNION dq(X, Y, Z, W);
	D3DXVECTOR3 dv(v.X, v.Y, v.Z);
	D3DXMatrixRotationQuaternion(&dm, &dq);
	D3DXVec3TransformCoord(&result, &dv, &dm);
	return Vector(result.x, result.y, result.z);
}

Quaternion Quaternion::operator/(const float scale) const
{
	return Quaternion(*this) /= scale;
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
	D3DXQUATERNION dq1(X, Y, Z, W);
	D3DXQUATERNION dq2(q.X, q.Y, q.Z, q.W);
	D3DXQuaternionMultiply(&result, &dq1, &dq2);
	X = result.x;
	Y = result.y;
	Z = result.z;
	W = result.w;
	return *this;
}

Quaternion Quaternion::operator/=(const float scale)
{
	float fInv = 1.f / scale;
	X *= fInv;
	Y *= fInv;
	Z *= fInv;
	W *= fInv;
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
