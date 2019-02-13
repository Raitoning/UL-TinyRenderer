#pragma once

#include <vector>
#include "Vector3.h"

class Matrix
{
private:
	int m_columns;
	int m_rows;
	std::vector<float> m_matrix;

public:
	Matrix(int rows, int columns);
	Matrix(Vector3 vec);
	void Set(int row, int column, float value);
	float Get(int row, int column);
	int GetColumns();
	int GetRows();
	Vector3 ToVector3();
	static Matrix Identity(int size);

	Matrix operator+ (Matrix& other);
	Matrix operator* (float coef);
	Matrix operator* (Matrix& other);
};
