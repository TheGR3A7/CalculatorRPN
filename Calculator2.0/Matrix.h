#pragma once
#include <vector>
#include "Calculable.h"
#include "RealNumber.h"
#include "Fraction.h"

class Matrix: public Calculable
{
	friend RealNumber;
private:
	std::vector<std::vector<double>> data;
	int rows, cols;
public:
	Matrix(int rows, int cols, std::vector<std::vector<double>>* data);
	void Print();
	Calculable* Plus(Calculable* b);
	Calculable* Minus(Calculable* b);
	Calculable* Multiplication(Calculable* b);
	Calculable* Division(Calculable* b);
	Calculable* Exponentiation(Calculable* b);
};

