#include <iostream>
#include <math.h>
#include <fstream>
#include "ReversePolishNotation.h"
#include "Calculator.h"

using namespace std;

int main() {
	string input = "(cos(3pi)-sin(2pi))*(tg(pi/4)+ctg(pi/4))-ln(e)*log(10^3)-sqrt(9)+(2*4-3)!";
	Queue<char>* queue = new Queue<char>();
	cout << "The expression before reversing: " << input << endl;
	
	queue = ReversePolishNotation(input);
	if (!queue->isEmpty()) {
		cout << "\nThe expression after reversing: ";
		queue->outQueue();
	}
	cout << endl;

	if (!queue->isEmpty())
		cout << "\nResult of the expression: " << Calculator(queue);
	else
		cout << "The expression is not correct.";
	cout << endl;

	return 0;
}