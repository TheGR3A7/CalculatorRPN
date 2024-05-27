#include <iostream>
#include <fstream>
#include <list>
#include "Token.h"
#include "RealNumber.h"
#include "Fraction.h"
#include "Matrix.h"
#include "Calculator.h"
#include <nlohmann/json.hpp>

int main()
{
    system("chcp 1251");

    Calculator calc;
    std::string text;
    int key;
    std::cout << "Выберите тип калькулятора:" << std::endl << "1 - вещественные числа" << std::endl << "2 - дробные числа" << std::endl << "3 - матрицы" << std::endl << "4 - json" << std::endl;
    std::cin >> key;

    if (key != 4)
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введите формулу: ";
        std::getline(std::cin, text);
    }
    else
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введите название файла: ";
        std::getline(std::cin, text);
    }

    Calculable* res = calc.Calculate(text, key - 1);
    std::cout << "Ответ: ";
    if (res->GetType() == CalcType::Matrix)
        std::cout << std::endl;
    res->Print();
}