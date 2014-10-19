/*******
Lance Regala
April 7, 2013
CISP430 - Dixon
*******/

#ifndef LREGALA_EXPRESSION_H
#define LREGALA_EXPRESSION_H

#include"List.h"
#include"Token.h"

class Expression : public List<Token*>
{
private:
public:
	// ctor/dtor
	Expression() : List<Token*>() {}	// construction
	~Expression() {}					// destruction
};

#endif