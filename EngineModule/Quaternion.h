#pragma once

#include "MathUtil.h"

const D3DXQUATERNION QUATERNION_IDENTITY = D3DXQUATERNION(0.f, 0.f, 0.f, 1.f);

inline D3DXVECTOR3 operator*(const D3DXQUATERNION& q, const D3DXVECTOR3& v)
{
	D3DXQUATERNION q1(-q.x, -q.y, -q.z, q.w);
	D3DXQUATERNION q2 = q1 * D3DXQUATERNION(v.x, v.y, v.z, 1.f) * q;
	return D3DXVECTOR3(q2.x, q2.y, q2.z);
}

inline D3DXVECTOR3 QuaternionToEuler(const D3DXQUATERNION& q)
{
	D3DXVECTOR3 result;

	float sinrCosp = 2 * (q.w * q.z + q.x * q.y);
	float cosrCosp = 1 - 2 * (q.z * q.z + q.x * q.x);
	result.z = D3DXToDegree(atan2f(sinrCosp, cosrCosp));

	float pitchTest = q.w * q.x - q.y * q.z;
	float asinThreshold = 0.4999995f;
	if (pitchTest < -asinThreshold)
	{
		result.x = -90;
	}
	else if (pitchTest > asinThreshold)
	{
		result.x = 90;
	}
	else
	{
		float sinp = 2 * pitchTest;
		result.x = D3DXToDegree(asinf(sinp));
	}

	float sinyCosp = 2 * (q.w * q.y + q.x * q.z);
	float cosyCosp = 1.f - 2 * (q.x * q.x + q.y * q.y);
	result.y = D3DXToDegree(atan2f(sinyCosp, cosyCosp));

	return result;

	//float sqx = q.x * q.x;
	//float sqy = q.y * q.y;
	//float sqz = q.z * q.z;
	//float sqw = q.w * q.w;


	/*result.x = atan2f(2 * (q.y * q.z + q.x * q.w), (-sqx - sqy + sqz + sqw));
	result.y = asinf(-2 * (q.x * q.z - q.y * q.w));
	result.z = atan2f(2 * (q.x * q.y + q.z * q.w), (sqx - sqy - sqz + sqw));*/

	/*result.x = asinf(2 * (q.w * q.x - q.y * q.z));
	result.y = atan2f(2 * (q.x * q.z + q.w * q.y), (-sqx - sqy + sqz + sqw));
	result.z = atan2f(2 * (q.x * q.y + q.w * q.z), (-sqx + sqy - sqz + sqw));*/
}