/*******
Lance Regala
April 7, 2013
CISP430 - Dixon
*******/

#ifndef LREGALA_PARSER_H
#define LREGALA_PARSER_H
#include<string>
#include<cmath> 
#include<cctype>
#include"List.h"
#include"Token.h"
#include"Operator.h"
#include"Operand.h"
#include"Function.h"
#include"ParseTable.h"
#include"Stack.h"
#include"Queue.h"
#include"Infix.h"
#include"Postfix.h"
using namespace std;

#define DELIM_SET " \t\v\n\r\f"
#define OPERATOR_SET "=+-*/()"
const string FUNCTION_SET[] = {"sin", "cos", "abs", "sqrt", "SIN", "COS", "ABS", "SQRT"};
#define MAXFUNCS 8

class Parser
{
private:
	Queue<Token*> _Q1;
	Stack<Token*> _S2;
	ParseTable _Ptable;
    string _expression;					// input string
    string _str_token;					// an output token in string form
    string _delimiter;					// configurable using the #define DELIM_SET
    string _operator;					// single character operators, #define OPERATOR_SET
	string::const_iterator currPos;		// STL iterator pointing to the current position
    void skipDelimiter();
    bool isDelimiter(char c);
	bool isOperator(char optr);
	bool isOperator(Token* optr);
	bool isFunction(Token* func);
public:
    Parser();
    Parser(const string& expression, const string& delimiter=DELIM_SET, const string& optor=OPERATOR_SET);
	~Parser() {}
    // setters
    void setParser(const string& expression, const string& delimiter=DELIM_SET, const string& optor=OPERATOR_SET);
    void setExpression(const string& expression);   // receives the incoming expression only
    void setDelimiter(const string& delimiter);     // sets the delimiter only
	// getters
    string getNextToken();						    // get the next token, return "" at End Of Expression
												    // getting other stuff individually here isn't necessary
	// facilitators
    List<Token*> createInfix(string& expression);	// return (Infix) from current cursor
	Postfix convertToPostfix(Infix infixed);	// return (Postfix) format from Infix
	void parseActionSwitch(int action, Token* subclass=NULL);
	int determineAction(Token* token);
};

Parser::Parser() : _expression(""), _str_token(""), _delimiter(DELIM_SET), _operator(OPERATOR_SET)
{
    currPos = _expression.begin();
	_Q1 = Queue<Token*>();
	_S2 = Stack<Token*>();
	_Ptable = ParseTable();
}

Parser::Parser(const string& str, const string& delimiter, const string& optor) 
	: _expression(str), _str_token(""), _delimiter(delimiter), _operator(optor)
{
    currPos = _expression.begin();
	_Q1 = Queue<Token*>();
	_S2 = Stack<Token*>();
	_Ptable = ParseTable();
}

void Parser::skipDelimiter()
{
    while(currPos != _expression.end() && isDelimiter(*currPos))
        ++currPos;
}

bool Parser::isDelimiter(char c)
{
    return (_delimiter.find(c) != string::npos);
}

bool Parser::isOperator(char optr)
{
	return (_operator.find(optr) != string::npos);
}
bool Parser::isOperator(Token* optr)
{
	bool check = true;
	string str_tkn;
	str_tkn = optr->getToken();
	for(unsigned int i=0;i<str_tkn.size();i++)
	{
		if (_operator.find(str_tkn[i]) == string::npos)
			check = false;
	}
	return check;
}

bool Parser::isFunction(Token* func)
{
	bool check = false;
	for (int i=0;i<MAXFUNCS;i++)
	{
		if(FUNCTION_SET[i].compare(func->getToken())==0)		
		{
			check = true;
		}
	}
	return check;
}

void Parser::setParser(const string& expression, const string& delimiter, const string& optor)
{
	this->_expression = expression;
    this->_delimiter = delimiter;
	this->_operator = optor;
    this->currPos = _expression.begin();
}

void Parser::setExpression(const string& expression)
{
    this->_expression = expression;
    this->currPos = _expression.begin();
}

void Parser::setDelimiter(const string& delimiter)
{
    this->_delimiter = delimiter;
    this->currPos = _expression.begin();
}

string Parser::getNextToken()  // 
{
    if(_expression.size() <= 0) 
		return "";					// skip if buffer is empty
    _str_token.clear();             // reset token string
    this->skipDelimiter();          // skip leading delimiters

    // append each char to token string until it meets delimiter
    if (currPos != _expression.end() && isOperator(*currPos))
	{
		_str_token = *currPos;
		++currPos;
	}
	else
	{
		while(currPos != _expression.end() && !isDelimiter(*currPos) && !isOperator(*currPos))
		{
			_str_token += *currPos;
			++currPos;
		}
	}
    return _str_token;
}

List<Token*> Parser::createInfix(string& expression)
{
    List<Token*> tokens;
	string temp;
	if (expression.empty())
		expression = "INVALID = 0";
	this->setParser(expression);
    while((temp = this->getNextToken()) != "")
	{
		Token* tokenptr= new Token;
		tokenptr->setToken(temp);
		tokens.insert_ATEND(tokenptr);
	}
	if (tokens.isEmpty())
	{
		Token* tokenptr= new Token;
		tokenptr->setToken("INVALID");
		tokens.insert_ATEND(tokenptr);
	}
	return tokens;  // infix format
}

Postfix Parser::convertToPostfix(Infix infixed)	// return (Postfix) format from Infix
{ 
	//cout << "(within Postfix scope)";
	int action=ERR;
	ListEntry<Token*>* listCursor = new ListEntry<Token*>;
    Postfix postfixedtokens;
	listCursor =  infixed.getHead();
	/*		
	//		enum {IN_ID, IN_EQ, IN_AS, IN_MD, IN_LEFTPAREN, IN_RIGHTPAREN, IN_END, IN_FUNC}; 
	//		enum {S_NULL, S_EQ, S_AS, S_MD, S_LEFTPAREN, S_FUNC};
	*/
	while(listCursor != NULL)
	{
		if (isOperator(listCursor->getData()))  // (ptrdata) within Node is a Polymorphic Token
		{
			//cout << "I'm NOT an OPERATOR YET: " << *listCursor->getData() << endl;
			//******* determine what kind of parse action and make a derived class object *******//
			Operator* optrclass = new Operator;
				// now take the *listCursor->getData() and make an Operator
			optrclass->setToken(listCursor->getData()->getToken());
			if (_S2.stack_isEmpty())
				_S2.push(optrclass); // simply to prevent the program from crashing
									// this action will result in an error later if the Optor isn't an =
			else
			{
				action = determineAction(optrclass);  // Token*
				//cout << "Optor Action: " << action << endl;
				parseActionSwitch(action, optrclass);		// decide the action, do the action
			}
		}
		else if (isFunction(listCursor->getData()))
		{
			Function* funclass = new Function;
			funclass->setToken(listCursor->getData()->getToken());
			action = _Ptable.getParseAction(IN_FUNC,_S2.showTop());
			parseActionSwitch(action, funclass);
		}
		else // *listCursor->getData() is an Operand...
		{
			Operand* opdclass = new Operand;
			action = Q1; // enum of ParseAction found in ParseTable.h
				// now take the *listCursor->getData() and make an Operand
			opdclass->setToken(listCursor->getData()->getToken());
			parseActionSwitch(action, opdclass);		// do what needs to be done on _Q1 or _S2
		}
		/*************************************/
		listCursor = listCursor->getLinknext();
	}
	if (listCursor == NULL)
	{
		while (!(_S2.stack_isEmpty()))
		{
			// action U2
			parseActionSwitch(U2);
		}
	}
	// At this time the parse actions will have dropped the postfix form into _Q1
	// ...now assign _Q1 to a Postfix class
	//postfixedtokens ! _Q1;

	while (!(_Q1.queue_isEmpty()))
	{
		Token* ptrtkn;
		postfixedtokens += _Q1.dequeue(ptrtkn);
	}
	return postfixedtokens;
}

void Parser::parseActionSwitch(int action, Token* subclass)
{
	//	enum {Q1, S2, ERR, U1, UC, U2};  // found in ParseTable.h
	Token* popped = new Token;
	switch (action)
		{
            case Q1:
				// enqueue Token* subclass onto _Q1
				_Q1.enqueue(subclass);
				//cout << "Q1" << endl;
                break;
            case S2:
				// push Token* subclass onto _S2
				_S2.push(subclass);
				//cout << "S2" << endl;
				break;
            case U1:
				// push one item from _S2 onto Q1 
				// AND do another comparison on the incoming Token* subclass
				int newaction;
				//cout << "U1" << endl;
				_S2.pop(popped);
				_Q1.enqueue(popped);
				newaction = determineAction(subclass);
				parseActionSwitch(newaction,subclass);
				break;
            case UC:
				// unstack _S2 onto _Q1 until "(" is found, discard "("
				while (!(*_S2.showTop() == "("))
				{
					_Q1.enqueue(_S2.pop(popped));
					//cout << "UC" << endl;
				}
				_S2.pop(popped);
				delete popped;
				break;
			case U2:
				// enqueue onto _Q1 everything in _S2 until _S2 is empty
				while (!(_S2.stack_isEmpty()))
				{	
					_Q1.enqueue(_S2.pop(popped));
					//cout << "U2" << endl;
				}
				break;
			default: // ERR // everything else results in a bunch of errors
				{
					//cout << "STACKSTATE: " << _S2.showTop()->getToken() << endl;
					cout << "Syntax Error! Syntax Error!" << endl;
				}
				break;
        }
}

int Parser::determineAction(Token* token)
{
	int action;
			if (token->getToken() == "=")
			{
				if (!(_S2.stack_isEmpty()))
					action = _Ptable.getParseAction(IN_EQ,_S2.showTop());
				else 
					action = S2;
			}
			else if ((token->getToken() == "+") || (*token == "-")) 
			{
				action = _Ptable.getParseAction(IN_AS,_S2.showTop());
			}
			else if ((token->getToken() == "*") || (*token == "/"))
			{
				action = _Ptable.getParseAction(IN_MD,_S2.showTop());
			}
			else if (token->getToken() == "(") 
			{
				//cout << "STACKSTATE: " << _S2.showTop()->getToken() << endl;
				action = _Ptable.getParseAction(IN_LEFTPAREN,_S2.showTop());
			}
			else if (token->getToken() == ")") 
			{
				action = _Ptable.getParseAction(IN_RIGHTPAREN,_S2.showTop());
			}
			else
			{
				if (isFunction(token))
					action = _Ptable.getParseAction(IN_FUNC,_S2.showTop());
				else
					action = ERR;
			}
		return action;
}

#endif