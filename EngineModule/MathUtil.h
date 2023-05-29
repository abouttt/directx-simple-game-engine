#pragma once

#include "pch.h"

// ��ó : https://github.com/onlybooks/gamemath/blob/main/Source/Runtime/Math/Public/MathUtil.h

struct Math
{
	static constexpr float PI = { 3.14159265358979323846f };
	static constexpr float TwoPI = { 2.f * PI };
	static constexpr float HalfPI = { 1.57079632679f };
	static constexpr float InvPI = { 0.31830988618f };
	static constexpr float SMALL_NUMBER = (1.e-8f);

	inline static constexpr int TruncToInt(float value)
	{
		return (int)value;
	}

	inline static constexpr int RountToInt(float value)
	{
		return TruncToInt(roundf(value));
	}

	inline static constexpr int FloorToInt(float value)
	{
		return TruncToInt(floorf(value));
	}

	inline static int CeilToInt(float value)
	{
		return TruncToInt(ceilf(value));
	}

	inline static constexpr bool EqualsInTolerance(float value1, float value2, float tolerance = SMALL_NUMBER)
	{
		return Math::Abs(value1 - value2) <= tolerance;
	}

	template< class T>
	inline static constexpr T Lerp(const T& src, const T& dest, float alpha)
	{
		return (T)(src + alpha * (dest - src));
	}

	template<class T>
	inline static constexpr T Square(const T num)
	{
		return num * num;
	}

	inline static constexpr float Deg2Rad(float degree)
	{
		return degree * PI / 180.f;
	}

	inline static constexpr float Rad2Deg(float radian)
	{
		return radian * 180.f * InvPI;
	}

	template<class T>
	inline static constexpr T Max(const T a, const T b)
	{
		return (a >= b) ? a : b;
	}

	template<class T>
	inline static constexpr T Min(const T a, const T b)
	{
		return (a <= b) ? a : b;
	}

	template< class T >
	inline static T constexpr Max3(const T a, const T b, const T c)
	{
		return Max(Max(a, b), c);
	}

	template< class T >
	inline static T constexpr Min3(const T a, const T b, const T c)
	{
		return Min(Min(a, b), c);
	}

	template<class T>
	inline static constexpr T Abs(const T a)
	{
		return (a >= (T)0) ? a : -a;
	}

	template<class T>
	inline static constexpr T Clamp(const T x, const T min, const T max)
	{
		return x < min ? min : x < max ? x : max;
	}

	// �𸮾� ���� �ڵ忡�� ������. ������ ������ ���� �� �ﰢ�Լ��� �Բ� �������� �Լ�. 
	static inline constexpr void GetSinCosRad(float* const outSin, float* const outCos, float radian)
	{
		// Copied from UE4 Source Code
		// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
		float quotient = (InvPI * 0.5f) * radian;
		if (radian >= 0.0f)
		{
			quotient = (float)((int)(quotient + 0.5f));
		}
		else
		{
			quotient = (float)((int)(quotient - 0.5f));
		}
		float y = radian - (2.0f * PI) * quotient;

		// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
		float sign = 0.f;
		if (y > HalfPI)
		{
			y = PI - y;
			sign = -1.0f;
		}
		else if (y < -HalfPI)
		{
			y = -PI - y;
			sign = -1.0f;
		}
		else
		{
			sign = +1.0f;
		}

		float y2 = y * y;

		// 11-degree minimax approximation
		*outSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

		// 10-degree minimax approximation
		float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
		*outCos = sign * p;
	}


	static inline constexpr void GetSinCos(float* const outSin, float* const outCos, float degree)
	{
		if (degree == 0.f)
		{
			*outSin = 0.f;
			*outCos = 1.f;
		}
		else if (degree == 90.f)
		{
			*outSin = 1.f;
			*outCos = 0.f;
		}
		else if (degree == 180.f)
		{
			*outSin = 0.f;
			*outCos = -1.f;
		}
		else if (degree == 270.f)
		{
			*outSin = -1.f;
			*outCos = 0.f;
		}
		else
		{
			GetSinCosRad(outSin, outCos, Math::Deg2Rad(degree));
		}
	}

	inline static float FMod(float x, float y)
	{
		if (fabsf(y) <= SMALL_NUMBER)
		{
			return 0.f;
		}

		const float quotient = (float)TruncToInt(x / y);
		float intPortion = y * quotient;
		if (fabsf(intPortion) > fabsf(x))
		{
			intPortion = x;
		}

		return (x - intPortion);
	}

	// �𸮾� ���� �ڵ忡�� ������. ��� �������� ����
	inline static float InvSqrt(float value)
	{
		// Performs two passes of Newton-Raphson iteration on the hardware estimate
		//    v^-0.5 = x
		// => x^2 = v^-1
		// => 1/(x^2) = v
		// => F(x) = x^-2 - v
		//    F'(x) = -2x^-3

		//    x1 = x0 - F(x0)/F'(x0)
		// => x1 = x0 + 0.5 * (x0^-2 - Vec) * x0^3
		// => x1 = x0 + 0.5 * (x0 - Vec * x0^3)
		// => x1 = x0 + x0 * (0.5 - 0.5 * Vec * x0^2)
		//
		// This final form has one more operation than the legacy factorization (X1 = 0.5*X0*(3-(Y*X0)*X0)
		// but retains better accuracy (namely InvSqrt(1) = 1 exactly).

		const __m128 fOneHalf = _mm_set_ss(0.5f);
		__m128 Y0, X0, X1, X2, FOver2;
		float temp;

		Y0 = _mm_set_ss(value);
		X0 = _mm_rsqrt_ss(Y0);	// 1/sqrt estimate (12 bits)
		FOver2 = _mm_mul_ss(Y0, fOneHalf);

		// 1st Newton-Raphson iteration
		X1 = _mm_mul_ss(X0, X0);
		X1 = _mm_sub_ss(fOneHalf, _mm_mul_ss(FOver2, X1));
		X1 = _mm_add_ss(X0, _mm_mul_ss(X0, X1));

		// 2nd Newton-Raphson iteration
		X2 = _mm_mul_ss(X1, X1);
		X2 = _mm_sub_ss(fOneHalf, _mm_mul_ss(FOver2, X2));
		X2 = _mm_add_ss(X1, _mm_mul_ss(X1, X2));

		_mm_store_ss(&temp, X2);
		return temp;
	}
};