#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdlib.h>
#include "LinkedListStack.h"
#include <stdbool.h>

typedef enum {
	LEFT_PARENTHESIS = '(', RIGHT_PARENTHESIS = ')',
	PLUS = '+', MINUS = '-',
	MULTIPLY = '*', DIVIDE = '/',
	SPACE = ' ', OPERAND
} SYMNBOL;

// Infix가 기본 표기법 Postfix가 후위 표기법 연산자를 뒤로 보내는 표기법

bool IsNumber(char Cipher);
unsigned int GetNextToken(char* Expression, char* Token, int* TYPE);
int GetPriority(char Operator, bool InStack);
bool IsPrior(char Operator1, char Operator2);
void GetPostfix(char* InfixExpression, char* PostfixExpression); 
double Calculate(char* PostfixExpression);

#endif
