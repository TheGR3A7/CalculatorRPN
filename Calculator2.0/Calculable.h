#pragma once


enum class CalcType
{
	RealNumber,
	Fraction,
	Matrix
};

class Calculable
{
protected:
	CalcType type;
public:
	virtual Calculable* Plus(Calculable* b) = 0;
	virtual Calculable* Minus(Calculable* b) = 0;
	virtual Calculable* Multiplication(Calculable* b) = 0;
	virtual Calculable* Division(Calculable* b) = 0;
	virtual Calculable* Exponentiation(Calculable* b) = 0;
	virtual void Print() = 0;
	CalcType GetType();
};