/**********
Lance Regala
March 5, 2013
CISP430 Dixon
**********/

#ifndef LREGALA_LIST_H
#define LREGALA_LIST_H
#include<iostream>
#include<cstdlib>
#include<fstream>
#include"ListEntry.h"
using namespace std;

template<typename ITEM>
class List
{
protected:
	ListEntry<ITEM>* _ptr_head;
	ListEntry<ITEM>* _ptr_tail;
	int _counter;		// stores the number of ListEntries currently in the List
private:
	ListEntry<ITEM>* newEntry_ADDR(const ITEM& type) { return new ListEntry<ITEM>(type); }
public:
	List();
	List(const List& copy)
	{
		this->_ptr_head = NULL;
		this->_ptr_tail = NULL;
		this->_counter = 0;
		ListEntry<ITEM>* ptrCurrent = copy._ptr_head;
		while (ptrCurrent != NULL)
		{
			this->insert_ATEND(ptrCurrent->getData());
			ptrCurrent = ptrCurrent->getLinknext();
		}
	}
	~List();
	const ITEM& getStart();
	const ITEM& getEnd();
	ListEntry<ITEM>* getHead();
	ListEntry<ITEM>* getTail();
	int getCounter();
	void insert_ATSTART(const ITEM&);
	void insert_ATEND(const ITEM&);
	void insert_INTOMIDDLE(const ITEM&);
	void insert_ASCENDING(const ITEM& type);
	ITEM& delete_FROMHEAD(ITEM& deleted);
	ITEM& delete_FROMTAIL(ITEM& deleted);
	bool isEmpty() const;
	bool isFull() const;
	bool search_unsorted(const ITEM& target);
	ListEntry<ITEM>* returnFirstMatch(const ITEM& target);
	void bubble_sort(bool order);
	List<ITEM>& operator= (const List<ITEM>& rhs)
	{
		if (this==&rhs)
			return *this;
		delete [] _ptr_head;
		delete [] _ptr_tail;
		this->_ptr_head = NULL;
		this->_ptr_tail = NULL;
		this->_counter = 0;
		ListEntry<ITEM>* ptrCurrent = rhs._ptr_head;
		while (ptrCurrent != NULL)
		{
			this->insert_ATEND(ptrCurrent->getData());
			ptrCurrent = ptrCurrent->getLinknext();
		}		
		return *this;
	}
};

template<typename ITEM>
List<ITEM>::List()
	: _ptr_head(NULL), _ptr_tail(NULL), _counter(0)
{
	// {default Constructor} ...empty brackets
}

template<typename ITEM>
List<ITEM>::~List()
{
	if (isEmpty())
	{
		ListEntry<ITEM>* ptrCurrent = _ptr_head;
		ListEntry<ITEM>* ptrTemp;

		while (ptrCurrent != NULL)
		{
			ptrTemp = ptrCurrent;
			ptrCurrent = ptrCurrent->getLinknext();
			delete ptrTemp;
		}
	}
}
template<typename ITEM>
const ITEM& List<ITEM>::getStart()
{
	return _ptr_head->getData();
}
template<typename ITEM>
const ITEM& List<ITEM>::getEnd()
{
	return _ptr_tail->getData();
}
template<typename ITEM>
ListEntry<ITEM>* List<ITEM>::getHead()
{
	return _ptr_head;
}
template<typename ITEM>
ListEntry<ITEM>* List<ITEM>::getTail()
{
	return _ptr_tail;
}

template<typename ITEM>
int List<ITEM>::getCounter()
{
	return _counter;
}

template<typename ITEM>
void List<ITEM>::insert_ATSTART(const ITEM& type)
{
	if (isFull()) // verify that memory is available
		return;
	ListEntry<ITEM>* ptrType = newEntry_ADDR(type);
	
	if (isEmpty())	// if the List is empty: the new List now has only one Node
	{
		_ptr_head = _ptr_tail = ptrType;
		++_counter;
	}
	else	// else the List is NOT empty: 
	{
			// point newNode's _ptr_next at the old first node
		ptrType->setNext(_ptr_head);
			// point the old _ptr_head's ptr_prev back at newNode
		_ptr_head->setPrev(ptrType);
			// and then replace _ptr_head point with this new Node as the List head
		_ptr_head = ptrType;
				// the old Node address is still there, only _ptr_head has changed
		++_counter; // increment the counter
	}
}
template<typename ITEM>
void List<ITEM>::insert_ATEND(const ITEM& type)
{
	if (isFull()) // verify that memory is available
		return;
	ListEntry<ITEM>* ptrType = newEntry_ADDR(type);

	if (isEmpty())	// if the List is empty: the new List now has only one Node
	{
		_ptr_head = _ptr_tail = ptrType;
		++_counter;
	}
	else	// else the List is NOT empty:
	{
			// update the old tail's _ptr_next to point to newdata's newNode
		_ptr_tail->setNext(ptrType);
			// point newNode's linkprev at the old tail
		ptrType->setPrev(_ptr_tail);
			// and reassign _ptr_tail to ptr_newNode
		_ptr_tail = ptrType;
			// increment counter
		++_counter;
	}
}
template<typename ITEM>
void List<ITEM>::insert_INTOMIDDLE(const ITEM& type)
{
	if (isFull()) // verify that memory is available
		return;
	ListEntry<ITEM>* ptrType = newEntry_ADDR(type);
		// there must be at least two entries for an actual INTOMIDDLE insert
	if (isEmpty())	// if the List is empty: the new List now has only one Node
	{
		_ptr_head = _ptr_tail = ptrType;
		++_counter;
	}
	else if (_ptr_head == _ptr_tail && _ptr_head != NULL) // if there is only 1 entry:
	{		// in my design, we will insert_ATEND here...
			// update the old tail to point to newdata's new ptrType
		_ptr_tail->setNext(ptrType);
			// point newNode's linkprev at the old tail
		ptrType->setPrev(_ptr_tail);
			// and reassign _ptr_tail to the new ptrType
		_ptr_tail = ptrType;
			// increment counter
		++_counter;
	}
	else	// there are at least 2 entries:
			// _ptr_head and _ptr_tail will not change;
			// the entry will be inserted between them...
	{
		ListEntry<ITEM>* ptrCurrent = _ptr_head;
		for (int i = 0; i<(_counter/2)-1; i++)
			ptrCurrent = ptrCurrent->getLinknext();
		ListEntry<ITEM>* ptrNext = ptrCurrent->getLinknext();

			// ...make ptrCurrent's _ptr_next point to ptrType's node
		ptrCurrent->setNext(ptrType);
			// ...make ptrType's _ptr_prev point to Current's node
		ptrType->setPrev(ptrCurrent);
			// ...make ptrNext's _ptr_prev point to ptrType's node
		ptrNext->setPrev(ptrType);
			// ...make ptrType's _ptr_next point to Next's node
		ptrType->setNext(ptrNext);
			// ++_counter
		++_counter;
	}
}

template <typename ITEM>
void List<ITEM>::insert_ASCENDING(const ITEM& type)
{
	if (isFull()) // verify that memory is available
		return;

	ListEntry<ITEM>* ptrCursor1 = newEntry_ADDR(type);
		// there must be at least 1 existing entry for an actual SORTED insert

	if (isEmpty())	// if the List is empty: the new List now has only one Node
	{
		_ptr_head = _ptr_tail = ptrCursor1;
		++_counter;
		return;
	}
			// compare the new entry with _ptr_head
			// and insert above the old head if the new data is the lesser
	if (ptrCursor1->getData() < _ptr_head->getData())
	{
			// point newNode's _ptr_next at the old first node
		ptrCursor1->setNext(_ptr_head);
			// point the old _ptr_head's ptr_prev back at newNode
		_ptr_head->setPrev(ptrCursor1);
			// and then replace _ptr_head point with this new Node as the List head
		_ptr_head = ptrCursor1;
				// the old Node address is still there, only _ptr_head has changed
		++_counter; // increment the counter
		return;
	}
			// compare the incoming data with the tail
			// and insert it after the tail if the new data is the greater
	if (ptrCursor1->getData() > _ptr_tail->getData())
	{
			// update the old tail's _ptr_next to point to newdata's newNode
		_ptr_tail->setNext(ptrCursor1);
			// point newNode's linkprev at the old tail
		ptrCursor1->setPrev(_ptr_tail);
			// and reassign _ptr_tail to ptr_newNode
		_ptr_tail = ptrCursor1;
			// increment counter
		++_counter;
		return;
	}
	else  // the incoming data must be inserted between the head and the tail
	{
		ListEntry<ITEM>* ptrCursor2 = _ptr_head;
			// scroll through the list to find the point of insertion
		while (!(ptrCursor1->getData() < ptrCursor2->getData()))
			ptrCursor2 = ptrCursor2->getLinknext();
		ListEntry<ITEM>* ptrPrev = ptrCursor2->getLinkprev();
					//...very similar to an insert_INTOMID now:
			// ...make ptrPrev's _ptr_next point to ptrCursor1's node
		ptrPrev->setNext(ptrCursor1);
			// ...make ptrCursor1's _ptr_prev point to Prev's node
		ptrCursor1->setPrev(ptrPrev);
			// ...make ptrCursor2's _ptr_prev point to ptrCursor1's node
		ptrCursor2->setPrev(ptrCursor1);
			// ...make ptrCursor1's _ptr_next point to Cursor2's node
		ptrCursor1->setNext(ptrCursor2);
			// ++_counter
		++_counter;
		return;
	}
}

template<typename ITEM>
ITEM& List<ITEM>::delete_FROMHEAD(ITEM& deleted)
{
	if(isEmpty())
		return deleted;
	else
	{
		ListEntry<ITEM>* ptrTemp = _ptr_head;

		if (_ptr_head == _ptr_tail)
			_ptr_head = _ptr_tail = NULL;
		else
			_ptr_head = _ptr_head->getLinknext();
		--_counter;
		deleted = ptrTemp->getData();
		delete ptrTemp;
		return deleted;
	}
}
template<typename ITEM>
ITEM& List<ITEM>::delete_FROMTAIL(ITEM& deleted)
{
	if(isEmpty())
		return deleted;
	else
	{
		ListEntry<ITEM>* ptrTemp = _ptr_tail;

		if (_ptr_tail == _ptr_head)
			_ptr_tail = _ptr_head = NULL;
		else
		{
			_ptr_tail = _ptr_tail->getLinkprev();	// Tail's _ptr_prev is now the tail
			_ptr_tail->setNext(NULL);		// make the new tail's _ptr_next NULL
		}
		--_counter;
		deleted = ptrTemp->getData();
		delete ptrTemp;
		return deleted;
	}
}
template<typename ITEM>	
bool List<ITEM>::isEmpty() const
{
	return _ptr_head == NULL;
}
template<typename ITEM>	
bool List<ITEM>::isFull() const
{
	try
	{
		ListEntry<ITEM>* ptrTest = new ListEntry<ITEM>;
		delete ptrTest;
	}
	catch (std::bad_alloc& bad)
	{
		std::cerr << "bad_alloc: [ " << bad.what() << " ] " << endl;
		return true;
	}
	return false;
}

template<typename ITEM>
bool List<ITEM>::search_unsorted(const ITEM& target)
{
	ListEntry<ITEM>* ptrCursor;

	for(ptrCursor = _ptr_head; ptrCursor != NULL; ptrCursor = ptrCursor->getLinknext())
		if (target == ptrCursor->getData())
			return true; // if the target finds a match, returns true
	return false; // false otherwise
}

template<typename ITEM>
ListEntry<ITEM>* List<ITEM>::returnFirstMatch(const ITEM& target)
{
	ListEntry<ITEM>* ptrCursor;

	for(ptrCursor = _ptr_head; ptrCursor != NULL; ptrCursor = ptrCursor->getLinknext())
	{
		if (target == ptrCursor->getData())
			return ptrCursor; // if the target finds a match, returns the address
	}
	return ptrCursor=NULL; // NULL otherwise
}

template<typename ITEM>
void List<ITEM>::bubble_sort(bool order)	// ascending = true, descending = false
{
	ListEntry<ITEM>* ptrCursor1 = _ptr_head;
	ListEntry<ITEM>* ptrCursor2 = _ptr_head;

	for(ptrCursor1 = _ptr_head; ptrCursor1 != NULL; ptrCursor1 = ptrCursor1->getLinknext())
	{
		for(ptrCursor2 = _ptr_head; ptrCursor2 != ptrCursor1; ptrCursor2 = ptrCursor2->getLinknext())
		{
			if ( order == true )	// ascending order
			{
				if (ptrCursor1->getData() < ptrCursor2->getData())
				{
					ListEntry<ITEM>* ptrTemp = new ListEntry<ITEM>;
					ptrTemp->setData(ptrCursor1->getData());
					ptrCursor1->setData(ptrCursor2->getData());
					ptrCursor2->setData(ptrTemp->getData());
					delete ptrTemp;
				}
			}
			else					// descending order
			{
				if (ptrCursor1->getData() > ptrCursor2->getData())
				{
					ListEntry<ITEM>* ptrTemp = new ListEntry<ITEM>;
					ptrTemp->setData(ptrCursor1->getData());
					ptrCursor1->setData(ptrCursor2->getData());
					ptrCursor2->setData(ptrTemp->getData());
					delete ptrTemp;
				}
			}
		}
	}
}

#endif