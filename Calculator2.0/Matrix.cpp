#include "Matrix.h"
#include "Exception.h"

Matrix::Matrix(int rows, int cols, std::vector<std::vector<double>>* data) : rows(rows), cols(cols), data(*data)
{
    type = CalcType::Matrix;
}

void Matrix::Print()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            std::cout << data[i][j] << " ";
        std::cout << std::endl;
    }
}

Calculable* Matrix::Plus(Calculable* b)
{
    if (b->GetType() == CalcType::Matrix)
    {
        Matrix* matrix_b = dynamic_cast<Matrix*>(b);
        if (matrix_b->rows != rows || matrix_b->cols != cols)
        {
            throw new Exception(ExceptionType::SIZE_EXCEPTION);
        }
        else
        {
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    data[i][j] += matrix_b->data[i][j];
                }
            }
            return new Matrix(rows, cols, &data);
        }
    }
    else if (b->GetType() == CalcType::RealNumber)
    {
        double real_b = dynamic_cast<RealNumber*>(b)->GetValue();
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                data[i][j] += real_b;
            }
        }
        return new Matrix(rows, cols, &data);
    }
    throw new Exception(ExceptionType::FORMULA_EXCEPTION);
}

Calculable* Matrix::Minus(Calculable* b)
{
    if (b->GetType() == CalcType::Matrix)
    {
        Matrix* matrix_b = dynamic_cast<Matrix*>(b);
        if (matrix_b->rows != rows || matrix_b->cols != cols)
        {
            throw new Exception(ExceptionType::SIZE_EXCEPTION);
        }
        else
        {
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    data[i][j] -= matrix_b->data[i][j];
                }
            }
            return new Matrix(rows, cols, &data);
        }
    }
    else if (b->GetType() == CalcType::RealNumber)
    {
        double real_b = dynamic_cast<RealNumber*>(b)->GetValue();
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                data[i][j] -= real_b;
            }
        }
        return new Matrix(rows, cols, &data);
    }
    throw new Exception(ExceptionType::FORMULA_EXCEPTION);
}

Calculable* Matrix::Multiplication(Calculable* b)
{
    if (b->GetType() == CalcType::Matrix)
    {
        Matrix* matrix_b = dynamic_cast<Matrix*>(b);
        if (cols != matrix_b->rows)
        {
            throw new Exception(ExceptionType::SIZE_EXCEPTION);
        }
        std::vector<std::vector<double>> new_data(rows, std::vector<double>(matrix_b->cols, 0));

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < matrix_b->cols; j++)
            {
                for (int k = 0; k < cols; k++)
                {
                    new_data[i][j] += data[i][k] * matrix_b->data[k][j];
                }
            }
        }
        return new Matrix(rows, matrix_b->cols, &new_data);
    }
    else if (b->GetType() == CalcType::RealNumber)
    {
        Matrix* matrix_b = new Matrix(rows, cols, &data);
        int x = dynamic_cast<RealNumber*>(b)->GetValue();
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                matrix_b->data[i][j] *= x;
            }
        }
        return matrix_b;
    }
    throw new Exception(ExceptionType::FORMULA_EXCEPTION);
}

Calculable* Matrix::Division(Calculable* b)
{
    if (b->GetType() == CalcType::RealNumber)
    {
        double divisor = dynamic_cast<RealNumber*>(b)->GetValue();
        if (divisor == 0)
        {
            throw new Exception(ExceptionType::ZERO_DIVISION);
        }
        Matrix* result = new Matrix(rows, cols, &data);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                result->data[i][j] /= divisor;
            }
        }
        return result;
    }
    else if (b->GetType() == type)
    {
        throw new Exception(ExceptionType::MATRIX_DIVISION);
    }
    throw new Exception(ExceptionType::FORMULA_EXCEPTION);
}

Calculable* Matrix::Exponentiation(Calculable* b)
{
    if (b->GetType() == CalcType::RealNumber)
    {
        Matrix* matrix_b = new Matrix(rows, cols, &data);
        double exponent = dynamic_cast<RealNumber*>(b)->GetValue();
        if (floor(exponent) != exponent || exponent < 0)
        {
            throw new Exception(ExceptionType::EXPONENTIATION_EXCEPTION);
        }
        else
        {
            Matrix* result = new Matrix(rows, cols, &data);
            if (exponent == 0)
            {
                for (int i = 0; i < rows; i++)
                {
                    for (int j = 0; j < cols; j++)
                    {
                        if (i == j)
                            result->data[i][j] = 1;
                        else
                            result->data[i][j] = 0;
                    }
                }
            }
            else
            {
                for (int i = 1; i < exponent; i++)
                {
                    result = dynamic_cast<Matrix*>(result->Multiplication(this));
                }
            }
            return result;
        }
    }
    throw new Exception(ExceptionType::FORMULA_EXCEPTION);
}



