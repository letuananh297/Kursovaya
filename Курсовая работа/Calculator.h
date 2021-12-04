#pragma once
#include <iostream>
#include "Queue.h"
#include "Stack.h"
#include "ReversePolishNotation.h"
#include <math.h>
#define pi 3.141592653589793

//const double pi = 3.141592653589793;
const double e = 2.718281828459045;

bool function = 0;

double Calculator(Queue<char>* queue) {
	Stack<double>* stack = new Stack<double>;
	stack->push(0);
	bool newnumber = 0;
	double current1 = 0;
	double current2 = 0;
	int count1 = 0, count2 = 0;
	while (!queue->isEmpty()) {
		if (queue->front->data == '(' && queue->front->next->data != '-') {
			count1++;
			queue->deQueue();
		}

		else if (queue->front->data == ')') {
			count2++;
			queue->deQueue();
			if (count2 >= count1 && function) {
				newnumber = 1;
				function = 0;
				break;
			}
		}

		else if (queue->front->data == ' ') {
			newnumber = 1;
			queue->deQueue();
		}

		else if (is_digit(queue->front->data)) {
			if (newnumber) {
				stack->push((int)queue->deQueue() - 48);
				newnumber = 0;
			}
			else
				stack->top->data = stack->top->data * 10 + ((int)queue->deQueue() - 48);
		}

		else if (queue->front->data == '.') {
			queue->deQueue();
			int i = -1;
			while (is_digit(queue->front->data)) {
				stack->top->data = stack->top->data + ((int)queue->deQueue() - 48) * pow(10, i);
				i--;
			}
		}

		else if (queue->front->data == '!') {
			current2 = stack->pop();
			if (current2 == 0) {
				stack->push(1);
				queue->deQueue();
			}
			else if (current2 > 0 && current2 == (int)current2) {
				int x = 1;
				for (int i = 1; i <= current2; i++)
					x = x * i;
				stack->push(x);
				queue->deQueue();
			}
			else if (current2 < 0 || current2 != (int)current2) {
				throw logic_error("The parameter of the factorial function must be a non-negative integer.");
				stack->~Stack();
				break;
			}
		}

		else if (is_operator(queue->front->data)) {
			if (queue->front->data == '+') {
				current2 = stack->pop();
				current1 = stack->pop();
				stack->push(current1 + current2);
				queue->deQueue();
			}
			else if (queue->front->data == '-') {
				current2 = stack->pop();
				current1 = stack->pop();
				stack->push(current1 - current2);
				queue->deQueue();
			}
			else if (queue->front->data == '*') {
				current2 = stack->pop();
				current1 = stack->pop();
				stack->push(current1 * current2);
				queue->deQueue();
			}
			else if (queue->front->data == '/') {
				current2 = stack->pop();
				current1 = stack->pop();
				if (current2 == 0) {
					throw logic_error("Divisor of division equals 0.");
					stack->~Stack();
					break;
				}
				else
					stack->push(current1 / current2);
				queue->deQueue();
			}
			else if (queue->front->data == '^') {
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

		else if (queue->front->data == 'e') {
			stack->push(e);
			queue->deQueue();
		}

		else if (queue->front->data == 'c' && queue->front->next->data == 'o' 
			&& queue->front->next->next->data == 's') {
			queue->deQueue();
			queue->deQueue();
			queue->deQueue();
			function = 1;
			double x = Calculator(queue);
			stack->push(cos(x));
		}

		else if (queue->front->data == 's' && queue->front->next->data == 'i'
			&& queue->front->next->next->data == 'n') {
			queue->deQueue();
			queue->deQueue();
			queue->deQueue();
			function = 1;
			double x = Calculator(queue);
			stack->push(sin(x));
		}

		else if (queue->front->data == 't' && queue->front->next->data == 'g') {
		    queue->deQueue();
			queue->deQueue();
			function = 1;
			double x = Calculator(queue);
			if ((x / pi - (int)(x / pi)) == 0.5) {
				throw logic_error("tg(x) does not exist.");
				stack->~Stack();
				break;
			}
			else 
				stack->push(tan(x));
		}

		else if (queue->front->data == 'c' && queue->front->next->data == 't'
		&& queue->front->next->next->data == 'g') {
		    queue->deQueue();
			queue->deQueue();
			queue->deQueue();
			function = 1;
			double x = Calculator(queue);
			if ((x / pi - (int)(x / pi)) == 0.0) {
				throw logic_error("ctg(x) does not exist.");
				stack->~Stack();
				break;
			}
			else 
				stack->push(1/tan(x));
		}

		else if (queue->front->data == 'l' && queue->front->next->data == 'n') {
		    queue->deQueue();
			queue->deQueue();
			function = 1;
			double x = Calculator(queue);
			if (x <= 0) {
				throw logic_error("The parameter of the function 'ln' must be positive.");
				stack->~Stack();
				break;
			}
			else
				stack->push(log(x));
		}

		else if (queue->front->data == 'l' && queue->front->next->data == 'o'
		&& queue->front->next->next->data == 'g') {
		    queue->deQueue();
			queue->deQueue();
			queue->deQueue();
		    function = 1;
			double x = Calculator(queue);
			if (x <= 0) {
				throw logic_error("The parameter of the function 'log' must be positive.");
				stack->~Stack();
				break;
			}
			else
				stack->push(log10(x));
		}

		else if (queue->front->data == 's' && queue->front->next->data == 'q' &&
		queue->front->next->next->data == 'r' && queue->front->next->next->next->data == 't') {
		    queue->deQueue();
			queue->deQueue();
			queue->deQueue();
			queue->deQueue();
		    function = 1;
			double x = Calculator(queue);
			if (x < 0) {
				throw logic_error("The parameter of the square root function must be non-negative.");
				stack->~Stack();
				break;
			}
			else
				stack->push(sqrt(x));
		}

		else if (queue->front->data == '(' && queue->front->next->data == '-') {
		    count1++;
			queue->deQueue();
			queue->deQueue();
			function = 1;
			double x = Calculator(queue);
			stack->push(-x);
        }

		else {
            throw logic_error("Expression is not correct.");
            stack->~Stack();
            break;
        }
	}

	return stack->top->data;
}