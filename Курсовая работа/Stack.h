#pragma once
#pragma once
#include <iostream>

using namespace std;

template<class T>
class Stack {
private:
	class Element_Stack {
	public:
		T data;
		Element_Stack* next;
	};

public:
	Element_Stack* top;
	size_t size;

	bool contains(T x) {
		if (isEmpty())
			throw runtime_error("Stack is empty.");
		else {
			Element_Stack* temporary = top;
			bool check = 0;
			while (temporary != NULL) {
				if (temporary->data == x) {
					check = 1;
					break;
				}
				temporary = temporary->next;
			}
			return check;
		}
	}

	void push(T x) {
		if (isEmpty()) {
			Element_Stack* Node = new Element_Stack;
			Node->data = x;
			Node->next = NULL;
			top = Node;
		}
		else {
			Element_Stack* Node = new Element_Stack;
			Node->data = x;
			Node->next = top;
			top = Node;
		}
		size++;
	}

	T pop() {
		if (isEmpty())
			throw runtime_error("Stack is empty.");
		else {
			Element_Stack* temporary = top;
			if (top->next == NULL)
				top = NULL;
			else
				top = temporary->next;
			T popped = temporary->data;
			delete temporary;
			size--;
			return popped;
		}
	}

	T peek() {
		if (isEmpty())
			throw runtime_error("Stack is empty.");
		else {
			return top->data;
		}
	}

	bool isEmpty() {
		if (top == NULL)
			return true;
		else
			return false;
	}

	Stack() {
		top = NULL;
		size = 0;
	}

	~Stack() {
		while (size)
			pop();
	};
};