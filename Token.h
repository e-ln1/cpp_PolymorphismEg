/******
Lance Regala
April 7, 2013
CISP430 - Dixon
*******/

#ifndef LREGALA_TOKEN_H
#define LREGALA_TOKEN_H
#include<string>
#include<cstdlib>
using namespace std;

class Token
{
protected:
	string _token;
public:
	// ctors, dtor
	Token() { _token = ""; }									// default
	Token(const string& token) { this->_token = token; }		// ctor from str
	Token(const Token& token) { this->_token = token._token; }  // copy ctor
	~Token() { }
	// polymorphic boolean test returns true if the object is what it is
	virtual bool isOperator() { return false; }
	virtual bool isFunction() { return false; }
	virtual bool isOperand() { return false; }
	// getters
	const string getToken() const;
	// setters
	void setToken(const string newtoken);
	// Token functions
	Token tokenize(const string& newtoken)
	{
		return Token(newtoken);
	}
	string clearToken()
	{
		_token.clear();                            // reset token string
		return _token;
	}
	// overloaders
	Token operator=(const string rhs)
	{
		_token = rhs;
		return *this;
	}
	friend bool operator==(const Token lhs, const string rhs)
	{
		return (lhs._token.compare(rhs) == 0);
	}
	friend bool operator>(const Token lhs, const Token rhs)
	{
		return (lhs._token > rhs._token);
	}
	friend bool operator<(const Token lhs, const Token rhs)
	{
		return (lhs._token < rhs._token);
	}
	friend bool operator==(const Token lhs, const Token rhs)
	{
		return (lhs._token == rhs._token);
	}
};

const string Token::getToken() const
{
	return _token;
}

void Token::setToken(const string newtoken)
{
	_token = newtoken;
}

#endif