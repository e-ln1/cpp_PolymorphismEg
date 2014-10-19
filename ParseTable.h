/*******
Lance Regala
April 7, 2013
CISP430 - Dixon
*******/

#ifndef LREGALA_PARSETABLE_H
#define LREGALA_PARSETABLE_H
#include"Parser.h"

#define INPUTSYM 8
#define STACKSTATE 6

    enum {IN_ID, IN_EQ, IN_AS, IN_MD, IN_LEFTPAREN, IN_RIGHTPAREN, IN_END, IN_FUNC}; 
    enum {S_NULL, S_EQ, S_AS, S_MD, S_LEFTPAREN, S_FUNC}; 
	enum {Q1, S2, ERR, U1, UC, U2};

class ParseTable
{
private:
	int _grid[INPUTSYM][STACKSTATE]; // 35 total parse action cells in _grid
public:
	// most basic ctor/dtor ever
	ParseTable();
	~ParseTable() {}
	// getter
	const int getParseAction(int inputsym, Token* stackstate)  // Parser uses getParseAction
	{
		//cout << "STACKSTATE: " << stackstate << endl;
		int s=S_NULL;
		if (stackstate->getToken() == "=")
			s=S_EQ;
		else if ((stackstate->getToken() == "+") || (stackstate->getToken() == "-"))
			s=S_AS;
		else if ((stackstate->getToken() == "*") || (stackstate->getToken() == "/"))
			s=S_MD;
		else if (stackstate->getToken() == "(")
			s=S_LEFTPAREN;
		else // otherwise the operation must be a function
			s=S_FUNC;
		return _grid[inputsym][s];
	}
	// ParseTable's _grid is defined and doesn't need a setter
	// No additional facilitators or overloads
};

ParseTable::ParseTable()
{
	_grid[IN_ID][S_NULL] = Q1;
	_grid[IN_ID][S_EQ] = Q1;
	_grid[IN_ID][S_AS] = Q1;
	_grid[IN_ID][S_MD] = Q1;
	_grid[IN_ID][S_LEFTPAREN] = Q1;
	_grid[IN_ID][S_FUNC] = Q1;
	_grid[IN_EQ][S_NULL] = S2;
	_grid[IN_EQ][S_EQ] = ERR;
	_grid[IN_EQ][S_AS] = ERR;
	_grid[IN_EQ][S_MD] = ERR;
	_grid[IN_EQ][S_LEFTPAREN] = ERR;
	_grid[IN_EQ][S_FUNC] = ERR;
	_grid[IN_AS][S_NULL] = ERR;
	_grid[IN_AS][S_EQ] = S2;
	_grid[IN_AS][S_AS] = U1;
	_grid[IN_AS][S_MD] = U1;
	_grid[IN_AS][S_LEFTPAREN] = S2;
	_grid[IN_AS][S_FUNC] = U1;
	_grid[IN_MD][S_NULL] = ERR;
	_grid[IN_MD][S_EQ] = S2;
	_grid[IN_MD][S_AS] = S2;
	_grid[IN_MD][S_MD] = U1;
	_grid[IN_MD][S_LEFTPAREN] = S2;
	_grid[IN_MD][S_FUNC] = U1;
	_grid[IN_LEFTPAREN][S_NULL] = ERR;
	_grid[IN_LEFTPAREN][S_EQ] = S2;
	_grid[IN_LEFTPAREN][S_AS] = S2;
	_grid[IN_LEFTPAREN][S_MD] = S2;
	_grid[IN_LEFTPAREN][S_LEFTPAREN] = S2;
	_grid[IN_LEFTPAREN][S_FUNC] = S2;
	_grid[IN_RIGHTPAREN][S_NULL] = ERR;
	_grid[IN_RIGHTPAREN][S_EQ] = ERR;
	_grid[IN_RIGHTPAREN][S_AS] = UC;
	_grid[IN_RIGHTPAREN][S_MD] = UC;
	_grid[IN_RIGHTPAREN][S_LEFTPAREN] = UC;
	_grid[IN_RIGHTPAREN][S_FUNC] = UC;
	_grid[IN_END][S_NULL] = ERR;
	_grid[IN_END][S_EQ] = U2;
	_grid[IN_END][S_AS] = U2;
	_grid[IN_END][S_MD] = U2;
	_grid[IN_END][S_LEFTPAREN] = U2;
	_grid[IN_END][S_FUNC] = U2;
	_grid[IN_FUNC][S_NULL] = ERR;
	_grid[IN_FUNC][S_EQ] = S2;
	_grid[IN_FUNC][S_AS] = S2;
	_grid[IN_FUNC][S_MD] = S2;
	_grid[IN_FUNC][S_LEFTPAREN] = S2;
	_grid[IN_FUNC][S_FUNC] = ERR;
}

#endif