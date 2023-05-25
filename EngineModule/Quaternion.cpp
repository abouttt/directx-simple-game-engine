#include "pch.h"
#include "MathUtil.h"
#include "Quaternion.h"
#include "Vector.h"

const Quaternion Quaternion::Identity = Quaternion(0.f, 0.f, 0.f, 1.f);

Quaternion::Quaternion(float x, float y, float z, float w)
	: X(x)
	, Y(y)
	, Z(z)
	, W(w)
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
	Vector result;

	float sinrCosp = 2 * (W * Z + X * Y);
	float cosrCosp = 1 - 2 * (Z * Z + X * X);
	result.Z = Math::Rad2Deg(atan2f(sinrCosp, cosrCosp));

	float pitchTest = W * X - Y * Z;
	float asinThreshold = 0.4999995f;
	if (pitchTest < -asinThreshold)
	{
		result.X = -90;
	}
	else if (pitchTest > asinThreshold)
	{
		result.X = 90;
	}
	else
	{
		float sinp = 2 * pitchTest;
		result.X = Math::Rad2Deg(asinf(sinp));
	}

	float sinyCosp = 2 * (W * Y + X * Z);
	float cosyCosp = 1.f - 2 * (X * X + Y * Y);
	result.Y = Math::Rad2Deg(atan2f(sinyCosp, cosyCosp));

	return result;
}

Vector Quaternion::GetAxisX() const
{
	float cy = 0.f, sy = 0.f, cp = 0.f, sp = 0.f, cr = 0.f, sr = 0.f;
	Math::GetSinCos(&sy, &cy, Y);
	Math::GetSinCos(&sp, &cp, X);
	Math::GetSinCos(&sr, &cr, Z);
	return Vector(cy * cr + sy * sp * sr, cp * sr, -sy * cr + cy * sp * sr);
}

Vector Quaternion::GetAxisY() const
{
	float cy = 0.f, sy = 0.f, cp = 0.f, sp = 0.f, cr = 0.f, sr = 0.f;
	Math::GetSinCos(&sy, &cy, Y);
	Math::GetSinCos(&sp, &cp, X);
	Math::GetSinCos(&sr, &cr, Z);
	return Vector(-cy * sr + sy * sp * cr, cp * cr, sy * sr + cy * sp * cr);
}

Vector Quaternion::GetAxisZ() const
{
	float cy = 0.f, sy = 0.f, cp = 0.f, sp = 0.f, cr = 0.f, sr = 0.f;
	Math::GetSinCos(&sy, &cy, Y);
	Math::GetSinCos(&sp, &cp, X);
	Math::GetSinCos(&sr, &cr, Z);
	return Vector(sy * cp, -sp, cy * cp);
}

void Quaternion::Normalize()
{
	*this = GetNormalize();
}

Quaternion Quaternion::GetNormalize() const
{
	Quaternion result;
	const float squareSum = X * X + Y * Y + Z * Z + W * W;
	if (squareSum >= Math::SMALL_NUMBER)
	{
		const float scale = 1.f / sqrtf(squareSum);

		result.X *= scale;
		result.Y *= scale;
		result.Z *= scale;
		result.W *= scale;
	}
	else
	{
		result = Quaternion::Identity;
	}

	return result;
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
	return Quaternion(X + q.X, Y + q.Y, Z + q.Z, W + q.W);
}

Quaternion Quaternion::operator-() const
{
	return Quaternion(-X, -Y, -Z, -W);
}

Quaternion Quaternion::operator-(const Quaternion& q) const
{
	return Quaternion(X - q.X, Y - q.Y, Z - q.Z, W - q.W);
}

Quaternion Quaternion::operator*(const Quaternion& q) const
{
	Quaternion result;
	Vector v1(X, Y, Z);
	Vector v2(q.X, q.Y, q.Z);
	result.W = W * q.W - Vector::Dot(v1, v2);
	Vector v = v2 * W + v1 * q.W + Vector::Cross(v1, v2);
	result.X = v.X;
	result.Y = v.Y;
	result.Z = v.Z;

	return result;
}

Vector Quaternion::operator*(const Vector& v) const
{
	Quaternion q(X, Y, Z, W);
	Quaternion q1, q2;
	q1 = q.Inverse();
	q2 = q1 * Quaternion(v.X, v.Y, v.Z, 1.0f) * q;
	return Vector(q2.X, q2.Y, q2.Z);
}

Quaternion Quaternion::operator/(const float scale) const
{
	D3DXQUATERNION result(X, Y, Z, W);
	result /= scale;
	return Quaternion(result.x, result.y, result.z, result.w);
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
	Vector v1(X, Y, Z), v2(q.X, q.Y, q.Z);
	W = W * q.W - Vector::Dot(v1, v2);
	Vector v = v2 * W + v1 * q.W + Vector::Cross(v1, v2);
	X = v.X;
	Y = v.Y;
	Z = v.Z;
	return *this;
}

Quaternion Quaternion::operator/=(const float scale)
{
	D3DXQUATERNION result(X, Y, Z, W);
	result /= scale;
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
