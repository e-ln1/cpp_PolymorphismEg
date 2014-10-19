/**********
Lance Regala
March 5, 2013
CISP430 Dixon
**********/

#ifndef LREGALA_LISTENTRY_H
#define LREGALA_LISTENTRY_H
#include<cstdlib> // providing NULL

// template<typename ITEM> class List;
// update: List "unfriended" per class discussion
// List utilizes ListEntry's interface...

template<typename ITEM>
class ListEntry
{
	//friend class List<ITEM>;//

private:
	ITEM _data;
	ListEntry<ITEM>* _ptr_next;
	ListEntry<ITEM>* _ptr_prev;
public:
	ListEntry(const ITEM& data=ITEM(), ListEntry<ITEM>* next=NULL, ListEntry<ITEM>* prev=NULL);
	~ListEntry();
	const ITEM& getData() const;
	const ITEM& getNext() const;
	const ITEM& getPrev() const;
	ListEntry<ITEM>* getLinknext();
	ListEntry<ITEM>* getLinkprev();
	bool hasNext();
	bool hasPrev();
	void setData(const ITEM& newdata);
	void setNext(ListEntry<ITEM>* newnext);
	void setPrev(ListEntry<ITEM>* newprev);
	ListEntry<ITEM>* operator=(const ListEntry<ITEM>* copy);
};
	// the default Node constructor //
template<typename ITEM>
ListEntry<ITEM>::ListEntry(const ITEM& data=ITEM(), 
	ListEntry<ITEM>* next=NULL, ListEntry<ITEM>* prev=NULL)
{
	_data = data;
	_ptr_next = next;
	_ptr_prev = prev;
}
template<typename ITEM>
ListEntry<ITEM>::~ListEntry()
{	
	// Despite the existence of pointers as data members, 
	// destructor implementation is empty here.
	// List is responsible for removing all notions of ListEntry //
}
	// getter definitions //
template<typename ITEM>
const ITEM& ListEntry<ITEM>::getData() const
{
	return _data;
}
template<typename ITEM>
const ITEM& ListEntry<ITEM>::getNext() const
{
	ListEntry<ITEM>* ptrCursor;
	if (_ptr_next != NULL)
	{
		ptrCursor = _ptr_next;
		return ptrCursor->_data;
	}
	else
		return NULL;
}
template<typename ITEM>
const ITEM& ListEntry<ITEM>::getPrev() const
{
	ListEntry<ITEM>* ptrCursor;
	if (_ptr_prev != NULL)
	{
		ptrCursor = _ptr_prev;
		return ptrCursor->_data;
	}
	else
		return NULL;
}
template<typename ITEM>
ListEntry<ITEM>* ListEntry<ITEM>::getLinknext()			
{
	return _ptr_next;
}
template<typename ITEM>
ListEntry<ITEM>* ListEntry<ITEM>::getLinkprev()
{
	return _ptr_prev;
}

	// validation utilities for List bounds
template<typename ITEM>
bool ListEntry<ITEM>::hasNext()
{
	return (_ptr_next != NULL);
}
template<typename ITEM>
bool ListEntry<ITEM>::hasPrev()
{
	return (_ptr_prev != NULL);
}
	// setter definitions //
template<typename ITEM>
void ListEntry<ITEM>::setData(const ITEM& newdata)
{
	_data = newdata;
}
template<typename ITEM>
void ListEntry<ITEM>::setNext(ListEntry<ITEM>* newnext)
{
	_ptr_next = newnext;
}
template<typename ITEM>
void ListEntry<ITEM>::setPrev(ListEntry<ITEM>* newprev)
{
	_ptr_prev = newprev;
}

	// operator overload //
template<typename ITEM>
ListEntry<ITEM>* ListEntry<ITEM>::operator=(const ListEntry<ITEM>* rhs)
{
	if(this == rhs)
		return *this;
	_data = rhs._data;
	_ptr_prev = rhs->_ptr_prev;
	_ptr_next = rhs->_ptr_next;
	return *this;
}

#endif