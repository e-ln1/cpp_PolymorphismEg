/*******
Lance Regala
April 7, 2013
CISP430 - Dixon
*******/

#ifndef LREGALA_POSTFIX_H
#define LREGALA_POSTFIX_H
#include"Expression.h"
#include"Queue.h"

class Postfix : public Expression
{
private:
public:
	// ctor/dtor
	Postfix() : Expression() { }	// construction
	~Postfix() {}					// destruction
	ListEntry<Token*>* getHeader() { return this->getHead(); }
	ListEntry<Token*>* getFooter() { return this->getTail(); }
	Postfix& operator= (List<Token*>& rhs)
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
	Postfix& operator+= (Token* rhs)
	{
		this->insert_ATEND(rhs);
		return *this;
	}
};

#endif