#define _CRT_SECURE_NO_WARNINGS
#include "Calculator.h"

char NUMBER[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.' };

bool IsNumber(char Cipher) {
	int i = 0;
	int ArrayLength = sizeof(NUMBER);

	for (i = 0; i < ArrayLength; ++i) {
		if (Cipher == NUMBER[i]) {
			return true;
		}
	}
	return false;
}

unsigned int GetNextToken(char* Expression, char* Token, int* Type) {
	unsigned int i = 0;

	while (Expression[i] != 0) {
		
		Token[i] = Expression[i];
		// 수 일때
		if (IsNumber(Expression[i]) == true) { 
			*Type = OPERAND;
			// 숫자가 수의 마지막일 때
			if (IsNumber(Expression[i + 1]) == false) 
				break;
		}
		// 연산자일 때
		else { 
			*Type = Expression[i];
			break;
		}
		++i;
	}
	Token[++i] = '\0'; // Token은 인식된 하나의 기호 : operand or operator
	return i;
}

int GetPriority(char Operator, bool InStack) {
	int Priority = -1;

	switch (Operator)
	{
	case LEFT_PARENTHESIS:
		if (InStack == true)
			Priority = 3;
		else
			Priority = 0;
		break;

	case MULTIPLY:
	case DIVIDE:
		Priority = 1;
		break;

	case PLUS:
	case MINUS:
		Priority = 2;
		break;
	}

	return Priority;
}

// Priority는 우선순위로 높을 수록 나중에 처리 낮을수록 먼저 처리
// 토큰의 연산자가 스택의 연산자보다 Priority가 낮다면 true를 높다면 false를 반환한다.
bool IsPrior(char OperatorInStack, char OperatorInToken) {
	return (GetPriority(OperatorInStack, true) > GetPriority(OperatorInToken, false));
}

void GetPostfix(char* InfixExpression, char* PostfixExpression) {
	LinkedListStack* Stack;

	char Token[32];
	int Type = -1;
	unsigned int Position = 0;
	unsigned int Length = strlen(InfixExpression);

	LLS_CreateStack(&Stack);

	while (Position < Length) {
		Position += GetNextToken(&InfixExpression[Position], Token, &Type);
		// 피연산자 즉 숫자일 경우
		if (Type == OPERAND) {
			strcat(PostfixExpression, Token);
			strcat(PostfixExpression, " ");
		}
		// ')'일 경우
		else if (Type == RIGHT_PARENTHESIS) {
			while (!LLS_IsEmpty(Stack)) {
				Node* Popped = LLS_Pop(Stack);
				// '('을 만나면 루프 탈출
				if (Popped->Data[0] == LEFT_PARENTHESIS) {
					LLS_DestroyNode(Popped);
					break;
				}
				// 
				else {
					strcat(PostfixExpression, Popped->Data);
					strcat(PostfixExpression, " "); // 기호들을 구분하기 위함
					LLS_DestroyNode(Popped);
				}
			}
		}
		// 피연산자도 아니고 ')'도 아닐 경우 ex) +
		else {
			// 스텍 top의 연산자의 Priority <= Token의 Priority 인 경우까지 루프를 수행
			// 등호에 경우 먼저 나온 연산자가 먼저 계산되야 하기 때문
			// == 즉 토큰의 우선순위가 높은 경우까지만 수행된다
			// Priority가 낮으면 그냥 스택에 넣으면 된다.
			// 높거나 같은 경우의 스택의 원소들은 출력해야된다.
			while (!LLS_IsEmpty(Stack) &&
				!IsPrior(LLS_Top(Stack)->Data[0], Token[0])) {
				Node* Popped = LLS_Pop(Stack);

				if (Popped->Data[0] != LEFT_PARENTHESIS) {
					strcat(PostfixExpression, Popped->Data);
					strcat(PostfixExpression, " ");
				}
				LLS_DestroyNode(Popped);
			}

			LLS_Push(Stack, LLS_CreateNode(Token));
		}
	}

	while (!LLS_IsEmpty(Stack)) {
		Node* Popped = LLS_Pop(Stack);
		
		if (Popped->Data[0] != LEFT_PARENTHESIS) {
			strcat(PostfixExpression, Popped->Data);
			strcat(PostfixExpression, " ");
		}
		LLS_DestroyNode(Popped);
	}
	LLS_DestroyStack(Stack);
}

double Calculate(char* PostfixExpression) {
	LinkedListStack* Stack;
	Node* ResultNode;

	double Result;
	char Token[32];
	int Type = -1;
	unsigned int Read = 0;
	unsigned int Length = strlen(PostfixExpression);

	LLS_CreateStack(&Stack);

	while (Read < Length) {
		Read += GetNextToken(&PostfixExpression[Read], Token, &Type);

		if (Type == SPACE) {
			continue;
		}

		if (Type == OPERAND) {
			Node* NewNode = LLS_CreateNode(Token);
			LLS_Push(Stack, NewNode);
		}
		else {
			char ResultString[32];
			double Operator1, Operator2, TempResult;
			Node* OperatorNode;

			OperatorNode = LLS_Pop(Stack);
			Operator2 = atof(OperatorNode->Data);
			LLS_DestroyNode(OperatorNode);

			OperatorNode = LLS_Pop(Stack);
			Operator1 = atof(OperatorNode->Data);
			LLS_DestroyNode(OperatorNode);
			
			switch (Type)
			{
			case PLUS:     TempResult = Operator1 + Operator2; break;
			case MINUS:    TempResult = Operator1 - Operator2; break;
			case MULTIPLY: TempResult = Operator1 * Operator2; break;
			case DIVIDE:   TempResult = Operator1 / Operator2; break;
			}

			_gcvt(TempResult, 10, ResultString);
			LLS_Push(Stack, LLS_CreateNode(ResultString));
		}
	}
	
	ResultNode = LLS_Pop(Stack);
	Result = atof(ResultNode->Data);
	LLS_DestroyNode(ResultNode);

	LLS_DestroyStack(Stack);

	return Result;
}