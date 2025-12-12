#include "Matrices.h"

namespace Matrices
{
    Matrix::Matrix(int _rows, int _cols)
    {
        rows = _rows;
        cols = _cols;
        a.resize(rows);

        for (int i = 0; i < rows; ++i)
        {
            a[i].resize(cols, 0);
        }
    }

    Matrix operator+(const Matrix& a, const Matrix& b)
    {

        if (a.getRows() != b.getRows())
        {
            throw runtime_error("Error: dimensions must agree");
        }

        Matrix result(a.getRows(), a.getCols());

        for (int i = 0; i < a.getRows(); ++i)
        {
            for (int j = 0; j < a.getCols(); ++j)
            {
                result(i, j) = a(i, j) + b(i, j);
            }
        }

        return result;
    }

    Matrix operator*(const Matrix& a, const Matrix& b)
    {
        if (a.getCols() != b.getRows())
        {
            throw runtime_error("Error: dimensions must agree");
        }

        Matrix result(a.getRows(), b.getCols());

        for (int k = 0; k < b.getCols(); ++k)
        {
            for (int i = 0; i < a.getRows(); ++i)
            {
                for (int j = 0; j < a.getCols(); ++j)
                {
                    result(i, k) += a(i, j) * b(j, k);
                }
            }
        }

        return result;
    }

    bool operator==(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
        {

            return false;
        }

        for (int i = 0; i < a.getRows(); ++i)
        {
            for (int j = 0; j < a.getCols(); ++j)
            {
                if (abs(a(i, j) - b(i, j)) >= 0.001)
                {
                    return false;
                }
            }
        }

        return true;

    }

    bool operator!=(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
        {
            return true;
        }

        for (int i = 0; i < a.getRows(); ++i)
        {
            for (int j = 0; j < a.getRows(); ++j)
            {
                if (abs(a(i, j) - b(i, j)) >= 0.001)
                {
                    return true;
                }
            }
        }

        return false;
    }

    ostream& operator<<(ostream& os, const Matrix& a)
    {
        for (int i = 0; i < a.getRows(); ++i)
        {
            for (int j = 0; j < a.getCols(); ++j)
            {
                os << setw(10) << a(i, j) << " ";
            }
            os << "\n";
        }

        return os;
    }

	TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) 
		: Matrix(2, nCols)
	{
		for (int i = 0; i < nCols; i++)
		{
			a.at(0).at(i) = xShift;
			a.at(1).at(i) = yShift;
		}
	}

	RotationMatrix::RotationMatrix(double theta) 
        : Matrix(2, 2)
	{
		a.at(0).at(0) = cos(theta);
		a.at(0).at(1) = -sin(theta);
		a.at(1).at(0) = sin(theta);
		a.at(1).at(1) = cos(theta);
	}

	ScalingMatrix::ScalingMatrix(double scale) 
        : Matrix(2, 2)
	{
		a.at(0).at(0) = scale;
		a.at(1).at(1) = scale;
	}
}