#include "pch.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "Vector.h"

const Matrix Matrix::Identity({ 1.f, 0.f, 0.f, 0.f,
								0.f, 1.f, 0.f, 0.f,
								0.f, 0.f, 1.f, 0.f,
								0.f, 0.f, 0.f, 1.f });

Matrix::Matrix(const Matrix& m)
{
	memcpy(&M, &m.M, sizeof(Matrix));
}

Matrix::Matrix(float _11, float _12, float _13, float _14,
	float _21, float _22, float _23, float _24,
	float _31, float _32, float _33, float _34,
	float _41, float _42, float _43, float _44)
{
	memcpy(&_11, &M, sizeof(Matrix));
}

float Matrix::GetDeterminant() const
{
	D3DXMATRIX result;
	memcpy(&result, this, sizeof(Matrix));
	return D3DXMatrixDeterminant(&result);
}

Matrix Matrix::GetTranspose() const
{
	Matrix result;
	D3DXMATRIX out, dm;
	memcpy(&dm, this, sizeof(Matrix));
	D3DXMatrixTranspose(&out, &dm);
	memcpy(&result, &out, sizeof(Matrix));
	return result;
}

Matrix Matrix::GetInverse() const
{
	Matrix result;
	D3DXMATRIX out, dm;
	memcpy(&dm, this, sizeof(Matrix));
	float det = GetDeterminant();
	D3DXMatrixInverse(&out, &det, &dm);
	memcpy(&result, &out, sizeof(Matrix));
	return result;
}

void Matrix::SetIdentity()
{
	*this = Identity;
}

std::vector<tstring> Matrix::ToString() const
{
	std::vector<tstring> result;
	Matrix trMatrix = this->GetTranspose();
	for (BYTE i = 0; i < 4; ++i)
	{
		TCHAR row[64];
		_sntprintf(row, sizeof(row), _T("| %.3f , %.3f , %.3f, %.3f |"), trMatrix.M[i][0], trMatrix.M[i][1], trMatrix.M[i][2], trMatrix.M[i][3]);
		result.emplace_back(row);
	}
	return result;
}

Matrix Matrix::operator+(const Matrix& m) const
{
	Matrix result(*this);
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			result.M[row][col] += m.M[row][col];
		}
	}
	return result;
}

Matrix Matrix::operator-(const Matrix& m) const
{
	return Matrix(*this) += m;
}

Matrix Matrix::operator*(const Matrix& m) const
{
	return Matrix(*this) *= m;
}

Matrix Matrix::operator*(const float scalar) const
{
	return Matrix(*this) *= scalar;
}

Matrix Matrix::operator/(const float scalar) const
{
	return Matrix(*this) /= scalar;
}

Matrix& Matrix::operator+=(const Matrix& m)
{
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			M[row][col] += m.M[row][col];
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& m)
{
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			M[row][col] -= m.M[row][col];
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& m)
{
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			M[row][col] *= m.M[row][col];
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const float scalar)
{
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			M[row][col] *= scalar;
		}
	}
	return *this;
}

Matrix& Matrix::operator/=(const float scalar)
{
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			M[row][col] /= scalar;
		}
	}
	return *this;
}

bool Matrix::operator==(const Matrix& m) const
{
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			if (M[row][col] != m.M[row][col])
			{
				return false;
			}
		}
	}
	return true;
}

bool Matrix::operator!=(const Matrix& m) const
{
	return !(*this == m);
}
