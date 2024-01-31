#define _CRT_SECURE_NO_WARNINGS
#include "ExpressionTreeC.h"

ETNode* ET_CreateNode(ElemenType NewData) {
	ETNode* NewNode = (ETNode*)malloc(sizeof(ETNode));
	NewNode->Left = NULL;
	NewNode->Right = NULL;
	NewNode->Data = (ElemenType)malloc(strlen(NewData) + 1);
	strcpy(NewNode->Data, NewData);

	return NewNode;
}

void ET_DestroyNode(ETNode* Remove) {
	free(Remove->Data);
	free(Remove);
}

void ET_DestroyTree(ETNode* Root) {
	if (Root == NULL) {
		return;
	}
	
	ET_DestroyTree(Root->Left);
	ET_DestroyTree(Root->Right);

	ET_DestroyNode(Root);
}

void ET_PreOrderPrintTree(ETNode* Root, int Depth) {
	if (Root == NULL) {
		return;
	}
	
	for (int i = 0; i < Depth; ++i) {
		printf("   ");
	}

	if (Depth > 0) {
		printf("##");
	}

	printf("%s\n", Root->Data);

	ET_PreOrderPrintTree(Root->Left, Depth + 1);
	ET_PreOrderPrintTree(Root->Right, Depth + 1);
}

void ET_InOrderPrintTree(ETNode* Root, int Depth) {
	if (Root == NULL) {
		return;
	}

	ET_InOrderPrintTree(Root->Left, Depth + 1);

	for (int i = 0; i < Depth; ++i) {
		printf("   ");
	}

	if (Depth > 0) {
		printf("##");
	}

	printf("%s\n", Root->Data);

	ET_InOrderPrintTree(Root->Right, Depth + 1);
}

void ET_PostOrderPrintTree(ETNode* Root, int Depth) {
	if (Root == NULL) {
		return;
	}

	ET_PostOrderPrintTree(Root->Left, Depth + 1);
	ET_PostOrderPrintTree(Root->Right, Depth + 1);

	for (int i = 0; i < Depth; ++i) {
		printf("   ");
	}

	if (Depth > 0) {
		printf("##");
	}

	printf("%s\n", Root->Data);
}
// 1 2 3 '\0'
void StringReverse(char* Postfix) {
	int length = strlen(Postfix);
	char temp = 0;
	for (int i = 0; i < length / 2; ++i) {
		temp = Postfix[i];
		Postfix[i] = Postfix[(length - 1) - i];
		Postfix[(length - 1) - i] = temp;
	}
}

void ET_BuildExpressionTree(ETNode** Tree, char* ReversePostfix) {
	static unsigned int Index = 0;
	char Token[32];
	int Type = -1;

	if (ReversePostfix[Index] == '\0') {
		return;
	}
	// 1 2 * 7 8 - +

	while (Type != MINUS && Type != PLUS && Type != MULTIPLY && Type != DIVIDE && Type != OPERAND) 
	{
		Index += GetNextToken(&ReversePostfix[Index], Token, &Type);
	}

	if (isalnum(Token[0]) && strlen(Token) > 1) {
		StringReverse(Token);
	}

	switch (Type) {
	case PLUS:
	case MINUS:
	case MULTIPLY:
	case DIVIDE:
		(*Tree) = ET_CreateNode(Token);
		ET_BuildExpressionTree(&(*Tree)->Right, ReversePostfix);
		ET_BuildExpressionTree(&(*Tree)->Left, ReversePostfix);
		break;
	case OPERAND:
		(*Tree) = ET_CreateNode(Token);
		break;
	}
}

double ET_Calculate(ETNode* Tree) {
	double Leftval = 0;
	double Rightval = 0;
	double Result = 0;

	if (Tree == NULL) {
		return;
	}

	switch ((Tree->Data)[0]) 
	{
	case PLUS: case MINUS: case MULTIPLY: case DIVIDE:
		Leftval = ET_Calculate(Tree->Left);
		Rightval = ET_Calculate(Tree->Right);
		if ((Tree->Data)[0] == PLUS) Result = Leftval + Rightval;
		else if ((Tree->Data)[0] == MINUS) Result = Leftval - Rightval;
		else if ((Tree->Data)[0] == MULTIPLY) Result = Leftval * Rightval;
		else { 
			if (Rightval == 0) {
				printf("0인 값으로 나눌 수 없습니다.\n");
				exit(EXIT_FAILURE);
			}
			Result = Leftval / Rightval; 
		}
		break;
	default:
		Result = atof(Tree->Data);
		break;
	}

	return Result;
}