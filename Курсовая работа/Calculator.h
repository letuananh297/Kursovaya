#pragma once
#include <iostream>
#include "Queue.h"
#include "Stack.h"
#include "ReversePolishNotation.h"
#include<math.h>

const double pi = atan(1) * 4;
const double e = 2.718281828459;

/*double function(Queue<char>* queue) {
	Stack<double>* stack = new Stack<double>;
	stack->push(0);
	int count1 = 1, count2 = 0;
	bool newnumber = 0;
	double current1 = 0;
	double current2 = 0;
	while (count2 < count1) {
		if (queue->getfront() == '(') {
			count1++;
			queue->deQueue();
		}
		else if (queue->getfront() == ')') {
			count2++;
			queue->deQueue();
		}
		else if (queue->getfront() == ' ') {
			newnumber = 1;
			queue->deQueue();
		}
		else if (is_digit(queue->getfront())) {
			if (newnumber) {
				stack->push((int)queue->deQueue() - 48);
				newnumber = 0;
			}
			else
				stack->top->data = stack->top->data * 10 + ((int)queue->deQueue() - 48);
		}
		else if (queue->getfront() == '.') {
			queue->deQueue();
			int i = -1;
			while (queue->getfront() != ' ') {
				stack->top->data = stack->top->data + ((int)queue->deQueue() - 48) * pow(10, i);
				i--;
			}
		}
		else if (queue->getfront() == '!') {
			current2 = stack->pop();
			if (current2 == 0)
				stack->push(1);
			else {
				int x = 1;
				for (int i = 1; i <= current2; i++)
					x = x * i;
				stack->push(x);
			}
			queue->deQueue();
		}
		else if (is_operator(queue->getfront())) {
			if (queue->getfront() == '+') {
				current2 = stack->pop();
				current1 = stack->pop();
				stack->push(current1 + current2);
				queue->deQueue();
			}
			else if (queue->getfront() == '-') {
				current2 = stack->pop();
				current1 = stack->pop();
				stack->push(current1 - current2);
				queue->deQueue();
			}
			else if (queue->getfront() == '*') {
				current2 = stack->pop();
				current1 = stack->pop();
				stack->push(current1 * current2);
				queue->deQueue();
			}
			else if (queue->getfront() == '/') {
				current2 = stack->pop();
				current1 = stack->pop();
				stack->push(current1 / current2);
				queue->deQueue();
			}
			else if (queue->getfront() == '^') {
				current2 = stack->pop();
				current1 = stack->pop();
				stack->push(pow(current1, current2));
				queue->deQueue();
			}
			newnumber = 1;
		}
		else if (queue->front->data == 'p' && queue->front->next->data == 'i') {
			stack->push(pi);
			queue->deQueue();
			queue->deQueue();
		}
		else if (queue->getfront() == 'e') {
			stack->push(e);
			queue->deQueue();
		}
	}
	return stack->top->data;
}*/
bool function = 0;

double Calculator(Queue<char>* queue) {
	Stack<double>* stack = new Stack<double>;
	stack->push(0);
	bool newnumber = 0;
	double current1 = 0;
	double current2 = 0;
	int count1 = 0, count2 = 0;
	while (!queue->isEmpty()) {
		if (queue->getfront() == '(') {
			count1++;
			queue->deQueue();
		}
		else if (queue->getfront() == ')') {
			count2++;
			queue->deQueue();
			if (count2 >= count1 && function) {
				newnumber = 1;
				function = 0;
				break;
			}
		}
		else if (queue->getfront() == ' ') {
			newnumber = 1;
			queue->deQueue();
		}
		else if (is_digit(queue->getfront())) {
			if (newnumber) {
				stack->push((int)queue->deQueue() - 48);
				newnumber = 0;
			}
			else
				stack->top->data = stack->top->data * 10 + ((int)queue->deQueue() - 48);
		}
		else if (queue->getfront() == '.') {
			queue->deQueue();
			int i = -1;
			while (queue->getfront() != ' ') {
				stack->top->data = stack->top->data + ((int)queue->deQueue() - 48) * pow(10, i);
				i--;
			}
		}
		else if (queue->getfront() == '!') {
			current2 = stack->pop();
			if (current2 == 0)
				stack->push(1);
			else {
				int x = 1;
				for (int i = 1; i <= current2; i++)
					x = x * i;
				stack->push(x);
			}
			queue->deQueue();
		}
		else if (is_operator(queue->getfront())) {
			if (queue->getfront() == '+') {
				current2 = stack->pop();
				current1 = stack->pop();
				stack->push(current1 + current2);
				queue->deQueue();
			}
			else if (queue->getfront() == '-') {
				current2 = stack->pop();
				current1 = stack->pop();
				stack->push(current1 - current2);
				queue->deQueue();
			}
			else if (queue->getfront() == '*') {
				current2 = stack->pop();
				current1 = stack->pop();
				stack->push(current1 * current2);
				queue->deQueue();
			}
			else if (queue->getfront() == '/') {
				current2 = stack->pop();
				current1 = stack->pop();
				stack->push(current1 / current2);
				queue->deQueue();
			}
			else if (queue->getfront() == '^') {
				current2 = stack->pop();
				current1 = stack->pop();
				stack->push(pow(current1, current2));
				queue->deQueue();
			}
			newnumber = 1;
		}
		else if (queue->front->data == 'p' && queue->front->next->data == 'i') {
			stack->push(pi);
			queue->deQueue();
			queue->deQueue();
		}
		else if (queue->getfront() == 'e') {
			stack->push(e);
			queue->deQueue();
		}
		else if (queue->deQueue() == 'c' && queue->deQueue() == 'o' && queue->deQueue() == 's') {
			function = 1;
			double x = Calculator(queue);
			stack->push(cos(x));
		}
		else if (queue->deQueue() == 's' && queue->deQueue() == 'i' && queue->deQueue() == 'n') {
			function = 1;
			double x = Calculator(queue);
			stack->push(sin(x));
		}
		else if (queue->deQueue() == 't' && queue->deQueue() == 'g') {
			function = 1;
			double x = Calculator(queue);
			stack->push(tan(x));
		}
		else if (queue->deQueue() == 'c' && queue->deQueue() == 't' && queue->deQueue() == 'g') {
			function = 1;
			double x = Calculator(queue);
			stack->push(1/tan(x));
		}
		else if (queue->deQueue() == 'l' && queue->deQueue() == 'n') {
			function = 1;
			double x = Calculator(queue);
			stack->push(log(x));
		}
		else if (queue->deQueue() == 'l' && queue->deQueue() == 'o' && queue->deQueue() == 'g') {
		    function = 1;
			double x = Calculator(queue);
		    stack->push(log10(x));
		}
		else if (queue->deQueue() == 's' && queue->deQueue() == 'q' && queue->deQueue() == 'r' && queue->deQueue() == 't') {
			function = 1;
			double x = Calculator(queue);
			stack->push(sqrt(x));
		}
	}
	return stack->top->data;
}