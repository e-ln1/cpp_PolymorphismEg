/**********
Lance Regala
March 5, 2013
CISP430 Dixon
**********/

#ifndef LREGALA_STACK_H
#define LREGALA_STACK_H
#include"List.h"

template<typename ITEM>
class Stack : private List<ITEM> // PRIVATE inheritance 
								// hides the base interface outside the object
{
	// Stack has no additional private members.
public:
	Stack() : List() // <---
	{} // When Stack is initialized it creates an instance of the base class.
	~Stack() {}	// ...
	void push(const ITEM& obj);
	ITEM& pop(ITEM& popped);
	const ITEM& showTop();
	bool stack_isEmpty() const;
	ListEntry<ITEM>* getTop();
};

template<typename ITEM>
void Stack<ITEM>::push(const ITEM& obj)
{
	insert_ATSTART(obj);
}
template<typename ITEM>
ITEM& Stack<ITEM>::pop(ITEM& popped)
{
	return delete_FROMHEAD(popped);
}
template<typename ITEM>
const ITEM& Stack<ITEM>::showTop()
{
	return getStart();
}
template<typename ITEM>
bool Stack<ITEM>::stack_isEmpty() const
{
	return isEmpty();
}
template<typename ITEM>
ListEntry<ITEM>* Stack<ITEM>::getTop()
{
	return getHead();
}

#endif