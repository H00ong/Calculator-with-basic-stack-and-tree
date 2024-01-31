#pragma once
#ifndef CALCULATECPP_H
#define CALCULATECPP_H

// INFIX->POSTFIX->°è»ê

#include<string>
#include<stdlib.h>
#include<cctype>
#include"ListStack.hpp"
#include <sstream>

typedef enum
{
	LEFT_PARENTHESIS = '(', RIGHT_PARENTHESIS = ')',
	PLUS = '+', MINUS = '-',
	MULTIPLY = '*', DIVIDE = '/',
	SPACE = ' ', OPERAND
} SYMBOL;

class Postfix {
public:
	Postfix(std::string& Infix);
	std::string& Getstring() { return postfix; }
private:
	std::string postfix;
	LLStack<char> Operator_stack;
	int GetPriority(char Operator, bool Fromstack);
	bool IsPrior(int stack_priority, int priority);
};

class Calculator {
public:
	Calculator(const std::string& postfix);
	double GetValue() const { return Ret_val; };
	friend std::ostream& operator<<(std::ostream& os, const Calculator& cal);
private:
	LLStack<double> Operand_stack;
	double Ret_val;
};

#endif // !CALCULATECP5P_H
