/* Thomas Tang
* Yuan Zheng
* CIS22C
* InfixCalculator.h
*/

#ifndef INFIX_CALCULATOR_H
#define INFIX_CALCULATOR_H
#include <string>
#include "Stack.h"

class InfixCalculator {
public:
	int evaluate(std::string infix);
	std::string toPostfix(std::string infix);

private: // member functions
	bool isOp(char op);
	bool isVal(char val);
	void execute();
	int precedence(char op);

private: // member variable
	Stack<char> opStack;
	Stack<int> valStack;
};

#endif // INFIX_CALCULATOR_H