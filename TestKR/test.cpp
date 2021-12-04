#include "pch.h"
#include "gtest/gtest.h"
#include "..\Курсовая работа\ReversePolishNotation.h"
#include "..\Курсовая работа\Calculator.h"
#include <fstream>

class Test_ReversePolishNotation : public ::testing::Test {
public:
	string str;
	Queue<char>* queue = new Queue<char>;
};

TEST_F(Test_ReversePolishNotation, Test_RPN) {
	// Expression with the same priority of operations
	str = "2+3-4+5";
	queue = ReversePolishNotation(str);
	//2 3+4-5+ 
	ASSERT_EQ(queue->deQueue(), '2'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '3'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '+'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '4'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '-'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '5'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '+');
	str.clear();
	queue->~Queue();

	// Expression with not the same priority of operations
	str = "2^3*3-6/4";
	queue = ReversePolishNotation(str);
	//2 3^3*6 4/-
	ASSERT_EQ(queue->deQueue(), '2'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '3'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '^'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '3'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '*'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '6'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '4'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '/'); queue->deQueue();
	ASSERT_EQ(queue->deQueue(), '-');
	str.clear();
	queue->~Queue();

	//Expressions with trigonometric functions
	str = "cos(pi/2)-sin(2pi)";
	queue = ReversePolishNotation(str);
	//cos(pi 2/) sin(2 pi*) - 
	ASSERT_EQ(queue->deQueue(), 'c');
	ASSERT_EQ(queue->deQueue(), 'o');
	ASSERT_EQ(queue->deQueue(), 's');
	ASSERT_EQ(queue->deQueue(), '(');
	ASSERT_EQ(queue->deQueue(), 'p');
	ASSERT_EQ(queue->deQueue(), 'i');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), '2');
	ASSERT_EQ(queue->deQueue(), '/');
	ASSERT_EQ(queue->deQueue(), ')');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), 's');
	ASSERT_EQ(queue->deQueue(), 'i');
	ASSERT_EQ(queue->deQueue(), 'n');
	ASSERT_EQ(queue->deQueue(), '(');
	ASSERT_EQ(queue->deQueue(), '2');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), 'p');
	ASSERT_EQ(queue->deQueue(), 'i');
	ASSERT_EQ(queue->deQueue(), '*');
	ASSERT_EQ(queue->deQueue(), ')');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), '-');
	str.clear();
	queue->~Queue();

	//Expressions with logarithmic and other functions
	str = "ln(e)-4!/sqrt(3)";
	queue = ReversePolishNotation(str);
	//ln(e) 4! sqrt(3) /- 
	ASSERT_EQ(queue->deQueue(), 'l');
	ASSERT_EQ(queue->deQueue(), 'n');
	ASSERT_EQ(queue->deQueue(), '(');
	ASSERT_EQ(queue->deQueue(), 'e');
	ASSERT_EQ(queue->deQueue(), ')');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), '4');
	ASSERT_EQ(queue->deQueue(), '!');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), 's');
	ASSERT_EQ(queue->deQueue(), 'q');
	ASSERT_EQ(queue->deQueue(), 'r');
	ASSERT_EQ(queue->deQueue(), 't');
	ASSERT_EQ(queue->deQueue(), '(');
	ASSERT_EQ(queue->deQueue(), '3');
	ASSERT_EQ(queue->deQueue(), ')');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), '/');
	ASSERT_EQ(queue->deQueue(), ' ');
	ASSERT_EQ(queue->deQueue(), '-');
	str.clear();
	queue->~Queue();

	//When there is a space in the expression.
	str = "2 - 9 - 0 - 7";
	ASSERT_THROW(queue = ReversePolishNotation(str), runtime_error);
	str.clear();
	queue->~Queue();

	//When the brackets are not balanced.
	str = "(5+6)*(7-8";
	ASSERT_THROW(queue = ReversePolishNotation(str), logic_error);
	str.clear();
	queue->~Queue();

	//When negative number is not in parentheses.
	str = "4*-3+5/6";
	ASSERT_THROW(queue = ReversePolishNotation(str), logic_error);
	str.clear();
	queue->~Queue();

	//When 2 operators are in a row
	str = "4*/3+5/6";
	ASSERT_THROW(queue = ReversePolishNotation(str), logic_error);
	str.clear();
	queue->~Queue();

	//When missing number
	str = "4*3+5/6+";
	ASSERT_THROW(queue = ReversePolishNotation(str), logic_error);
	str.clear();
	queue->~Queue();

	//When the parameter of the cos/sin/tg/ctg/ln/log/sqrt function is not in parentheses.
	str = "cos-pi*lne-sqrt9";
	ASSERT_THROW(queue = ReversePolishNotation(str), logic_error);
	str.clear();
	queue->~Queue();

	//When the factorial function was entered incorrectly.
	str = "!2 - 3";
	ASSERT_THROW(queue = ReversePolishNotation(str), logic_error);
	str.clear();
	queue->~Queue();

	//When there are strange characters in the expression
	str = "cos(x)=sin(x)";
	ASSERT_THROW(queue = ReversePolishNotation(str), runtime_error);
	str.clear();
	queue->~Queue();
}

class Test_Calculator : public ::testing::Test {
public:
	string str;
	Queue<char>* queue = new Queue<char>;
};

TEST_F(Test_Calculator, Test_Calculator) {
	//Example of an expression
	str = "(2*4-3)!-(cos(3pi)-sin(2pi))*(tg(pi/4)+ctg(pi/4))-ln(e)*log(10^3)-sqrt(9)";
	queue = ReversePolishNotation(str);
	ASSERT_DOUBLE_EQ(Calculator(queue), 116);
	str.clear();
	queue->~Queue();

	//When divisor of division equals 0
	str = "29/0-7";
	queue = ReversePolishNotation(str);
	ASSERT_THROW(Calculator(queue), logic_error);
	str.clear();
	queue->~Queue();

	//The parameter of the factorial function is not a non-negative integer
	str = "(-7.29)!";
	queue = ReversePolishNotation(str);
	ASSERT_THROW(Calculator(queue), logic_error);
	str.clear();
	queue->~Queue();

	//When tg(x) does not exist (x = k*pi/2)
	str = "tg(pi/2)";
	queue = ReversePolishNotation(str);
	ASSERT_THROW(Calculator(queue), logic_error);
	str.clear();
	queue->~Queue();

	//When ctg(x) does not exist (x = k*pi)
	str = "ctg(pi)";
	queue = ReversePolishNotation(str);
	ASSERT_THROW(Calculator(queue), logic_error);
	str.clear();
	queue->~Queue();

	//The parameter of the function 'ln' is non-positive
	str = "ln(0)";
	queue = ReversePolishNotation(str);
	ASSERT_THROW(Calculator(queue), logic_error);
	str.clear();
	queue->~Queue();

	//The parameter of the function 'log' is non-positive
	str = "log(0)";
	queue = ReversePolishNotation(str);
	ASSERT_THROW(Calculator(queue), logic_error);
	str.clear();
	queue->~Queue();

	//The parameter of the square root function is negative
	str = "sqrt(-29)";
	queue = ReversePolishNotation(str);
	ASSERT_THROW(Calculator(queue), logic_error);
	str.clear();
	queue->~Queue();
}

class Test_Stack : public ::testing::Test {
public:
	void SetStack(Stack<int>* stack) {
		for (int i = 1; i <= 5; i++)
			stack->push(i);
	}
};

TEST_F(Test_Stack, Test_isEmpty) {
	Stack<int>* stack = new Stack<int>;
	ASSERT_TRUE(stack->isEmpty());
	ASSERT_EQ(stack->size, 0);

	SetStack(stack);
	ASSERT_FALSE(stack->isEmpty());
	ASSERT_NE(stack->size, 0);
}

TEST_F(Test_Stack, Test_contains) {
	Stack<int>* stack = new Stack<int>;
	ASSERT_THROW(stack->contains(7), runtime_error);

	SetStack(stack);
	ASSERT_TRUE(stack->contains(5));
	ASSERT_FALSE(stack->contains(7));
}

TEST_F(Test_Stack, Test_push) {
	Stack<int>* stack1 = new Stack<int>;
	stack1->push(7);
	ASSERT_EQ(stack1->size, 1);
	ASSERT_EQ(stack1->pop(), 7);

	Stack<int>* stack2 = new Stack<int>;
	SetStack(stack2);
	ASSERT_EQ(stack2->size, 5);
	ASSERT_EQ(stack2->pop(), 5);
	ASSERT_EQ(stack2->pop(), 4);
	ASSERT_EQ(stack2->pop(), 3);
	ASSERT_EQ(stack2->pop(), 2);
	ASSERT_EQ(stack2->pop(), 1);
}

TEST_F(Test_Stack, Test_pop) {
	Stack<int>* stack = new Stack<int>;
	ASSERT_THROW(stack->pop(), runtime_error);

	SetStack(stack);
	ASSERT_EQ(stack->pop(), 5);
	ASSERT_EQ(stack->size, 4);
	ASSERT_EQ(stack->pop(), 4);
	ASSERT_EQ(stack->size, 3);
	ASSERT_EQ(stack->pop(), 3);
	ASSERT_EQ(stack->size, 2);
	ASSERT_EQ(stack->pop(), 2);
	ASSERT_EQ(stack->size, 1);
	ASSERT_EQ(stack->pop(), 1);
	ASSERT_TRUE(stack->isEmpty());
}

class Test_Queue : public ::testing::Test {
public:
	void SetQueue(Queue<int>* queue) {
		for (int i = 1; i <= 5; i++)
			queue->enQueue(i);
	}
};

TEST_F(Test_Queue, Test_isEmpty) {
	Queue<int>* queue1 = new Queue<int>;
	ASSERT_TRUE(queue1->isEmpty());
	ASSERT_EQ(queue1->size, 0);

	SetQueue(queue1);
	ASSERT_FALSE(queue1->isEmpty());
	ASSERT_NE(queue1->size, 0);
}

TEST_F(Test_Queue, Test_contains) {
	Queue<int>* queue = new Queue<int>;
	ASSERT_THROW(queue->contains(7), runtime_error);

	SetQueue(queue);
	ASSERT_TRUE(queue->contains(5));
	ASSERT_FALSE(queue->contains(7));
}

TEST_F(Test_Queue, Test_enQueue) {
	Queue<int>* queue1 = new Queue<int>;
	queue1->enQueue(7);
	ASSERT_EQ(queue1->size, 1);
	ASSERT_EQ(queue1->deQueue(), 7);

	Queue<int>* queue2 = new Queue<int>;
	SetQueue(queue2);
	ASSERT_EQ(queue2->size, 5);
	ASSERT_EQ(queue2->deQueue(), 1);
	ASSERT_EQ(queue2->deQueue(), 2);
	ASSERT_EQ(queue2->deQueue(), 3);
	ASSERT_EQ(queue2->deQueue(), 4);
	ASSERT_EQ(queue2->deQueue(), 5);
}

TEST_F(Test_Queue, Test_deQueue) {
	Queue<int>* queue1 = new Queue<int>;
	ASSERT_THROW(queue1->deQueue(), runtime_error);

	Queue<int>* queue2 = new Queue<int>;
	SetQueue(queue2);
	ASSERT_EQ(queue2->deQueue(), 1);
	ASSERT_EQ(queue2->size, 4);
	ASSERT_EQ(queue2->deQueue(), 2);
	ASSERT_EQ(queue2->size, 3);
	ASSERT_EQ(queue2->deQueue(), 3);
	ASSERT_EQ(queue2->size, 2);
	ASSERT_EQ(queue2->deQueue(), 4);
	ASSERT_EQ(queue2->size, 1);
	ASSERT_EQ(queue2->deQueue(), 5);
	ASSERT_TRUE(queue2->isEmpty());
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}