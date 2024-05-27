#pragma once
#include <iostream>
#include <list>
#include <unordered_map>
#include "Token.h"
#include "RealNumber.h"
#include "Fraction.h"
#include "Matrix.h"
#include "Exception.h"
#include <sstream>

class Calculator
{
private:
    std::list<Token*> token_arr, rpn, stack;
    std::list <Calculable*> result;
    std::unordered_map<std::string, Calculable*> result_map;

    void Tokenize(std::string s, int key);
    void MakeRPN();
    Calculable* Calculate();
    void Clear();
    int Precedence(const std::string& op);
public:
    ~Calculator();
    Calculable* Calculate(std::string s, int key);
};

