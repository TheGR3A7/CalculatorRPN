#pragma once
#include "Calculable.h"
#include "RealNumber.h"

class Fraction : public Calculable
{
	friend RealNumber;
private:
	int numerator, denominator;
	void Shorten();
public:
	Fraction(int numerator, int denominator);
	void Print();
	Calculable* Plus(Calculable* b);
	Calculable* Minus(Calculable* b);
	Calculable* Multiplication(Calculable* b);
	Calculable* Division(Calculable* b);
	Calculable* Exponentiation(Calculable* b);
};

