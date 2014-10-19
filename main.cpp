/*******
Lance Regala
April 7, 2013
CISP430 - Dixon
*******/

#include<iostream>
#include<iomanip>
#include<string>
#include<climits>
#include"Parser.h"
#include"Eval.h"
#include"Operand.h"
#include"Operator.h"
#include"Expression.h"
#include"Infix.h"
#include"Postfix.h"
#define WIDTH 23
using namespace std;

void clearScreen();
void displayOptions();
int selectOption();
//
Operand* createOperands(Eval eval);
//
void listSymbolTable(Eval eval);
//
void evaluateExpressions(Eval eval);
//

int main()
{
	//*******User************//
	//*******Interface*******//
	Eval eval;
    do 
	{
        //clearScreen();
        int selection = -1;
		displayOptions();
		selection = selectOption();

        /* SWITCH */

        switch (selection)
        {
            case 1:
				eval.addStlistItem(createOperands(eval));
                break;
            case 2:
                listSymbolTable(eval);
                break;
            case 3:
				evaluateExpressions(eval);
				break;
            default:
                break;
        }
	clearScreen();
    } while (1 == 1);  // loops infinitely.  menu selection 0: exit(1) exits
	return 0;
}

void clearScreen(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void displayOptions()
{
        cout << setfill(' ') << right
        << setw(WIDTH)  <<"Lance's Expression Evaluator Program ~ Options:" << endl
        << setfill(' ') << left
        << setw(WIDTH)  <<" [1] = Create/edit symbols used for expressions." << endl
        << setw(WIDTH)  <<" [2] = List the existing expression symbols." << endl
		<< setw(WIDTH)  <<" [3] = Create and evaluate mathematical expressions." << endl
        << setw(WIDTH)  <<" [0] = <<Exit the application>>"	<< endl
        << endl;
}

int selectOption()
{
	int selection;
    do
    {
		cout << "Select an Option:: " << endl;
		while (!(cin >> selection))   //input validation
		{
			cout << endl << "Please choose a number: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
        if (selection == 0)
        {
			cout<<"Ok, exiting...";
                exit(1);
		}
        else if (selection < 0 || selection > 3)
            cout << "\n*You must choose a valid Menu Option.*" << endl << endl;
    } while (selection < 1 || selection > 3);
	return selection;
}

		/******************************************/

Operand* createOperands(Eval eval)
{
	Operand* N = new Operand;
	string userinput;
	double userval;
	bool valid;
	cout << "There are 4 pre-defined symbols (A, B, C, and D)." << endl
		<< "You can create one additional symbol but cannot re-define the existing ones." << endl;
	do
	{
		valid = true;
		cout << "  (symbols can be any combination of letters [A-Z, a-z])" << endl
			<< ": ";
		cin >> userinput;  // requires validation
		for(unsigned int i=0; (i<userinput.length()) && valid==true; i++)
		{
			if(isalpha(userinput[i]))
				valid = true;
			else
				valid = false;
		}
	} while(valid == false);
	cout << endl;
	//*********************
	N->setToken(userinput);
	while (eval.checkStlist(N))
	{
		cout << endl
		<< "Sorry it looks like " << userinput << " already exists. You cannot edit existing symbols." << endl;
		cout << "Please input another symbol." << endl;
		cin >> userinput;
		N->setToken(userinput);
	}
	cout << "Ok, great. What would you like the value of this operand symbol to be?" << endl
		<< " : ";
	cin >> userval;
	N->setValue(userval);
	cout << " " << userval << " has been added to " << N->getToken() << endl;
	cout << "Press [ENTER] to continue." << endl;
	cin.ignore();
	cin.get();
	return N;
}

void listSymbolTable(Eval eval)  // Option 2 - display Operands
{
	ListEntry<Operand*>* ptrCurrent = eval.getStlist().getFirst();

	cout << "Lance's SYMBOL TABLE: " << endl;
	while(ptrCurrent != NULL)
	{
		cout << ptrCurrent->getData()->getToken() << " = "
			<< ptrCurrent->getData()->getValue() << endl;
		ptrCurrent = ptrCurrent->getLinknext();
	}
	cout << endl << "Press [ENTER] when ready to continue." << endl;
	cin.ignore();
	cin.get();
}

void evaluateExpressions(Eval eval)
{
    Parser parser;
	Infix tknPtrInfix;
	Postfix tknPtrPostfix;
	ListEntry<Token*>* listCursor = new ListEntry<Token*>; // iterator
	string mathematicalexpression;	// userinput
	Operand solution;				// final LHS

	// first list the valid operands, again, for the user's reference:
	ListEntry<Operand*>* ptrSymTable = eval.getStlist().getFirst();
	cout << "Valid OPERANDS" << endl;
	while(ptrSymTable != NULL)
	{
		cout << ptrSymTable->getData()->getToken() << " = "
			<< ptrSymTable->getData()->getValue() << endl;		
		ptrSymTable = ptrSymTable->getLinknext();
	}
	// and list the valid operator set:
	cout << "...and valid OPERATORS" << endl;
	cout << " " << OPERATOR_SET;  // globally scoped, see Parser header
	// The reserved operator tokens are like the delimiters.  Reserved.
	cout << endl;
	cout << endl << "Please enter an equation:" << endl;
	cout << "example:    A = (B-A) + sin(D/C) * abs(C)" << endl;
	cout << " ° " << endl 
		<< "An expression begins with one valid symbol, then an = sign."
		<< endl << "There may only be one equal sign, followed by a mathematical expression:" << endl
		<< "     ";
	cin.ignore();
	getline(cin, mathematicalexpression);
    int counter = 0;
	tknPtrInfix = parser.createInfix(mathematicalexpression);
	 // test print
	/*******
	cout << "Infix: " << endl;
	if (tknPtrInfix.isEmpty())
		cout << "Empty.";
	listCursor =  tknPtrInfix.getHead();
	while(listCursor != NULL)
	{
		cout << listCursor->getData()->getToken();  // deref (ptrdata) within Node to utilize polymorphism at runtime
		listCursor = listCursor->getLinknext();
		cout << endl;
	}
	*******/
	////////////////////////////////////////////////////
	tknPtrPostfix = parser.convertToPostfix(tknPtrInfix);
	listCursor =  tknPtrPostfix.getHead();
	/*
	cout << "POSTFIX!" << endl;
	while(listCursor != NULL)
	{
		cout << listCursor->getData()->getToken();  // deref (ptrdata) within Node to utilize polymorphism at runtime
		listCursor = listCursor->getLinknext();
		cout << endl;
	}
	*/
	solution = eval.assignCalculatedExpressionToLHS(tknPtrPostfix);
	cout << endl << "Your expression evaluates to " << solution.getToken() << " = " << solution.getValue() << endl;

	cout << endl << "(Press [ENTER] to continue.)" << endl;
	cin.get();
}

// END OF LINE
/****************************************************/