#include "Token.h"
#include <vector>

Token::Token(TokenType t, std::string val) : type(t), value(val) {}

TokenType Token::GetType()
{
	return type;
}

std::string Token::GetValue()
{
	return value;
}


