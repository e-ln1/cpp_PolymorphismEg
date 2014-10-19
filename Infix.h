/*******
Lance Regala
April 7, 2013
CISP430 - Dixon
*******/

#ifndef LREGALA_INFIX_H
#define LREGALA_INFIX_H
#include"Expression.h"

class Infix : public Expression
{
private:
public:
	// ctor/dtor
	Infix() : Expression() { }	// construction
	~Infix() {}					// destruction
	Infix& operator= (List<Token*>& rhs)
	{
			if (this==&rhs)
			return *this;
		delete [] _ptr_head;
		delete [] _ptr_tail;
		this->_ptr_head = NULL;
		this->_ptr_tail = NULL;
		this->_counter = 0;
		ListEntry<Token*>* ptrCurrent = rhs.getHead();
		while (ptrCurrent != NULL)
		{
			this->insert_ATEND(ptrCurrent->getData());
			ptrCurrent = ptrCurrent->getLinknext();
		}
		return *this;
	}
};

#endif