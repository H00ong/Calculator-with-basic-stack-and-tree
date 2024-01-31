#pragma once
#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "Calculator.h"

typedef char* ElemenType;

typedef struct tagETNode {
	struct tagETNode* Left;
	struct tagETNode* Right;
	ElemenType Data;
} ETNode;

ETNode* ET_CreateNode(ElemenType NewData);
void ET_DestroyNode(ETNode* Remove);
void ET_DestroyTree(ETNode* Root);
void ET_PreOrderPrintTree(ETNode* Root, int Depth);
void ET_InOrderPrintTree(ETNode* Root, int Depth);
void ET_PostOrderPrintTree(ETNode* Root, int Depth);
void ET_BuildExpressionTree(ETNode** Tree, char* ReversePostfix);
void StringReverse(char* Postfix);
double ET_Calculate(ETNode* Tree);

#endif // !EXPRESSIONTREE_H
