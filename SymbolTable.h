/**********
Lance Regala
April 10, 2013
CISP430 Dixon
**********/

#ifndef LREGALA_SYMBOLTABLE_H_
#define LREGALA_SYMBOLTABLE_H_
#include"List.h"
#include"Token.h"

template <typename ITEM>
class SymbolTable : private List<ITEM> // an ordered, linked list of symbols
{
public:
	SymbolTable() : List()
	{	}
	SymbolTable(const SymbolTable& copy) : List(copy)
	{ 	}
	~SymbolTable() {}
	void insert_sortedly(const ITEM token) { insert_ASCENDING(token); }
	ITEM remove(ITEM removed) { return delete_FROMHEAD(removed); }
	ListEntry<ITEM>* getFirst() { return getHead(); }
	ITEM getHeadSymbol() { return getStart(); }
	int stlist_getCount() {  return getCounter();  }
	bool stlist_isEmpty() const { return isEmpty(); }
};

#endif
