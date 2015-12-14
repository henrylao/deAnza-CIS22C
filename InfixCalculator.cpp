/* Thomas Tang
* Yuan Zheng
* CIS22C
* InfixCalculator.cpp
*/

#include "InfixCalculator.h"

// returns true if char op is an operator
bool InfixCalculator::isOp(char op){
	return (op == '*' || op == '/' || op == '+'
		|| op == '-');
}

// returns true if char val is a value
bool InfixCalculator::isVal(char val){
	return val >= '0' && val <= '9';
}

// evaluates the equation: operand1 op operand2
void InfixCalculator::execute(){
	int operand2 = valStack.peek(); 
	valStack.pop();

	int operand1 = valStack.peek();
	valStack.pop();

	char op = opStack.peek();
	opStack.pop();

	int result;
	switch (op){
		case '*':
			result = operand1 * operand2;
			break;
		case '/':
			result = operand1 / operand2;
			break;
		case '+':
			result = operand1 + operand2;
			break;
		case '-':
			result = operand1 - operand2;
			break;
	}
	valStack.push(result);
}

// returns 1 if * or / and returns 0 if + or -... *,/ > +,-
int InfixCalculator::precedence(char op){
	if (isOp(op)){
		if (op == '*' || op == '/') return 1;
		if (op == '-' || op == '+') return 0;
	}
	return -1;
}

// make infix expression into postfix expression
// based off algorithm from book
int InfixCalculator::evaluate(std::string infix){
	int result;
	for (unsigned int i = 0; i < infix.size(); i++){
		if (isVal(infix[i])){
			valStack.push(infix[i] - 48);
		}
		if (isOp(infix[i])){
			if (opStack.isEmpty() || 
				precedence(infix[i]) > precedence(opStack.peek())){
				opStack.push(infix[i]);
			}
			else {
				while (!opStack.isEmpty() && precedence(infix[i]) <= precedence(opStack.peek())){
					execute();
				}
				opStack.push(infix[i]);
			}
		}
		if (infix[i] == '('){
			opStack.push(infix[i]);
		}
		if (infix[i] == ')'){
			while (opStack.peek() != '('){
				execute();
			}
			opStack.pop();
		}
	}
	while (!opStack.isEmpty()){
		execute();
	}
	result = valStack.peek();

	return result;
}

// returns a string of the infix expression in postfix form
std::string InfixCalculator::toPostfix(std::string infix){
	std::string p = "";
	for (unsigned int i = 0; i < infix.size(); i++){
		if (isVal(infix[i])){
			p += infix[i];
		}
		if (isOp(infix[i])){
			while (!opStack.isEmpty() && precedence(infix[i]) <= precedence(opStack.peek())){
				p += opStack.peek();
				opStack.pop();
			}
			opStack.push(infix[i]);
		}
		if (infix[i] == '('){
			opStack.push(infix[i]);
		}
		if (infix[i] == ')'){
			while (opStack.peek() != '('){
				p += opStack.peek();
				opStack.pop();
			}
			opStack.pop();
		}

	}
	while (!opStack.isEmpty()){
		p += opStack.peek();
		opStack.pop();
	}
	return p;
}