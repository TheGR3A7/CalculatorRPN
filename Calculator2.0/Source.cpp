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
    std::cout << "�������� ��� ������������:" << std::endl << "1 - ������������ �����" << std::endl << "2 - ������� �����" << std::endl << "3 - �������" << std::endl << "4 - json" << std::endl;
    std::cin >> key;

    if (key != 4)
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "������� �������: ";
        std::getline(std::cin, text);
    }
    else
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "������� �������� �����: ";
        std::getline(std::cin, text);
    }

    Calculable* res = calc.Calculate(text, key - 1);
    std::cout << "�����: ";
    if (res->GetType() == CalcType::Matrix)
        std::cout << std::endl;
    res->Print();
}