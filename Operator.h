/******
Lance Regala
April 7, 2013
CISP430 - Dixon
*******/

#ifndef LREGALA_OPERATOR_H
#define LREGALA_OPERATOR_H
#include"Token.h"

class Operator : public Token
{
public:
	Operator() : Token() {  }
	~Operator() { } 
	// polymorphic override returns true for the Operator class
	virtual bool isOperator() { return true; } //
	Operator& operator=(const Operator& rhs)
	{
		if (this == &rhs)
			return *this;
		_token = rhs._token;
		return *this;
	}
};

#endif