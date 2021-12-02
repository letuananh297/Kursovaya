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

int prior(char in) {
    if (in == '+' || in == '-')//если + или -,
        return 1;//то приоритет 1
    else if (in == '*' || in == '/')//если * или /,
        return 2;//то 2
    else if (in == '^')
        return 3;
    else//если это вообще не операци€, то возвращает 0
        return 0;
}

Queue<char>* ReversePolishNotation(string& input) {
	Stack<char>* stack = new Stack<char>;
	Queue<char>* queue = new Queue<char>;
    char i;

    if (!is_digit(input[input.size() - 1]) && input[input.size() - 1] != ')' &&
        input[input.size() - 1] != 'i' && input[input.size() - 1] != 'e' && 
        input[input.size() - 1] != '!') {
        cout << /*throw logic_error(*/"Missing number.";
    }

     else if (is_operator(input[0]) || input[0] == '.'
              || input[0] == ')' || input[0] == '!') {
        if (input[0] == '-')
            cout << /*throw logic_error(*/"Negative numbers are required in parentheses.";
        else
            cout << /*throw logic_error(*/"Operator at the beginning of the expression.";
    }

    else {
        for (int j = 0; j < input.size(); j++) {
            i = input[j];
            if (i == '.')//если это просто точка, т.е. пользователь ввел число по типу 0.2,
                queue->enQueue(i);//то тупо пихаем еЄ внутрь
            else if (is_digit(i))
                queue->enQueue(i);
            else if (is_operator(i)) {
                if (is_operator(input[j - 1])) {
                    cout << /*throw logic_error(*/"2 operators in a row.";
                    stack->~Stack();
                    queue->~Queue();
                    break;
                }
                else {
                    if (!(stack->isEmpty())) {
                        if (prior(stack->peek()) == prior(i)) {
                            queue->enQueue(stack->pop());
                            stack->push(i);
                        }
                        else if (prior(stack->peek()) > prior(i))//если же это была оперци€ меньшего приоритета, т.е. + или -
                        {
                            while (!stack->isEmpty() && stack->peek() != '(') {
                                queue->enQueue(stack->pop());
                            }
                            stack->push(i);
                        }
                    }
                    if (stack->isEmpty() || prior(stack->peek()) < prior(i)) {
                        bool neg = 0;
                        if (!queue->isEmpty() && is_digit(queue->getrear()))//если последнее, что было в gen - переменна€ или цифра, 
                            queue->enQueue(' ');//то следует поставить ограничивающий знак
                        else if (((!stack->isEmpty() && stack->contains('(')) && i == '-')) {
                            neg = 1;
                            queue->enQueue('(');
                            queue->enQueue('-');
                        }
                        else if ((queue->isEmpty() || (!stack->isEmpty() && !stack->contains('('))) && i == '-') {
                            cout << /*throw logic_error(*/"Negative numbers are required in parentheses.";
                            stack->~Stack();
                            queue->~Queue();
                            break;
                        }
                        if (!queue->isEmpty() && neg == 0)//если последнее в gen не _, которые мы могли только что записать => это кака€-то операци€
                            stack->push(i);
                    }
                }
            }
            else if (i == '(')//если же у нас не цифра, не переменна€ и не операци€, а откр. скобка, то...
            {
                if (!queue->isEmpty() && is_digit(queue->getrear())) {
                    queue->enQueue(' ');//ставим ограничивающий знак, а в стек записываем *
                    stack->push('*');//ќп€ть же, зачем? ј затем, чтобы не ставить его самим при записи типа: 23(13 + 1), например
                }
                stack->push(i);
                //queue->enQueue(i);//запихиваем ( в стэк
            }
            else if (i == ')')//если же у нас закрылась скобка, следует выгрущить все операции из stk в gen
            {
                while (!stack->isEmpty() && stack->peek() != '(')//пока стек не пустой (если он опустел значит пользователь ввел неправильное выражение) и до, конечно, открывающийс€ скобки 
                {
                    queue->enQueue(stack->pop());
                    //stack->pop();
                }
                if (queue->contains('(')) {
                    queue->enQueue(i);
                    queue->enQueue(' ');
                }
                if (!stack->isEmpty()) {
                    stack->pop();
                }
                else {
                    cout << /*throw logic_error(*/"Missing '('";
                    stack->~Stack();
                    queue->~Queue();
                    break;
                }
            }
            else if (i == '!') {
                if (is_digit(input[j - 1])) {
                    queue->enQueue(i);
                    queue->enQueue(' ');
                }
                else
                    cout << /*throw logic_error(*/"The factorial function was entered incorrectly.";
            }

            else if (input[j] == 'c' && input[j + 1] == 'o' && input[j + 2] == 's') {
                if (input[j + 3] != '(') {
                    cout << /*throw logic_error(*/"The parameter of the cos function must be enclosed in parentheses.";
                    stack->~Stack();
                    queue->~Queue();
                    break;
                }
                else {
                    stack->push(input[j + 3]);
                    for (int k = j; k < j + 4; k++)
                        queue->enQueue(input[k]);
                    j = j + 3;
                }
            }

            else if (input[j] == 's' && input[j + 1] == 'i' && input[j + 2] == 'n') {
                if (input[j + 3] != '(') {
                    cout << /*throw logic_error(*/"The parameter of the sin function must be enclosed in parentheses.";
                    stack->~Stack();
                    queue->~Queue();
                    break;
                }
                else {
                    stack->push(input[j + 3]);
                    for (int k = j; k < j + 4; k++)
                        queue->enQueue(input[k]);
                    j = j + 3;
                }
            }

            else if (input[j] == 't' && input[j + 1] == 'g') {
                if (input[j + 2] != '(') {
                    cout << /*throw logic_error(*/"The parameter of the tg function must be enclosed in parentheses.";
                    stack->~Stack();
                    queue->~Queue();
                    break;
                }
                else {
                    stack->push(input[j + 2]);
                    for (int k = j; k < j + 3; k++)
                        queue->enQueue(input[k]);
                    j = j + 2;
                }
            }

            else if (input[j] == 'c' && input[j + 1] == 't' && input[j + 2] == 'g') {
                if (input[j + 3] != '(') {
                    cout << /*throw logic_error(*/"The parameter of the ctg function must be enclosed in parentheses.";
                    stack->~Stack();
                    queue->~Queue();
                    break;
                }
                else {
                    stack->push(input[j + 3]);
                    for (int k = j; k < j + 4; k++)
                        queue->enQueue(input[k]);
                    j = j + 3;
                }
            }

            else if (input[j] == 'l' && input[j + 1] == 'n') {
                if (input[j + 2] != '(') {
                    cout << /*throw logic_error(*/"The parameter of the ln function must be enclosed in parentheses.";
                    stack->~Stack();
                    queue->~Queue();
                    break;
                }
                else {
                    stack->push(input[j + 2]);
                    for (int k = j; k < j + 3; k++)
                        queue->enQueue(input[k]);
                    j = j + 2;
                }
            }

            else if (input[j] == 'l' && input[j + 1] == 'o' && input[j + 2] == 'g') {
                if (input[j + 3] != '(') {
                    cout << /*throw logic_error(*/"The parameter of the log function must be enclosed in parentheses.";
                    stack->~Stack();
                    queue->~Queue();
                    break;
                }
                else {
                    stack->push(input[j + 3]);
                    for (int k = j; k < j + 4; k++)
                        queue->enQueue(input[k]);
                    j = j + 3;
                }
            }

            else if (input[j] == 's' && input[j + 1] == 'q' && input[j + 2] == 'r' && input[j + 3] == 't') {
                if (input[j + 4] != '(') {
                    cout << /*throw logic_error(*/"The parameter of the sqrt function must be enclosed in parentheses.";
                    stack->~Stack();
                    queue->~Queue();
                    break;
                }
                else {
                    stack->push(input[j + 4]);
                    for (int k = j; k < j + 5; k++)
                        queue->enQueue(input[k]);
                    j = j + 4;
                }
            }

            else if (input[j] == 'p' && input[j + 1] == 'i') {
                if (!queue->isEmpty() && is_digit(queue->getrear())) {
                    queue->enQueue(' ');//ставим ограничивающий знак, а в стек записываем *
                    stack->push('*');//ќп€ть же, зачем? ј затем, чтобы не ставить его самим при записи типа: 23(13 + 1), например
                }
                for (int k = j; k < j + 2; k++)
                    queue->enQueue(input[k]);
                j = j + 1;
            }

            else if (i == 'e') {
                if (!queue->isEmpty() && is_digit(queue->getrear())) {
                    queue->enQueue(' ');//ставим ограничивающий знак, а в стек записываем *
                    stack->push('*');//ќп€ть же, зачем? ј затем, чтобы не ставить его самим при записи типа: 23(13 + 1), например
                }
                queue->enQueue(i);
            }

            else {
                cout << /*throw logic_error(*/"Expression is not correct.";
                stack->~Stack();
                queue->~Queue();
                break;
            }
        }
    }

    while (!stack->isEmpty())
        queue->enQueue(stack->pop());

    if (is_digit(input[input.size() - 1]))
        queue->enQueue(' ');

    return queue;
}