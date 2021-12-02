#include <iostream>
#include <math.h>
#include "ReversePolishNotation.h"
#include "Calculator.h"

using namespace std;

int main() {
	string input;
	Queue<char>* queue = new Queue<char>();
	cout << "Enter an expression: ";
	getline(cin, input);
	//cout << has_cos(input);
	
	queue = ReversePolishNotation(input);
	if (!queue->isEmpty()) {
		cout << "\nThe expression after reversing: ";
		queue->outQueue();
	}
	/*cout << function(queue) << endl;
	queue->outQueue();*/
	cout << "\nAnswer: " << Calculator(queue);
	cout << endl;
	return 0;
}