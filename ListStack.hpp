#pragma once
#ifndef LISTSTACK_H
#define LISTSTACK_H

#include <list>
#include <iostream>

template<typename T>
class LLStack {
public:
	LLStack() = default;
	~LLStack()
	{
		if (!lst.empty()) {
			clear();
		}
	}
	void clear() {
		lst.clear();
	}

	bool isEmpty() {
		return lst.empty();
	}

	T& top() {
		return lst.back();
	}

	T pop() {
		T ret_val = lst.back();
		lst.pop_back();

		return ret_val;
	}

	void push(const T& newData) {
		lst.push_back(newData);
	}

public:
	friend std::ostream& operator<<(std::ostream& os, const LLStack& stack) {
		for (auto iter = stack.lst.rbegin(); iter != stack.lst.rend(); ++iter) {
			os << "Pop element : " << *iter << std::endl;
		}
		return os;
	}

private:
	std::list<T> lst;
};

#endif // !LISTSTACK_H

