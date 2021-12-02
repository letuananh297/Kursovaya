#pragma once
#pragma once
#include <iostream>

using namespace std;

template<class T>
class Queue {
private:
	class Element_Queue {
	public:
		T data;
		Element_Queue* next;
	};

	

public:
	Element_Queue* front;
	Element_Queue* rear;
	size_t size;
	bool contains(T x) {
		if (isEmpty())
			throw runtime_error("Queue is empty.");
		else {
			Element_Queue* temporary = front;
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

	void enQueue(T x) {
		Element_Queue* Node = new Element_Queue;
		Node->data = x;
		Node->next = NULL;
		if (isEmpty()) {
			rear = Node;
			front = Node;
		}
		else {
			if (front->next == NULL)
				front->next = Node;
			rear->next = Node;
			rear = Node;
		}
		size++;
	}

	T deQueue() {
		if (isEmpty())
			throw runtime_error("Queue is empty.");
		else {
			Element_Queue* temporary = front;
			if (temporary->next == NULL) {
				front = NULL;
				rear = NULL;
			}
			else
				front = front->next;

			T value = temporary->data;
			delete temporary;
			size--;
			return value;
		}
	}

	T getfront() {
		if (isEmpty())
			throw runtime_error("Stack is empty.");
		else {
			return front->data;
		}
	}

	T getrear() {
		if (isEmpty())
			throw runtime_error("Stack is empty.");
		else {
			return rear->data;
		}
	}

	size_t getsize() { return size; }

	bool isEmpty() {
		if (front == NULL && rear == NULL)
			return true;
		else {
			return false;
			if (front == NULL && rear != NULL)
				front = rear;
			if (front != NULL && rear == NULL)
				rear = front;
		}
	}

	void outQueue() {
		if (isEmpty())
			throw runtime_error("Queue is empty.");
		else {
			Element_Queue* temporary = front;
			while (temporary != NULL) {
				cout << temporary->data;
				temporary = temporary->next;
			}
		}
	}

	Queue() {
		front = NULL;
		rear = NULL;
		size = 0;
	}

	~Queue() {
		while (size)
			deQueue();
	};
};