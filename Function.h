/******
Lance Regala
April 7, 2013
CISP430 - Dixon
*******/

#ifndef LREGALA_FUNCTION_H
#define LREGALA_FUNCTION_H
#include"Token.h"
#include<string>

class Function : public Token
{
public:
	Function() : Token() { }
	~Function() { } 
	// polymorphic override returns true for the Operator class
	virtual bool isFunction() { return true; }
	Function& operator=(const Function& rhs)
	{
		if (this == &rhs)
			return *this;
		_token = rhs._token;
		return *this;
	}
};

#endif