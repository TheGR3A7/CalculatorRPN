#include "Fraction.h"
#include "Exception.h"
#include <numeric>
#include <iostream>

void Fraction::Shorten()
{
    int gcd = std::gcd(abs(numerator), abs(denominator)); // gcd - мнд
    numerator /= gcd;
    denominator /= gcd;
}

Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator)
{
    type = CalcType::Fraction;
    if (denominator == 0)
    {
        throw new Exception(ExceptionType::ZERO_DIVISION);
    }
    if (denominator < 0)
    {
        numerator *= -1;
        denominator *= -1;
    }

    Shorten(); 
}

void Fraction::Print()
{
    Shorten();

    if (abs(numerator) < abs(denominator))
        std::cout << numerator << "/" << denominator;
    else
    {
        if (numerator == denominator)
            std::cout << 1;
        else
        {
            if (numerator % denominator == 0)
                std::cout << numerator / denominator;
            else
                std::cout << numerator / denominator << "[" << abs(numerator % denominator) << "/" << abs(denominator) << "]";
        }
    }
}

Calculable* Fraction::Plus(Calculable* b)
{
    if (b->GetType() == CalcType::Fraction)
    {
        Fraction* fraction_b = dynamic_cast<Fraction*>(b);
        if (fraction_b->denominator == 0)
        {
            throw new Exception(ExceptionType::ZERO_DIVISION);
        }

        int common_denominator = std::lcm(denominator, fraction_b->denominator); // lcm - мнй

        int sum_numerator = numerator * (common_denominator / denominator) + fraction_b->numerator * (common_denominator / fraction_b->denominator);

        return new Fraction(sum_numerator, common_denominator);
    }
    else if (b->GetType() == CalcType::RealNumber)
    {
        RealNumber* real_b = dynamic_cast<RealNumber*>(b);
        double value_b = real_b->GetValue();
        double result = static_cast<double>(numerator) / denominator + value_b;
        return new RealNumber(result);
    }
    throw new Exception(ExceptionType::FORMULA_EXCEPTION);
}

Calculable* Fraction::Minus(Calculable* b)
{
    if (b->GetType() == CalcType::Fraction)
    {
        Fraction* fraction_b = dynamic_cast<Fraction*>(b);
        if (fraction_b->denominator == 0)
        {
            throw new Exception(ExceptionType::ZERO_DIVISION);
        }

        int common_denominator = std::lcm(denominator, fraction_b->denominator);

        int diff_numerator = numerator * (common_denominator / denominator) - fraction_b->numerator * (common_denominator / fraction_b->denominator);

        return new Fraction(diff_numerator, common_denominator);
    }
    else if (b->GetType() == CalcType::RealNumber)
    {
        RealNumber* real_b = dynamic_cast<RealNumber*>(b);
        double value_b = real_b->GetValue();
        double result = static_cast<double>(numerator) / denominator - value_b;
        return new RealNumber(result);
    }
    throw new Exception(ExceptionType::FORMULA_EXCEPTION);
}

Calculable* Fraction::Multiplication(Calculable* b)
{
    if (b->GetType() == CalcType::Fraction)
    {
        Fraction* fraction_b = dynamic_cast<Fraction*>(b);
        int new_numerator = numerator * fraction_b->numerator;
        int new_denominator = denominator * fraction_b->denominator;
        return new Fraction(new_numerator, new_denominator);
    }
    else if (b->GetType() == CalcType::RealNumber)
    {
        RealNumber* real_b = dynamic_cast<RealNumber*>(b);
        double value_b = real_b->GetValue();
        double result = static_cast<double>(numerator) / denominator * value_b;
        return new RealNumber(result);
    }
    throw new Exception(ExceptionType::FORMULA_EXCEPTION);
}

Calculable* Fraction::Division(Calculable* b)
{
    if (b->GetType() == CalcType::Fraction)
    {
        Fraction* fraction_b = dynamic_cast<Fraction*>(b);
        if (fraction_b->numerator == 0)
        {
            throw new Exception(ExceptionType::ZERO_DIVISION);
        }
        int new_numerator = numerator * fraction_b->denominator;
        int new_denominator = denominator * fraction_b->numerator;
        return new Fraction(new_numerator, new_denominator);
    }
    else if (b->GetType() == CalcType::RealNumber)
    {
        RealNumber* real_b = dynamic_cast<RealNumber*>(b);
        double value_b = real_b->GetValue();
        if (value_b == 0)
        {
            throw new Exception(ExceptionType::ZERO_DIVISION);
        }
        double result = static_cast<double>(numerator) / denominator / value_b;
        return new RealNumber(result);
    }
    throw new Exception(ExceptionType::FORMULA_EXCEPTION);
}

Calculable* Fraction::Exponentiation(Calculable* b)
{
    if (b->GetType() == CalcType::RealNumber)
    {
        double exponent = dynamic_cast<RealNumber*>(b)->GetValue();
        if (floor(exponent) != exponent || exponent < 0)
        {
            throw new Exception(ExceptionType::EXPONENTIATION_EXCEPTION);
        }
        else if (exponent == 0)
        {
            return new Fraction(1, 1);
        }
        else if (exponent == 1)
        {
            return new Fraction(numerator, denominator);
        }
        else
        {
            int new_numerator = pow(numerator, exponent);
            int new_denominator = pow(denominator, exponent);

            Fraction* result = new Fraction(new_numerator, new_denominator);
            result->Shorten();
            return result;
        }
    }
    throw new Exception(ExceptionType::FORMULA_EXCEPTION);
}

