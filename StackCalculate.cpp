#include "Calculate.hpp"


int Postfix::GetPriority(char Operator, bool Fromstack) {
	int prirority;
	switch (Operator) {
	case LEFT_PARENTHESIS:
		if (Fromstack) {
			prirority = 3;
			break;
		}
		prirority = 0;
		break;

	case MULTIPLY:
	case DIVIDE:
		prirority = 1;
		break;
	case PLUS:
	case MINUS:
		prirority = 2;
		break;
	default:
		prirority = -1; // RIGHT_PARENTHESIS
		break;
	}
	return prirority;
}

bool Postfix::IsPrior(int stack_priority, int priority) {
	return stack_priority > priority ? true : false;
}

Postfix::Postfix(std::string& Infix) {
	int index = 0;
	std::string temp;

	while (index < Infix.size()) {

		if (isalnum(Infix[index])) {
			temp += Infix[index];
			if (!isalnum(Infix[index + 1])) {
				postfix += temp;
				postfix += ' ';
				temp.clear();
			}
		}
		else if (Infix[index] == RIGHT_PARENTHESIS) {
			while (!Operator_stack.isEmpty()) {
				if (Operator_stack.top() == LEFT_PARENTHESIS) {
					break;
				}
				postfix += Operator_stack.pop();
				postfix += ' ';
			}
		}
		else {
			if (Infix[index] == SPACE) {
				++index;
				continue;
			}
			// stack이 비어있거나 새로운 연산자가 Priority가 높지 않다면
			while (!Operator_stack.isEmpty() &&
				!IsPrior(GetPriority(Operator_stack.top(), true), GetPriority(Infix[index], false)))
			{
				if (Operator_stack.top() == LEFT_PARENTHESIS || Operator_stack.top() == RIGHT_PARENTHESIS) {
					Operator_stack.pop();
					continue;
				}
				postfix += Operator_stack.pop();
				postfix += ' ';
			}
			Operator_stack.push(Infix[index]);
		}
		++index;
	}

	while (!Operator_stack.isEmpty()) {
		if (Operator_stack.top() == LEFT_PARENTHESIS ||
			Operator_stack.top() == RIGHT_PARENTHESIS)
		{
			Operator_stack.pop();
			continue;
		}
		postfix += Operator_stack.pop();
		postfix += ' ';
	}
}


Calculator::Calculator(const std::string& postfix) : Ret_val(0)
{
	std::istringstream word(postfix);
	std::string temp;

	while (word >> temp) {
		char ch = temp[0];
		if (ch == SPACE) {
			continue;
		}
		else if (isalnum(ch)) {
			Operand_stack.push(stod(temp));
		}
		else {
			double Operand2 = Operand_stack.pop(); // ex) 18 3 -> Operand2 = 3; Operand1 = 18
			double Operand1 = Operand_stack.pop();

			switch (ch) {
			case PLUS:
				Ret_val = (Operand1 + Operand2);
				break;
			case MINUS:
				Ret_val = (Operand1 - Operand2);
				break;
			case MULTIPLY:
				Ret_val = (Operand1 * Operand2);
				break;
			case DIVIDE:
				if (Operand2 == 0) {
					std::cerr << "0인 값으로 나눌 수 없습니다" << std::endl;
					exit(1);
				}
				Ret_val = (Operand1 / Operand2);
				break;
			}
			Operand_stack.push(Ret_val);
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Calculator& cal) {
	os << cal.Ret_val << std::endl;
	return os;
}