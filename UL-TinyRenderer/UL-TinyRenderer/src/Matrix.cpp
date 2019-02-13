#include "Matrix.h"

Matrix::Matrix(int rows, int columns)
{
	m_columns = columns;
	m_rows = rows;
	m_matrix = std::vector<float>(columns * rows);
	std::fill(m_matrix.begin(), m_matrix.end(), 0.0f);
}

Matrix::Matrix(Vector3 vec)
{
	m_columns = 1;
	m_rows = 4;
	m_matrix = std::vector<float>(4);
	m_matrix[0] = vec.GetX();
	m_matrix[1] = vec.GetY();
	m_matrix[2] = vec.GetZ();
	m_matrix[3] = 1.0f;
}

void Matrix::Set(int row, int column, float value)
{
	m_matrix[column * m_rows + row] = value;
}

float Matrix::Get(int row, int column)
{
	return m_matrix[column * m_rows + row];
}

int Matrix::GetColumns()
{
	return m_columns;
}

int Matrix::GetRows()
{
	return m_rows;
}

Vector3 Matrix::ToVector3()
{
	return Vector3(m_matrix[0] / m_matrix[3], m_matrix[1] / m_matrix[3], m_matrix[2] / m_matrix[3]);
}

Matrix Matrix::Identity(int size)
{
	Matrix m(size, size);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == j)
			{
				m.Set(i, j, 1);
			}
			else
			{
				m.Set(i, j, 0);
			}
		}
	}

	return m;
}

Matrix Matrix::operator+(Matrix & other)
{
	if (m_columns == other.GetColumns() && m_rows == other.GetRows())
	{
		Matrix res(m_rows, m_columns);

		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < m_columns; j++)
			{
				res.Set(i, j, this->Get(i, j) + other.Get(i, j));
			}
		}

		return res;
	}
}

Matrix Matrix::operator*(float coef)
{
	Matrix res(m_rows, m_columns);

	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_columns; j++)
		{
			res.Set(i, j, this->Get(i, j) * coef);
		}
	}

	return res;
}

Matrix Matrix::operator*(Matrix& other)
{
	if (m_columns == other.GetRows())
	{
		Matrix res(m_rows, other.GetColumns());

		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < other.GetColumns(); j++)
			{
				float value = 0.0f;

				for (int k = 0; k < m_columns; k++)
				{
					value += (this->Get(i, k) * other.Get(k, j));
				}

				res.Set(i, j, value);
			}
		}
		return res;
	}
}
