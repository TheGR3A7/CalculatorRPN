#include "RealNumber.h"
#include "Fraction.h"
#include "Matrix.h"
#include "Exception.h"

RealNumber::RealNumber(double v) : value(v) 
{
	type = CalcType::RealNumber;
}

void RealNumber::Print()
{
	std::cout << value;
}

double RealNumber::GetValue()
{
	return value;
}

Calculable* RealNumber::Plus(Calculable* b)
{
    if (type == b->GetType())
    {
        return new RealNumber(dynamic_cast<RealNumber*>(b)->GetValue() + value);
    }
    else if (b->GetType() == CalcType::Fraction)
    {
        Fraction* fraction_b = dynamic_cast<Fraction*>(b);
        double value_b = static_cast<double>(fraction_b->numerator) / static_cast<double>(fraction_b->denominator);
        return new RealNumber(value_b + value);
    }
    else if (b->GetType() == CalcType::Matrix)
    {
        Matrix* matrix_b = dynamic_cast<Matrix*>(b);
        int rows = matrix_b->rows;
        int cols = matrix_b->cols;
        std::vector<std::vector<double>> matrix_data = matrix_b->data;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                matrix_data[i][j] += this->value;
            }
        }
        return new Matrix(rows, cols, &matrix_data);
    }
    throw new Exception(ExceptionType::FORMULA_EXCEPTION);
}

Calculable* RealNumber::Minus(Calculable* b)
{
    if (type == b->GetType())
    {
        return  new RealNumber(value - dynamic_cast<RealNumber*>(b)->GetValue());
    }
    else if (b->GetType() == CalcType::Fraction)
    {
        Fraction* fraction_b = dynamic_cast<Fraction*>(b);
        double value_b = static_cast<double>(fraction_b->numerator) / static_cast<double>(fraction_b->denominator);
        return new RealNumber(value - value_b);
    }
    else if (b->GetType() == CalcType::Matrix)
    {
        Matrix* matrix_b = dynamic_cast<Matrix*>(b);
        int rows = matrix_b->rows;
        int cols = matrix_b->cols;
        std::vector<std::vector<double>> matrix_data = matrix_b->data;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                matrix_data[i][j] = this->value - matrix_data[i][j];
            }
        }
        return new Matrix(rows, cols, &matrix_data);
    }
    throw new Exception(ExceptionType::FORMULA_EXCEPTION);
}

Calculable* RealNumber::Multiplication(Calculable* b)
{
    if (type == b->GetType())
    {
        return new RealNumber(dynamic_cast<RealNumber*>(b)->GetValue() * value);
    }
    else if (b->GetType() == CalcType::Fraction)
    {
        Fraction* fraction_b = dynamic_cast<Fraction*>(b);
        double result = fraction_b->numerator * value / fraction_b->denominator;
        return new RealNumber(result);
    }
    else if (b->GetType() == CalcType::Matrix)
    {
        Matrix* matrix_b = dynamic_cast<Matrix*>(b);
        int rows = matrix_b->rows;
        int cols = matrix_b->cols;
        std::vector<std::vector<double>> matrix_data = matrix_b->data;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                matrix_data[i][j] *= this->value;
            }
        }
        return new Matrix(rows, cols, &matrix_data);
    }
    throw new Exception(ExceptionType::FORMULA_EXCEPTION);
}

Calculable* RealNumber::Division(Calculable* b)
{
    if (type == b->GetType())
    {
        double divisor = dynamic_cast<RealNumber*>(b)->GetValue();
        if (divisor == 0)
        {
            throw new Exception(ExceptionType::ZERO_DIVISION);
        }
        return new RealNumber(value / divisor);
    }
    else if (b->GetType() == CalcType::Fraction)
    {
        Fraction* fraction_b = dynamic_cast<Fraction*>(b);
        double value_b = static_cast<double>(fraction_b->numerator) / static_cast<double>(fraction_b->denominator);
        if (value_b == 0)
        {
            throw new Exception(ExceptionType::ZERO_DIVISION);
        }
        return new RealNumber(value / value_b);
    }
    throw new Exception(ExceptionType::FORMULA_EXCEPTION);
}

Calculable* RealNumber::Exponentiation(Calculable* b)
{
    if (type == b->GetType())
    {
        double exponent = dynamic_cast<RealNumber*>(b)->GetValue();
        if (floor(exponent) != exponent || exponent < 0)
        {
            throw new Exception(ExceptionType::EXPONENTIATION_EXCEPTION);
        }
        if (exponent == 0)
        {
            return new RealNumber(1);
        }
        return new RealNumber(pow(value, exponent));
    }
    else if (b->GetType() == CalcType::Fraction)
    {
        Fraction* fraction_b = dynamic_cast<Fraction*>(b);
        double value_b = pow(fraction_b->numerator, value) / pow(fraction_b->denominator, value);
        return new RealNumber(value_b);
    }
    throw new Exception(ExceptionType::FORMULA_EXCEPTION);
}


