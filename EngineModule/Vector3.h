#pragma once

#include "MathUtil.h"

const D3DXVECTOR3 VECTOR3_ZERO = D3DXVECTOR3(0.f, 0.f, 0.f);
const D3DXVECTOR3 VECTOR3_ONE = D3DXVECTOR3(1.f, 1.f, 1.f);
const D3DXVECTOR3 VECTOR3_FORWARD = D3DXVECTOR3(0.f, 0.f, 1.f);
const D3DXVECTOR3 VECTOR3_BACKWARD = D3DXVECTOR3(0.f, 0.f, -1.f);
const D3DXVECTOR3 VECTOR3_UP = D3DXVECTOR3(0.f, 1.f, 0.f);
const D3DXVECTOR3 VECTOR3_DOWN = D3DXVECTOR3(0.f, -1.f, 0.f);
const D3DXVECTOR3 VECTOR3_RIGHT = D3DXVECTOR3(1.f, 0.f, 0.f);
const D3DXVECTOR3 VECTOR3_LEFT = D3DXVECTOR3(-1.f, 0.f, 0.f);

inline D3DXVECTOR3 operator*(const D3DXVECTOR3& v1, const D3DXVECTOR3& v2)
{
	return D3DXVECTOR3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

inline D3DXVECTOR3 operator*(const D3DXVECTOR3& v, const D3DXQUATERNION& q)
{
	D3DXQUATERNION q1(-q.x, -q.y, -q.z, q.w);
	D3DXQUATERNION q2 = q1 * D3DXQUATERNION(v.x, v.y, v.z, 1.f) * q;
	return D3DXVECTOR3(q2.x, q2.y, q2.z);
}

inline D3DXQUATERNION EulerToQuaternion(const D3DXVECTOR3& v)
{
	float sp = 0.f, sy = 0.f, sr = 0.f;
	float cp = 0.f, cy = 0.f, cr = 0.f;

	Math::GetSinCos(&sp, &cp, v.x * 0.5f);
	Math::GetSinCos(&sy, &cy, v.y * 0.5f);
	Math::GetSinCos(&sr, &cr, v.z * 0.5f);

	D3DXQUATERNION q;
	q.w = sy * sp * sr + cy * cp * cr;
	q.x = sy * sr * cp + sp * cy * cr;
	q.y = sy * cp * cr - sp * sr * cy;
	q.z = -sy * sp * cr + sr * cy * cp;
	return q;
}