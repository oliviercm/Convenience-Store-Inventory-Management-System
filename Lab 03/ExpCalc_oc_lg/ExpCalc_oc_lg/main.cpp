/*
CIS 22C
Lab 03: Create a class that can convert infix expressions into postfix and prefix expressions.
Authors:
Olivier Chan Sion Moy
Luis Guerrero
*/

#include <iostream>

#include "Calculator.h"

using namespace std;

int main()
{
	Calculator calc;
	bool again;

	do
	{
		//Get user inputted expression
		//4 + ( 9 / 4 - 2 % 3 ) + ( 5 - 2 ) * 3
		string expression;
		cout << "Enter an expression." << endl
			<< "Operators and operands must be separated by spaces." << endl
			<< "Allowed operators: +, -, *, /, %, (, ). Negation is not allowed." << endl;
		getline(cin, expression);
		cout << endl;

		try
		{

			//Convert expression to postfix, then print out postfix expression and calculate
			string* postfix = calc.infixToPostfix(expression);

			cout << "Postfix Expression:" << endl;
			cout << calc.arrayToString(postfix) << endl;
			cout << "Postfix Result:" << endl;
			cout << calc.resolvePostfix(postfix) << endl << endl;

			//Convert expression to prefix, then print out prefix expression and calculate
			string* prefix = calc.infixToPrefix(expression);

			cout << "Prefix Expression:" << endl;
			cout << calc.arrayToString(prefix) << endl;
			cout << "Prefix Result:" << endl;
			cout << calc.resolvePrefix(prefix) << endl << endl;

			delete[] postfix;
			delete[] prefix;
		}
		catch (ExceptionMalformedExpression e)
		{
			cout << e.what() << endl;
		}

		//Ask user if they want to restart
		cout << "Restart? [0] = No, [1] = Yes" << endl;
		cin >> again;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl;
	} while (again);

	//Exit
	cout << endl;
	system("pause");
	return 0;
}