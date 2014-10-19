/*******
Lance Regala
April 7, 2013
CISP430 - Dixon
*******/

#ifndef LREGALA_OPERAND_H
#define LREGALA_OPERAND_H
#include"Token.h"
#include<string>

class Operand : public Token
{
private:
	double _value;
public:
	Operand() : Token() { }
	~Operand() { }
	virtual bool isOperator() { return false; }
	virtual bool isOperand() { return true; }
	const double getValue() { return _value; }
	void setValue(const double newval) { _value = newval; }
	Operand& operator=(const Operand& rhs)
	{
		if (this == &rhs)
			return *this;
		_value = rhs._value;
		_token = rhs._token;
		return *this;
	}
};

#endif