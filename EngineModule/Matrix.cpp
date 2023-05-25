#include "pch.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "Vector.h"

const Matrix Matrix::Identity({ 1.f, 0.f, 0.f, 0.f,
								0.f, 1.f, 0.f, 0.f,
								0.f, 0.f, 1.f, 0.f,
								0.f, 0.f, 0.f, 1.f });

float Matrix::GetDeterminant() const
{
	D3DXMATRIX result(
		M[0][0], M[0][1], M[0][2], M[0][3],
		M[1][0], M[1][1], M[1][2], M[1][3],
		M[2][0], M[2][1], M[2][2], M[2][3],
		M[3][0], M[3][1], M[3][2], M[3][3]);
	return D3DXMatrixDeterminant(&result);
}

Matrix Matrix::GetTransposed() const
{
	Matrix result;
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			result.M[col][row] = M[row][col];
		}
	}
	return result;
}

Matrix Matrix::GetInverse() const
{
	Matrix result;
	D3DXMATRIX out, dm;
	std::copy(&M[0][0], &M[0][0] + 4 * 4, &dm.m[0][0]);
	float det = GetDeterminant();
	D3DXMatrixInverse(&out, &det, &dm);
	std::copy(&out.m[0][0], &out.m[0][0] + 4 * 4, &result.M[0][0]);
	return result;
}

void Matrix::SetIdentity()
{
	*this = Identity;
}

std::vector<tstring> Matrix::ToString() const
{
	std::vector<tstring> result;

	Matrix trMatrix = this->GetTransposed();
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
	Matrix result(*this);
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			result.M[row][col] -= m.M[row][col];
		}
	}
	return result;
}

Matrix Matrix::operator*(const Matrix& m) const
{
	Matrix result(*this);
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			result.M[row][col] *= m.M[row][col];
		}
	}
	return result;
}

Matrix Matrix::operator*(const float scalar) const
{
	Matrix result(*this);
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			result.M[row][col] *= scalar;
		}
	}
	return result;
}

Matrix Matrix::operator/(const float scalar) const
{
	Matrix result(*this);
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			result.M[row][col] /= scalar;
		}
	}
	return result;
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
