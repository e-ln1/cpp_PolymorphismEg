/*******
Lance Regala
April 7, 2013
CISP430 - Dixon
*******/

#ifndef LREGALA_EVAL_H
#define LREGALA_EVAL_H
#include<cstdlib>
#include<cmath>
#include<cctype>
#include"Stack.h"
#include"SymbolTable.h"
#include"Postfix.h"
#include"Operand.h"
#include"Operator.h"

class Eval
{
private:
	Stack<double> _evaluationStack;
	SymbolTable<Operand*> _stlist;
public:
	Eval();
	~Eval();
	// getter
	SymbolTable<Operand*> getStlist() { return _stlist; }
	//facilitators
	bool checkStlist(Operand* sym)
	{
		ListEntry<Operand*>* ptrCurrent = _stlist.getFirst();
		while(ptrCurrent != NULL)
		{
			if (sym->getToken() == ptrCurrent->getData()->getToken())
				return true;
			ptrCurrent = ptrCurrent->getLinknext();
		}
		return false;
	}
	double getStlistOperandVal(const Operand* sym)
	{
		ListEntry<Operand*>* ptrCurrent = _stlist.getFirst();
		while(ptrCurrent != NULL)
		{
			if (sym->getToken() == ptrCurrent->getData()->getToken())
				return ptrCurrent->getData()->getValue();
			ptrCurrent = ptrCurrent->getLinknext();
		}
		return ptrCurrent->getData()->getValue();
	}
	void addStlistItem(Operand* N)
	{
		_stlist.insert_sortedly(N);
	}
	Operand assignCalculatedExpressionToLHS(Postfix exp);
};

Eval::Eval() : _evaluationStack(Stack<double>())
{
	Operand* A = new Operand;
	Operand* B = new Operand;
	Operand* C = new Operand;
	Operand* D = new Operand;
	A->setValue(5);  A->setToken("A");
	B->setValue(10); B->setToken("B");
	C->setValue(-1); C->setToken("C");
	D->setValue(2);  D->setToken("D");
	_stlist.insert_sortedly(B);
	_stlist.insert_sortedly(C);
	_stlist.insert_sortedly(D);
	_stlist.insert_sortedly(A);
}

Eval::~Eval()
{
	if (_stlist.stlist_isEmpty())
	{
		ListEntry<Operand*>* ptrCurrent = this->_stlist.getFirst();
		ListEntry<Operand*>* ptrTemp;

		while (ptrCurrent != NULL)
		{
			ptrTemp = ptrCurrent;
			ptrCurrent = ptrCurrent->getLinknext();
			delete ptrTemp;
		}
	}
}

Operand Eval::assignCalculatedExpressionToLHS(Postfix exp)
{
	Operand LHS;
	double solution;
	if (exp.isEmpty())
	{
		LHS.setToken("AN INVALID SOLUTION");
		LHS.setValue(0);
		return LHS;
	}
	if (exp.getHeader()->getData()->isOperand() && *exp.getFooter()->getData() == "=")
	{
		// assign the string from the first Operand to the LHS
		LHS.setToken(exp.getHeader()->getData()->getToken());

		// look at the first Item after the assignment variable
		ListEntry<Token*>* iteratorNode = exp.getHeader()->getLinknext();
		// iterate through the expression, one Token at a time
		while (iteratorNode->getData()->getToken() != "=")
		{
			if (iteratorNode->getData()->isOperand())
			{
				double value;
				Operand* temp = new Operand;
				temp->setToken(iteratorNode->getData()->getToken());
				// check the symbol table for the Operand, 
				// push the value from the symbol table onto the _eval stack
				if (checkStlist(temp))
				{
					value = getStlistOperandVal(temp);
					_evaluationStack.push(value);
				}
				else // is it a numerical entry?
				{
					bool isval = true;
					for(int i=0;i<(temp->getToken().size());i++)
					{
						if (isdigit(temp->getToken()[i])) // test individual characters
							continue;
						else
							isval = false;
					}
					if (isval) // then convert to value and push onto the _eval stack
					{
						value = stod(temp->getToken()); // string to double conversion
						_evaluationStack.push(value);
					}
				}
			}
			else if (iteratorNode->getData()->isFunction()) // IS IT A FUNCTION???
			{
				double num1; // pop, evaluate, push
				string func;
				// pop... once from the _eval stack, perform the operation
				if (!(_evaluationStack.stack_isEmpty())) // if the _eval stack isn't empty
					num1 = _evaluationStack.pop(num1);	// ***pop*** num1
				else
				{
					cout << "SYNTAX error in expression evaluation." << endl;
					break;
				}
				// ***evaluate, push***
				func = iteratorNode->getData()->getToken(); // initialize func to token
				if (func == "sin" || func == "SIN")
					_evaluationStack.push(sin(num1));
				else if (func == "cos" || func == "COS")
					_evaluationStack.push(cos(num1));
				else if (func == "abs" || func == "ABS")
					_evaluationStack.push(abs(num1));
				else if (func == "sqrt" || func == "SQRT")
					_evaluationStack.push(sqrt(num1));
				else
					cout << "Invalid FUNCTION. How could this even occur?" << endl;				;
			}
			else if (iteratorNode->getData()->isOperator())
			{
				double num1, num2;
				string op;
				// pop... pop... from the _eval stack, slip the operator in between
				if (!(_evaluationStack.stack_isEmpty())) // if the _eval stack isn't empty
					num1 = _evaluationStack.pop(num1);	// ***pop*** num1
				else
				{
					cout << "SYNTAX error in expression evaluation." << endl;
					break;
				}
				if (!(_evaluationStack.stack_isEmpty())) // if the _eval stack isn't empty
					num2 = _evaluationStack.pop(num2);	// ***pop*** num2
				else
				{
					cout << "SYNTAX error in expression evaluation." << endl;
				}
				// ***evaluate, push***
				op = iteratorNode->getData()->getToken();
				if (op == "+")
					_evaluationStack.push(num2 + num1);
				else if (op == "-")
					_evaluationStack.push(num2 - num1);
				else if (op == "*")
					_evaluationStack.push(num2 * num1);
				else if (op == "/")
					_evaluationStack.push(num2 / num1);
				else if (op == "=")
					continue;
				else
					cout << "Evaluation Error, invalid Operator found." << endl;
			}
			//
			iteratorNode = iteratorNode->getLinknext();
		}
		LHS.setValue(_evaluationStack.pop(solution));
	}
	else
		cout << "Invalid assignment." << endl;
	return LHS;
}

#endif