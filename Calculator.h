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

// Infix�� �⺻ ǥ��� Postfix�� ���� ǥ��� �����ڸ� �ڷ� ������ ǥ���

bool IsNumber(char Cipher);
unsigned int GetNextToken(char* Expression, char* Token, int* TYPE);
int GetPriority(char Operator, bool InStack);
bool IsPrior(char Operator1, char Operator2);
void GetPostfix(char* InfixExpression, char* PostfixExpression); 
double Calculate(char* PostfixExpression);

#endif
