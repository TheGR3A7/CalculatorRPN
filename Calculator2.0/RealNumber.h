#pragma once
#include "Calculable.h"
#include <iostream>
#include <vector>

class RealNumber : public Calculable
{
private:
    double value;
public:
    RealNumber(double v);
    void Print();
    double GetValue();
    Calculable* Plus(Calculable* b);
    Calculable* Minus(Calculable* b);
    Calculable* Multiplication(Calculable* b);
    Calculable* Division(Calculable* b);
    Calculable* Exponentiation(Calculable* b);
};

