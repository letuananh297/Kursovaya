#pragma once
#include <iostream>
#include <string>
#include "Stack.h"
#include "Queue.h"

using namespace std;

bool is_digit(char in) {
    return (in >= '0' && in <= '9');
}

bool is_operator(char in) {
    return (in == '+' || in == '-' || in == '*' || in == '/' || in == '^');
}

int priority(char in) {
    if (in == '+' || in == '-')
        return 1;
    else if (in == '*' || in == '/')
        return 2;
    else if (in == '^')
        return 3;
    else
        return 0;
}

int s1 = 0, s2 = 0;
bool closed = 0;

Queue<char>* ReversePolishNotation(string& input) {
	Stack<char>* stack = new Stack<char>;
	Queue<char>* queue = new Queue<char>;
    char i;

    if (!is_digit(input[input.size() - 1]) && input[input.size() - 1] != ')' &&
        input[input.size() - 1] != 'i' && input[input.size() - 1] != 'e' && 
        input[input.size() - 1] != '!') {
        throw logic_error("Expression is not correct.");
    }

     else if (is_operator(input[0]) || input[0] == '.'
              || input[0] == ')' || input[0] == '!' || input[0] == '^') {
        if (input[0] == '-')
            throw logic_error("Negative numbers are required in parentheses.");
        else
            throw logic_error("Expression is not correct.");
    }

    else {
        for (int j = 0; j < input.size(); j++) {
            i = input[j];
            if (i == '.')
                queue->enQueue(i);

            else if (is_digit(i))
                queue->enQueue(i);

            else if (is_operator(i)) {
                if (is_operator(input[j - 1])) {
                    throw logic_error("2 operators in a row.");
                    stack->~Stack();
                    queue->~Queue();
                    break;
                }
                else {
                    if (!(stack->isEmpty())) {
                        if (priority(stack->peek()) == priority(i)) {
                            if (is_digit(queue->rear->data))
                                queue->enQueue(' ');
                            queue->enQueue(stack->pop());
                            queue->enQueue(' ');
                            stack->push(i);
                        }
                        else if (priority(stack->peek()) > priority(i))
                        {
                            while (!stack->isEmpty() && stack->peek() != '(') {
                                if (is_digit(queue->rear->data) || is_operator(queue->rear->data))
                                    queue->enQueue(' ');
                                queue->enQueue(stack->pop());
                                queue->enQueue(' ');
                            }
                            stack->push(i);
                        }
                    }
                    if (stack->isEmpty() || priority(stack->peek()) < priority(i)) {
                        bool neg = 0;
                        if (!queue->isEmpty() && is_digit(queue->rear->data))
                            queue->enQueue(' ');
                        else if ((!stack->isEmpty() && stack->contains('(') && i == '-')) {
                            if (queue->isEmpty()) {
                                neg = 1;
                                queue->enQueue('(');
                                queue->enQueue('-');
                                queue->enQueue(' ');
                            }                        
                            else if (!queue->isEmpty() && queue->rear->data != ' ') {
                                neg = 1;
                                if (queue->rear->data != '(')
                                    queue->enQueue('(');
                                queue->enQueue('-');
                                queue->enQueue(' ');
                            }
                        }
                        else if (((!stack->isEmpty() && !stack->contains('('))) && i == '-') {
                            throw logic_error("Negative numbers are required in parentheses.");
                            stack->~Stack();
                            queue->~Queue();
                            break;
                        }
                        if (!queue->isEmpty() && neg == 0)
                            stack->push(i);
                    }
                }
            }

            else if (i == '(')
            {
                s1++;
                if (!queue->isEmpty() && is_digit(queue->rear->data)) {
                    queue->enQueue(' ');
                    stack->push('*');
                }
                stack->push(i);
            }

            else if (i == ')')
            {
                s2++;
                while (!stack->isEmpty() && stack->peek() != '(')
                    queue->enQueue(stack->pop());
                if (((queue->contains('(') && s2 < s1) || !closed) /* && input[j + 1] != '!'*/) {
                    queue->enQueue(i);
                    if (input[j + 1] != '!')
                        queue->enQueue(' ');
                    closed = 1;
                }
                if (!stack->isEmpty()) {
                    stack->pop();
                }
                else {
                    throw logic_error("The brackets are not balanced.");
                    stack->~Stack();
                    queue->~Queue();
                    break;
                }
            }

            else if (i == '!') {
                if (is_digit(input[j - 1]) || input[j - 1] == ')') {
                    if (is_operator(queue->rear->data))
                        queue->enQueue(' ');
                    queue->enQueue(i);
                    queue->enQueue(' ');
                    closed = 1;
                }
                else {
                    throw logic_error("The factorial function was entered incorrectly.");
                    stack->~Stack();
                    queue->~Queue();
                    break;
                }
            }

            else if (input[j] == 'c' && input[j + 1] == 'o' && input[j + 2] == 's') {
                if (input[j + 3] != '(') {
                    throw logic_error("The parameter of the cos function must be enclosed in parentheses.");
                    stack->~Stack();
                    queue->~Queue();
                    break;
                }
                else {
                    for (int k = j; k < j + 4; k++)
                        queue->enQueue(input[k]);
                    j = j + 2;
                    closed = 0;
                }
            }

            else if (input[j] == 's' && input[j + 1] == 'i' && input[j + 2] == 'n') {
                if (input[j + 3] != '(') {
                    throw logic_error("The parameter of the sin function must be enclosed in parentheses.");
                    stack->~Stack();
                    queue->~Queue();
                    break;
                }
                else {
                    for (int k = j; k < j + 4; k++)
                        queue->enQueue(input[k]);
                    j = j + 2;
                    closed = 0;
                }
            }

            else if (input[j] == 't' && input[j + 1] == 'g') {
                if (input[j + 2] != '(') {
                    throw logic_error("The parameter of the tg function must be enclosed in parentheses.");
                    stack->~Stack();
                    queue->~Queue();
                    break;
                }
                else {
                    for (int k = j; k < j + 3; k++)
                        queue->enQueue(input[k]);
                    j = j + 1;
                    closed = 0;
                }
            }

            else if (input[j] == 'c' && input[j + 1] == 't' && input[j + 2] == 'g') {
                if (input[j + 3] != '(') {
                    throw logic_error("The parameter of the ctg function must be enclosed in parentheses.");
                    stack->~Stack();
                    queue->~Queue();
                    break;
                }
                else {
                    for (int k = j; k < j + 4; k++)
                        queue->enQueue(input[k]);
                    j = j + 2;
                    closed = 0;
                }
            }

            else if (input[j] == 'l' && input[j + 1] == 'n') {
                if (input[j + 2] != '(') {
                    throw logic_error("The parameter of the ln function must be enclosed in parentheses.");
                    stack->~Stack();
                    queue->~Queue();
                    break;
                }
                else {
                    for (int k = j; k < j + 3; k++)
                        queue->enQueue(input[k]);
                    j = j + 1;
                    closed = 0;
                }
            }

            else if (input[j] == 'l' && input[j + 1] == 'o' && input[j + 2] == 'g') {
                if (input[j + 3] != '(') {
                    throw logic_error("The parameter of the log function must be enclosed in parentheses.");
                    stack->~Stack();
                    queue->~Queue();
                    break;
                }
                else {
                    for (int k = j; k < j + 4; k++)
                        queue->enQueue(input[k]);
                    j = j + 2;
                    closed = 0;
                }
            }

            else if (input[j] == 's' && input[j + 1] == 'q' && input[j + 2] == 'r' && input[j + 3] == 't') {
                if (input[j + 4] != '(') {
                    throw logic_error("The parameter of the sqrt function must be enclosed in parentheses.");
                    stack->~Stack();
                    queue->~Queue();
                    break;
                }
                else {
                    for (int k = j; k < j + 5; k++)
                        queue->enQueue(input[k]);
                    j = j + 3;
                    closed = 0;
                }
            }

            else if (input[j] == 'p' && input[j + 1] == 'i') {
                if (!queue->isEmpty() && is_digit(queue->rear->data)) {
                    queue->enQueue(' ');
                    stack->push('*');
                }
                for (int k = j; k < j + 2; k++)
                    queue->enQueue(input[k]);
                if (input[j + 2] != ')')
                    queue->enQueue(' ');
                j = j + 1;
            }

            else if (i == 'e') {
                if (!queue->isEmpty() && is_digit(queue->rear->data)) {
                    queue->enQueue(' ');
                    stack->push('*');
                }
                queue->enQueue(i);
                if (input[j + 1] != ')')
                    queue->enQueue(' ');
            }

            else {
                throw runtime_error("Expression is not correct.");
                stack->~Stack();
                queue->~Queue();
                break;
            }
        }
    }

    while (!stack->isEmpty()) {
        if (is_digit(queue->rear->data) || is_operator(queue->rear->data))
            queue->enQueue(' ');
        queue->enQueue(stack->pop());
    }

    if (is_digit(input[input.size() - 1]))
        queue->enQueue(' ');

    if (s1 != s2) {
        stack->~Stack();
        queue->~Queue();
        throw logic_error("The brackets are not balanced.");
    }

    return queue;
}