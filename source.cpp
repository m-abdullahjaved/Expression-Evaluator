#include <iostream>
#include <string>
#include <math.h>
using namespace std;

struct Stack {
	char data;
	Stack* next;
};
Stack* top = NULL;

bool isEmpty() {
	return top == NULL;
}
void push(char val) {
	Stack* newNode = new Stack;
	newNode->data = val;
	newNode->next = top;
	top = newNode;
}

int pop() {
	if (isEmpty()) {
		return -1;
	}
	else {
		Stack* temp = top;
		int dat = top->data;
		top = top->next;
		delete temp;
		return dat;
	}
}
int peek() {
	if (!isEmpty())
		return top->data;
	else
		return -1;
}
void displayStack() {
	Stack* temp = top;
	while (temp != NULL) {
		cout << temp->data << "->";
		temp = temp->next;
	}
	cout << endl;
}
bool isOperand(char ch) {
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
		return true;
	else
		return false;
}
int precedence(char op) {
	switch (op)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
	case '%':
		return 2;
	case '^':
		return 3;
	default:
		return -1;
	}
}
string infixToPostfix(string exp) {
	string temp = "";
	for (int i = 0; exp[i] != '\0'; i++) {
		// If operand is encountered then output it.
		if (isOperand(exp[i])) {
			temp += exp[i];
		}
		else {
			if (exp[i] == '(') {
				push(exp[i]);
			}
			else if (exp[i] == ')') {
				while (peek() != '(') {
					temp += pop();
				}
				// removes the '(' bracket
				pop();
			}
			else { // Operator other then brackets
				while (!isEmpty() && precedence(peek()) > precedence(exp[i]) && peek() != '(') {
					temp += pop();
				}
				// push the operator into stack
				push(exp[i]);
			}
		}
	}
	// operators at the end should now be popped and added into output
	while (!isEmpty()) {
		temp += pop();
	}
	return temp;
}
int postfixEvaluation(string exp) {
	int x = 0, y = 0, temp = 0;
	for (int i = 0; exp[i] != '\0'; i++) {
		if (isOperand(exp[i])) {
			push(exp[i] - '0');
		}
		else {
			x = pop();
			y = pop();
			/* Switch Statement for Operator checker*/
			switch (exp[i]) {
			case '+':
				temp = y + x; break;
			case '-':
				temp = y - x; break;
			case '/':
				temp = y / x; break;
			case '*':
				temp = y * x; break;
			case '%':
				temp = y % x; break;
			case '^':
				temp = pow(y, x); break;
			}
			push(temp);
		}
	}
	return pop();
}
int main() {
	string exp = "(3+1)/(1+1)";
	string temp = infixToPostfix(exp);
	cout << "Postfix Form: " << temp << endl;
	cout << "Result : " << postfixEvaluation(temp) << endl;
	return 0;
}

