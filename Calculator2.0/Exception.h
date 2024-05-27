#pragma once

enum class ExceptionType
{
	ZERO_DIVISION,
	MATRIX_DIVISION,
	SIZE_EXCEPTION,
	EXPONENTIATION_EXCEPTION,
	FORMULA_EXCEPTION,
	JSON_EXCEPTION,
};

class Exception
{
private:
	ExceptionType type;
public:
	Exception(ExceptionType type);
	ExceptionType GetType();
};


