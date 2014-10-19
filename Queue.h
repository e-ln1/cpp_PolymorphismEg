/**********
Lance Regala
March 5, 2013
CISP430 Dixon
**********/

#ifndef LREGALA_QUEUE_H
#define LREGALA_QUEUE_H

#include"List.h"

using namespace std;

template<typename ITEM>
class Queue : private List<ITEM> // PRIVATE inheritance 
								// hides the base interface outside the object
{
	// Queue has no additional private members.
public:
	Queue() : List() // <---
	{}	// when Queue is initialized it creates an instance of the base class
	~Queue() {}	// There is a destructor, and its implementation is taken care of.
	void enqueue(const ITEM& obj);
	ITEM& dequeue(ITEM& dqd);
	void sort(bool order);
	bool search(const ITEM& target);
	bool queue_isEmpty() const;
	ListEntry<ITEM>* getFront();
};

template<typename ITEM>
void Queue<ITEM>::enqueue(const ITEM& obj)
{
	insert_ATEND(obj);
}
template<typename ITEM>
ITEM& Queue<ITEM>::dequeue(ITEM& dqd)
{
	return delete_FROMHEAD(dqd);
}
template<typename ITEM>
void Queue<ITEM>::sort(bool order)	// true = ascending, false = descending
{
	bubble_sort(order);
}
template<typename ITEM>
bool Queue<ITEM>::search(const ITEM& target)
{
	return search_unsorted(target);
}
template<typename ITEM>
bool Queue<ITEM>::queue_isEmpty() const
{
	return isEmpty();
}
template<typename ITEM>
ListEntry<ITEM>* Queue<ITEM>::getFront()
{
	return getHead();
}

#endif