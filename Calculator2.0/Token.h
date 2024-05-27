#pragma once
#include <string>
#include <iostream>

enum class TokenType 
{
    NUMBER,
    OPERATOR,
    VARIABLE,
    LPAREN,
    RPAREN
};

class Token {
private:
    TokenType type;
    std::string value;
public:
    Token(TokenType t, std::string val);
    TokenType GetType();
    std::string GetValue();
};

