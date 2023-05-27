#include "pch.h"
#include "MathUtil.h"
#include "Quaternion.h"
#include "Vector.h"

const Vector Vector::Backward = Vector(0.f, 0.f, -1.f);
const Vector Vector::Down = Vector(0.f, -1.f, 0.f);
const Vector Vector::Forward = Vector(0.f, 0.f, 1.f);
const Vector Vector::Left = Vector(-1.f, 0.f, 0.f);
const Vector Vector::One = Vector(1.f, 1.f, 1.f);
const Vector Vector::Right = Vector(1.f, 0.f, 0.f);
const Vector Vector::Up = Vector(0.f, 1.f, 0.f);
const Vector Vector::Zero = Vector(0.f, 0.f, 0.f);

Vector::Vector()
	: X(0.f)
	, Y(0.f)
	, Z(0.f)
{
}

Vector::Vector(float x, float y, float z)
	: X(x)
	, Y(y)
	, Z(z)
{
}

float Vector::Angle(const Vector& v1, const Vector& v2)
{
	float length = std::sqrtf(v1.GetSizeSq() * v2.GetSizeSq());
	float dot = Dot(v1, v2);
	float cosAngle = std::acosf(dot / length);
	cosAngle = Math::Rad2Deg(cosAngle);
	return (v1.X * v2.Y - v1.Y * v2.X > 0.0f) ? cosAngle : -cosAngle;
}

Vector Vector::Cross(const Vector& v1, const Vector& v2)
{
	return Vector(
		v1.Y * v2.Z - v1.Z * v2.Y,
		v1.Z * v2.X - v1.X * v2.Z,
		v1.X * v2.Y - v1.Y * v2.X);
}

float Vector::Distance(const Vector& v1, const Vector& v2)
{
	return std::sqrtf(DistanceSq(v1, v2));
}

float Vector::DistanceSq(const Vector& v1, const Vector& v2)
{
	float xLength = v2.X - v1.X;
	float yLength = v2.Y - v1.Y;
	float zLength = v2.Z - v1.Z;
	return (xLength * xLength) + (yLength * yLength) + (zLength * zLength);
}

float Vector::Dot(const Vector& v1, const Vector& v2)
{
	return (v1.X * v2.X) + (v1.Y * v2.Y) + (v1.Z * v2.Z);
}

Vector Vector::Lerp(const Vector& v1, const Vector& v2, float t)
{
	D3DXVECTOR3 result;
	D3DXVECTOR3 dv1(v1.X, v1.Y, v1.Z);
	D3DXVECTOR3 dv2(v2.X, v2.Y, v2.Z);
	D3DXVec3Lerp(&result, &dv1, &dv2, t);
	return Vector(result.x, result.y, result.z);
}

Vector Vector::GetAbs() const
{
	return Vector(Math::Abs(X), Math::Abs(Y), Math::Abs(Z));
}

float Vector::GetSize() const
{
	return std::sqrtf(GetSizeSq());
}

float Vector::GetSizeSq() const
{
	return (X * X) + (Y * Y) + (Z * Z);
}

float Vector::GetMax() const
{
	float max = Math::Max(X, Y);
	return Math::Max(max, Z);
}

float Vector::GetMin() const
{
	float min = Math::Min(X, Y);
	return Math::Min(min, Z);
}

Vector Vector::GetNormalize() const
{
	float sizeSq = GetSizeSq();
	if (sizeSq == 1.f)
	{
		return *this;
	}
	else if (sizeSq == 0.f)
	{
		return Vector::Zero;
	}

	float invLength = Math::InvSqrt(sizeSq);
	return Vector(X * invLength, Y * invLength, Z * invLength);
}

void Vector::Normalize()
{
	*this = GetNormalize();
}

void Vector::Set(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

std::wstring Vector::ToString()
{
	TCHAR result[64]{};
	_sntprintf(result, sizeof(result), _T("(%.3f, %.3f, %.3f)"), X, Y, Z);
	return result;
}

Vector Vector::operator+(const Vector& v) const
{
	return Vector(X + v.X, Y + v.Y, Z + v.Z);
}

Vector Vector::operator+(const float bias) const
{
	return Vector(X + bias, Y + bias, Z + bias);
}

Vector Vector::operator-() const
{
	return Vector(-X, -Y, -Z);
}

Vector Vector::operator-(const Vector& v) const
{
	return Vector(X - v.X, Y - v.Y, Z - v.Z);
}

Vector Vector::operator-(const float bias) const
{
	return Vector(X - bias, Y - bias, Z - bias);
}

Vector Vector::operator*(const float scale) const
{
	return Vector(X * scale, Y * scale, Z * scale);
}

Vector Vector::operator*(const Vector& v) const
{
	return Vector(X * v.X, Y * v.Y, Z * v.Z);
}

Vector Vector::operator*(const Quaternion& q) const
{
	Quaternion q1 = q.GetInverse();
	Quaternion q2 = q1 * Quaternion(X, Y, Z, 1.f) * q;
	return Vector(q2.X, q2.Y, q2.Z);
}

Vector Vector::operator/(const float scale) const
{
	return Vector(X / scale, Y / scale, Z / scale);
}

Vector Vector::operator/(const Vector& v) const
{
	return Vector(X / v.X, Y / v.Y, Z / v.Z);
}

Vector Vector::operator+=(const Vector& v)
{
	X += v.X;
	Y += v.Y;
	Z += v.Z;
	return *this;
}

Vector Vector::operator-=(const Vector& v)
{
	X -= v.X;
	Y -= v.Y;
	Z -= v.Z;
	return *this;
}

Vector Vector::operator*=(const float scale)
{
	X *= scale;
	Y *= scale;
	Z *= scale;
	return *this;
}

Vector Vector::operator*=(const Vector& v)
{
	X *= v.X;
	Y *= v.Y;
	Z *= v.Z;
	return *this;
}

Vector Vector::operator/=(const float scale)
{
	X /= scale;
	Y /= scale;
	Z /= scale;
	return *this;
}

Vector Vector::operator/=(const Vector& v)
{
	X /= v.X;
	Y /= v.Y;
	Z /= v.Z;
	return *this;
}

bool Vector::operator==(const Vector& v) const
{
	float xAbs = Math::Abs(X - v.X);
	float yAbs = Math::Abs(Y - v.Y);
	float zAbs = Math::Abs(Z - v.Z);
	return (xAbs <= FLT_EPSILON && yAbs <= FLT_EPSILON && zAbs <= FLT_EPSILON);
}

bool Vector::operator!=(const Vector& v) const
{
	return !(*this == v);
}
