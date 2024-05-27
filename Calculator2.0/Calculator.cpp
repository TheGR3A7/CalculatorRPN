#include "Calculator.h"
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <stack>
#include <sstream>
#include "Token.h"
#include "RealNumber.h"
#include "Fraction.h"
#include "Matrix.h"
#include "Exception.h"
#include <nlohmann/json.hpp>

Calculator::~Calculator()
{
    Clear();
}

void Calculator::Tokenize(std::string s, int key)
{
    nlohmann::json json;

    if (key == 3)
    {
        std::fstream file;
        file.open(s);
        if (!file)
        {
            throw new Exception(ExceptionType::JSON_EXCEPTION);
        }
        file >> json;
        file.close();
        s = json["formula"];
    }

    std::istringstream stream(s);
    char ch;
    while (stream >> ch)
    {
        if (isdigit(ch) || ch == '.')
        {
            std::string number(1, ch);
            while (stream.peek() != EOF && (isdigit(stream.peek()) || stream.peek() == '.'))
            {
                number += stream.get();
            }
            token_arr.push_back(new Token(TokenType::NUMBER, number));
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
        {
            token_arr.push_back(new Token(TokenType::OPERATOR, std::string(1, ch)));
        }
        else if (ch == '(') 
        {
            token_arr.push_back(new Token(TokenType::LPAREN, "("));
        }
        else if (ch == ')')
        {
            token_arr.push_back(new Token(TokenType::RPAREN, ")"));
        }
        else if (isalpha(ch))
        {
            std::string var;
            double v;
            int n, d;
            int rows, cols;
            std::vector<std::vector<double>> array;
            while (isalpha(ch))
            {
                var += ch;
                if (!(stream >> ch)) break;
            }
            stream.unget(); 
            Calculable* data = nullptr;
            switch (key)
            {
            case 0:
                std::cout << "Введите значение переменной " << var << ": ";
                std::cin >> v;
                data = new RealNumber(v);
                break;
            case 1:
                std::cout << "Введите числитель переменной " << var << ": ";
                std::cin >> n;
                std::cout << "Введите знаменатель переменной " << var << ": ";
                std::cin >> d;
                data = new Fraction(n, d);
                break;
            case 2:
                do
                {
                    std::cout << "Введите количество строк для переменной " << var << ": ";
                    std::cin >> rows;
                } while (rows < 1);

                do
                {
                    std::cout << "Введите количество столбцов для переменной " << var << ": ";
                    std::cin >> cols;
                } while (cols < 1);

                array.resize(rows);

                for (int i = 0; i < rows; i++)
                    array[i].resize(cols);

                for (int i = 0; i < rows; i++)
                {
                    for (int j = 0; j < cols; j++)
                    {
                        double x;
                        std::cout << "Введите " << j + 1 << " элемент " << i + 1 << " строки для переменной " << var << ": ";
                        std::cin >> x;
                        array[i][j] = x;
                    }
                }

                data = new Matrix(rows, cols, &array);
                break;
            case 3:
                bool flag = false;
                for (auto& i : json["var"])
                {
                    if (i["name"] == var)
                    {
                        flag = true;
                        int x = i["type"];
                        switch (x)
                        {
                        case 0:
                            data = new RealNumber(i["value"]);
                            break;
                        case 1:
                            data = new Fraction(i["value"]["num"], i["value"]["denom"]);
                            break;
                        case 2:
                            rows = i["value"]["rows"];
                            cols = i["value"]["cols"];

                            for (auto& i : i["value"]["data"])
                            {
                                std::vector<double> row;
                                for (auto& j : i)
                                    row.push_back(j);
                                if (row.size() != cols)
                                    throw new Exception(ExceptionType::SIZE_EXCEPTION);
                                array.push_back(row);
                            }

                            if (array.size() != rows)
                                throw new Exception(ExceptionType::SIZE_EXCEPTION);
                            data = new Matrix(rows, cols, &array);
                        }
                        break;
                    }
                }
                if (!flag)
                {
                    throw new Exception(ExceptionType::JSON_EXCEPTION);
                }
            }
            token_arr.push_back(new Token(TokenType::VARIABLE, var));
            result_map[var] = data;
            var.clear();
        }
        else
        {
            throw new Exception(ExceptionType::FORMULA_EXCEPTION);
        }
    }
}

void Calculator::MakeRPN()
{
    while (!token_arr.empty())
    {
        Token* tok = token_arr.front();
        token_arr.pop_front();

        switch (tok->GetType())
        {
        case TokenType::NUMBER:
        case TokenType::VARIABLE:
            rpn.push_back(tok);
            break;
        case TokenType::LPAREN:
            stack.push_back(tok);
            break;
        case TokenType::RPAREN:
        {
            while (!stack.empty() && stack.back()->GetType() != TokenType::LPAREN)
            {
                rpn.push_back(stack.back());
                stack.pop_back();
            }
            if (stack.empty())
                throw new Exception(ExceptionType::FORMULA_EXCEPTION);

            delete stack.back();
            stack.pop_back();
            delete tok;
            break;
        }
        case TokenType::OPERATOR:
        {
            while (!stack.empty() && stack.back()->GetType() == TokenType::OPERATOR && Precedence(stack.back()->GetValue()) >= Precedence(tok->GetValue()))
            {
                rpn.push_back(stack.back());
                stack.pop_back();
            }
            stack.push_back(tok);
            break;
        }
        }
    }

    while (!stack.empty())
    {
        if (stack.back()->GetType() == TokenType::LPAREN)
            throw new Exception(ExceptionType::FORMULA_EXCEPTION);

        rpn.push_back(stack.back());
        stack.pop_back();
    }
}

int Calculator::Precedence(const std::string& op)
{
    if (op == "+" || op == "-")
        return 1;
    else if (op == "*" || op == "/")
        return 2;
    else if (op == "^")
        return 3;
    else
        return 0;
}

void Calculator::Clear()
{
    if(!token_arr.empty())
        for (auto t : token_arr)
            delete t;
    if (!rpn.empty())
        for (auto t : rpn)
            delete t;
    if (!result.empty())
        for (auto t : result)
            delete t;

    token_arr.clear();
    rpn.clear();
    stack.clear();
    result.clear();
    result_map.clear(); 
}

Calculable* Calculator::Calculate()
{
    while (!rpn.empty())
    {
        Token* token = rpn.front();
        rpn.pop_front();

        switch (token->GetType())
        {
        case TokenType::NUMBER:
            result.push_back(new RealNumber(std::stod(token->GetValue())));
            break;
        case TokenType::VARIABLE:
        {
            auto it = result_map.find(token->GetValue());
            if (it != result_map.end())
            {
                result.push_back(it->second);
            }
            else
            {
                throw new Exception(ExceptionType::FORMULA_EXCEPTION);
            }
            break;
        }
        case TokenType::OPERATOR:
        {
            if (result.size() < 2)
                throw new Exception(ExceptionType::FORMULA_EXCEPTION);

            Calculable* second = result.back();
            result.pop_back();
            Calculable* first = result.back();
            result.pop_back();

            std::string op = token->GetValue();

            Calculable* new_data = nullptr;
            if (op == "+")
                new_data = first->Plus(second);
            else if (op == "-")
                new_data = first->Minus(second);
            else if (op == "*")
                new_data = first->Multiplication(second);
            else if (op == "/")
                new_data = first->Division(second);
            else if (op == "^")
                new_data = first->Exponentiation(second);
            else
                throw new Exception(ExceptionType::FORMULA_EXCEPTION);

            delete first;
            delete second;
            result.push_back(new_data);
            break;
        }
        }
        delete token;
    }

    if (result.empty())
        throw new Exception(ExceptionType::FORMULA_EXCEPTION);

    return result.front();
}

Calculable* Calculator::Calculate(std::string s, int key)
{
    try
    {
        Clear();
        Tokenize(s, key);
        MakeRPN();
        return Calculate();
    }
    catch (Exception* e)
    {
        Exception* exc = static_cast<Exception*>(e);
        switch (exc->GetType())
        {
        case ExceptionType::EXPONENTIATION_EXCEPTION:
            std::cout << "Возведение в отрицательную или нецелую степень.";
            break;
        case ExceptionType::FORMULA_EXCEPTION:
            std::cout << "Ошибка в формуле.";
            break;
        case ExceptionType::JSON_EXCEPTION:
            std::cout << "Ошибка в файле Json.";
            break;
        case ExceptionType::ZERO_DIVISION:
            std::cout << "Деление на ноль.";
            break;
        case ExceptionType::MATRIX_DIVISION:
            std::cout << "Деление матриц.";
            break;
        case ExceptionType::SIZE_EXCEPTION:
            std::cout << "Разное количество строк и/или столбцов в матрице.";
            break;
        default:
            std::cout << "Неизвестная ошибка.";
            break;
        }
        Clear();
        delete e;
        exit(0);
    }
}
