#include "Calculator.h"

/**
* splitString
*
* @brief Creates an array of substrings from a parent string, the substrings being tokens of the parent string separated by spaces.
*
* @param str The parent string to generate substrings from.
*
* @return An array of substrings generated from the parent string.
*/

std::string* Calculator::splitString(std::string str)
{
	int numberOfTokens = getNumberOfTokens(str);

	std::string* stringArray = new std::string[numberOfTokens];

	size_t pos = 0;
	size_t start = 0;
	size_t end = 0;

	//While the end of the string hasn't been reached
	for (int i = 0; i < numberOfTokens; i++)
	{
		//Find the first non-space character from pos
		start = str.find_first_not_of(' ', pos);
		//Then find the end of the first non-space character
		end = str.find_first_of(' ', start);
		//Add the token to the array
		stringArray[i] = str.substr(start, end - start);
		//Move pos forward
		pos = end;
	}

	return stringArray;
}

/**
* infixToPostfix
*
* @brief Converts a string infix expression into an array of string tokens (operands and operators) in postfix order. The array is terminated with the string "\0".
*
* @param infix A string infix expression, with all separate operands and operators separated by spaces. An invalid expression will cause an exception.
*
* @return A dynamic array of tokens in postfix order. The array is terminated with the string "\0". This array must be properly deallocated.
*/

std::string* Calculator::infixToPostfix(std::string infix)
{
	//Ensure the expression is valid before doing anything. An invalid expression will throw an ExceptionMalformedExpression exception.
	validateExpression(infix);
	
	Stack<std::string> operatorStack;
	Queue<std::string> expressionQueue;
	int expressionQueueSize = 0;

	std::string* tokenArray = splitString(infix); //Convert the expression string into an array of tokens
	int tokenArraySize = getNumberOfTokens(infix);

	for (int i = 0; i < tokenArraySize; i++)
	{
		//If token is an operand
		if (isOperand(tokenArray[i]))
		{
			//Enqueue operands immediately
			expressionQueue.enqueue(tokenArray[i]);
			expressionQueueSize++;
		}
		//If token is an operator
		else if (isOperator(tokenArray[i]))
		{
			//While the stack isn't empty and the top of the stack is higher or equal precedence (exception: parentheses), pop and enqueue operators from the stack
			while (!operatorStack.isEmpty() && operatorStack.peek() != "(" && operatorStack.peek() != ")" && getOperatorPrecedence(operatorStack.peek()) >= getOperatorPrecedence(tokenArray[i]))
			{
				expressionQueue.enqueue(operatorStack.pop());
				expressionQueueSize++;
			}

			//If operator is ")", pop and enqueue operators until "("
			if (!operatorStack.isEmpty() && tokenArray[i] == ")")
			{
				while (!operatorStack.isEmpty())
				{
					if (operatorStack.peek() == "(")
					{
						operatorStack.pop();
						break;
					}
					else
					{
						expressionQueue.enqueue(operatorStack.pop());
						expressionQueueSize++;
					}
				}
			}
			else
			{
				operatorStack.push(tokenArray[i]);
			}
		}
	}

	//Pop remaining operators
	while (!operatorStack.isEmpty())
	{
		expressionQueue.enqueue(operatorStack.pop());
		expressionQueueSize++;
	}

	//Create the expression array with one extra space so a terminator can be added
	std::string* expressionArray = new std::string[expressionQueueSize + 1];

	//Populate the expression array with the queue
	for (int i = 0; i < expressionQueueSize; i++)
	{
		expressionArray[i] = expressionQueue.dequeue();
	}

	//Delete the token array since the queue and stack are no longer needed
	delete [] tokenArray;

	//Set the last element of the array as a terminator
	expressionArray[expressionQueueSize] = "\0";

	return expressionArray;
}

/**
* infixToPrefix
*
* @brief Converts an infix expression string to a prefix expression array. Terminator placed at the end of array.
*
* @param The expression string.
*
* @return A dynamic Array of strings with null terminator at the end.
*/

std::string* Calculator::infixToPrefix(std::string expression)
{
	//Ensures the expression is right before proceding
	validateExpression(expression);

	Stack<std::string> operatorStack;
	Queue<std::string> operandQueue;

	std::string* reversedArray = reverseString(expression);
	int arraySize = getNumberOfTokens(expression);
	int queueSize = 0;

	for (int i = 0; i < arraySize; i++)
	{
		//If token is an operand
		if (isOperand(reversedArray[i]))
		{
			//Enqueue operands immediately
			operandQueue.enqueue(reversedArray[i]);
			queueSize++;
		}
		//If token is an operator
		else if (isOperator(reversedArray[i]))
		{
			//While the stack isn't empty and the top of the stack is higher or equal precedence (exception: parentheses), pop and enqueue operators from the stack
			while (!operatorStack.isEmpty() && operatorStack.peek() != "(" && operatorStack.peek() != ")" && getOperatorPrecedence(operatorStack.peek()) > getOperatorPrecedence(reversedArray[i]))
			{
				operandQueue.enqueue(operatorStack.pop());
				queueSize++;
			}

			//If operator is ")", pop and enqueue operators until "("
			if (!operatorStack.isEmpty() && reversedArray[i] == ")")
			{
				while (!operatorStack.isEmpty())
				{
					if (operatorStack.peek() == "(")
					{
						operatorStack.pop();
						break;
					}
					else
					{
						operandQueue.enqueue(operatorStack.pop());
						queueSize++;
					}
				}
			}
			else
			{
				operatorStack.push(reversedArray[i]);
			}
		}
	}

	//Pop remaining operators
	while (!operatorStack.isEmpty())
	{
		operandQueue.enqueue(operatorStack.pop());
		queueSize++;
	}

	//Create the expression array with one extra space so a terminator can be added
	std::string* expressionArray = new std::string[queueSize + 1];

	//Populate the expression array with the queue
	for (int i = 0; i < queueSize; i++)
	{
		expressionArray[i] = operandQueue.dequeue();
	}

	//Delete the token array since the queue and stack are no longer needed
	delete[] reversedArray;

	//Set the last element of the array as a terminator
	expressionArray[queueSize] = "\0";

	reverseArray(expressionArray);

	return expressionArray;
}

/**
* resolvePostfix
*
* @brief Calculates the result of a postfix expression, given the postfix expression as an array of tokens.
*
* @param postfixArray The postfix expression as an array. This array should be created by infixToPostfix().
*
* @return The resulting evaluation of the postfix expression.
*/
int Calculator::resolvePostfix(std::string* postfixArray)
{
	Stack<std::string> operandStack;

	int postfixArraySize = 0;

	//Find the size of the array
	{
		int i = 0;
		while (postfixArray[i] != "\0")
		{
			postfixArraySize++;
			i++;
		}
		postfixArraySize++;
	}

	//Make a temporary copy of the array to allow overwriting values
	std::string* tempArray = new std::string[postfixArraySize];
	for (int i = 0; i < postfixArraySize; i++)
	{
		tempArray[i] = postfixArray[i];
	}

	//Calculate the result of the expression
	int result;
	{
		int i = 0;
		while (tempArray[i] != "\0")
		{
			//If token is an operand
			if (isOperand(tempArray[i]))
			{
				operandStack.push(tempArray[i]);
			}
			//If token is an operator
			else if (isOperator(tempArray[i]))
			{
				int right = std::stoi(operandStack.pop());
				int left = std::stoi(operandStack.pop());

				//Note: The operator is being replaced here so that we can keep the result in the stack after leaving scope
				if (tempArray[i] == "+")
				{
					tempArray[i] = std::to_string(left + right);
				}
				else if (tempArray[i] == "-")
				{
					tempArray[i] = std::to_string(left - right);
				}
				else if (tempArray[i] == "*")
				{
					tempArray[i] = std::to_string(left * right);
				}
				else if (tempArray[i] == "/")
				{
					tempArray[i] = std::to_string(left / right);
				}
				else if (tempArray[i] == "%")
				{
					tempArray[i] = std::to_string(left % right);
				}

				operandStack.push(tempArray[i]);
			}
			else
			{
				throw ExceptionMalformedExpression();
			}

			i++;
		}
		//The remaining operand is the result
		result = std::stoi(operandStack.pop());
	}

	delete [] tempArray;

	return result;
}

/**
* resolvePrefix
*
* @brief Calculates the result of a prefix expression, given the prefix expression as an array of tokens.
*
* @param prefixArray expression as an array. Array created by infixToPrefix.
*
* @return The resulting evaluation of the prefix expression.
*/
int Calculator::resolvePrefix(std::string* prefixArray)
{
	Stack<std::string> evaluationStack;
	int prefixArraySize = 0;
	{
		//Find the size of the array
		int i = 0;
		while (prefixArray[i] != "\0")
		{
			prefixArraySize++;
			i++;
		}
		prefixArraySize++;
	}

	//Create a copy of the array
	std::string* tempArray = new std::string[prefixArraySize];
	for (int i = 0; i < prefixArraySize; i++)
	{
		tempArray[i] = prefixArray[i];
	}

	int result;
	{
		int i = 0;
		while (tempArray[i] != "\0")
		{
			if (isOperator(tempArray[i]))
			{
				evaluationStack.push(tempArray[i]);
			}
			else if (isOperand(tempArray[i]))
			{
				//If an operand is being pushed on top of another operand
				if (!evaluationStack.isEmpty() && isOperand(evaluationStack.peek()))
				{
					std::string temp = tempArray[i];
					
					//Pop an operand and an operator, then calculate using them and the operand to be pushed, and repeat as long as an operand is being pushed on an operand
					while (!evaluationStack.isEmpty() && isOperand(evaluationStack.peek()) && isOperand(temp))
					{
						int left = std::stoi(evaluationStack.pop());
						std::string op = evaluationStack.pop();
						int right = std::stoi(temp);

						if (op == "+")
						{
							temp = std::to_string(left + right);
						}
						else if (op == "-")
						{
							temp = std::to_string(left - right);
						}
						else if (op == "*")
						{
							temp = std::to_string(left * right);
						}
						else if (op == "/")
						{
							temp = std::to_string(left / right);
						}
						else if (op == "%")
						{
							temp = std::to_string(left % right);
						}
					}

					tempArray[i] = temp;
					evaluationStack.push(tempArray[i]);
				}
				else
				{
					evaluationStack.push(tempArray[i]);
				}
			}
			else
			{
				throw ExceptionMalformedExpression();
			}

			i++;
		}
		result = std::stoi(evaluationStack.pop());
		delete[] tempArray;
		return result;
	}
}

/**
* getNumberOfTokens
*
* @brief Returns the number of tokens in a given string, delimited by any number of spaces.
*
* @param str The string to count substrings from.
*
* @return The number of tokens in the string.
*/
int Calculator::getNumberOfTokens(std::string str)
{
	int numberOfTokens = 0;
	size_t pos = 0;

	//While the end of the string hasn't been reached
	while (pos != std::string::npos)
	{
		//Find the first non-space character
		pos = str.find_first_not_of(' ', pos);
		//Then move to the end of that non-space character
		pos = str.find_first_of(' ', pos);
		//Add a token
		numberOfTokens++;
	}

	return numberOfTokens;
}

/**
* reverseArray
*
* @brief Reverse an array using ptrs.
*
* @param ptr of an Array.
*
* @return The reverse ptr string.
*/
std::string * Calculator::reverseArray(std::string *pArray)
{
	int pArraySize = 0;
	{
		int j = 0;
		while (pArray[j] != "\0")
		{
			pArraySize++;
			j++;
		}
	}
	std::string* pStart = pArray;
	std::string* pEnd = pStart + pArraySize - 1;
	
	while (pEnd > pStart)
	{
		std::string temp = *pStart;
		*pStart = *pEnd;
		*pEnd = temp;
		pStart++;
		pEnd--;
	}
	return pArray;
}

/**
* isOperator
*
* @brief Checks whether a given string is a valid operator, allowed characters: +, -, *, /, %, (, )
*
* @param str The string to check.
*
* @return Whether the string is a valid operator or not.
*/
bool Calculator::isOperator(std::string str)
{
	if (str == "+" ||
		str == "-" ||
		str == "*" || 
		str == "/" ||
		str == "%" ||
		str == "(" ||
		str == ")")
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
* isOperand
*
* @brief Checks whether a given string is a valid operand, allowed characters: 1, 2, 3, 4, 5, 6, 7, 8, 9, 0
*
* @param str The string to check.
*
* @return Whether the string is a valid operand or not.
*/

bool Calculator::isOperand(std::string str)
{
	if (str.size() == 0)
	{
		return false;
	}
	
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] != '1' &&
			str[i] != '2' &&
			str[i] != '3' &&
			str[i] != '4' &&
			str[i] != '5' &&
			str[i] != '6' &&
			str[i] != '7' &&
			str[i] != '8' &&
			str[i] != '9' &&
			str[i] != '0')
		{
			return false;
		}
	}

	return true;
}

/**
* getOperatorPrecedence
*
* @brief 
*/
int Calculator::getOperatorPrecedence(std::string str)
{
	if (str == "+" || str == "-")
	{
		return 1;
	}
	else if (str == "*" || str == "/" || str == "%")
	{
		return 2;
	}
	else if (str == "(" || str == ")")
	{
		return 3;
	}
	else
	{
		return 0;
	}
}

/**
* arrayToString
*
* @brief Convert an expression array into a string representation.
*
* @param array The expression array to convert. This array should be created by infixToPostfix() or infixToPrefix().
*
* @return The string representation of the expression array.
*/

std::string Calculator::arrayToString(std::string* expressionArray)
{
	std::string expressionString = std::string();

	int i = 0;
	while (expressionArray[i] != "\0")
	{
		expressionString.append(expressionArray[i]);
		if (expressionArray[i + 1] != "\0")
		{
			expressionString.append(" ");
		}
		i++;
	}

	return expressionString;
}

/**
* reverseString
*
* @brief Reverse the string that was built from spliString function
*
* @param the array string and the size
*
* @return Reverse pointer string.
*/

std::string* Calculator::reverseString(std::string expressionString)
{
	std::string *stringReverse = splitString(expressionString);
	int size = getNumberOfTokens(expressionString);
	std::string temp;
	for (int i = 0; i < size / 2; i++)
	{
		temp = stringReverse[size - 1 - i];
		stringReverse[size - 1 - i] = stringReverse[i];
		stringReverse[i] = temp;
	}
	//Reverse the Parenthesis in order to get the prefix right
	for (int j = 0; j < size; j++)
	{
		if (stringReverse[j] == "(")
		{
			stringReverse[j] = ")";
		}
		else if (stringReverse[j] == ")")
		{
			stringReverse[j] = "(";
		}
	}
	return stringReverse;
}

/**
* validateExpression
*
* @brief Verifies that an expression is well formed. An invalid expression will throw an ExceptionMalformedExpression exception.
*
* @param expression The expression to verify.
*/

void Calculator::validateExpression(std::string expression)
{
	std::string* expressionArray = splitString(expression);
	int expressionArraySize = getNumberOfTokens(expression);

	Stack<std::string> expressionStack;
	int openParentheses = 0;
	int closeParentheses = 0;

	//Ensure that all operators are followed by operands, and all operands are followed by operators.
	for (int i = 0; i < expressionArraySize; i++)
	{
		//If token is an operand
		if (isOperand(expressionArray[i]))
		{
			//Operands cannot follow other operands
			if (!expressionStack.isEmpty() && isOperand(expressionStack.peek()))
			{
				throw ExceptionMalformedExpression();
			}

			expressionStack.push(expressionArray[i]);
		}
		//If token is an operator
		else if (isOperator(expressionArray[i]))
		{
			//Operators cannot be first in the expression, with the exception of "("
			if (expressionStack.isEmpty() && expressionArray[i] != "(")
			{
				throw ExceptionMalformedExpression();
			}
			
			//Operators cannot follow other operators, unless one of the operators in question is "(" or ")"
			if (!expressionStack.isEmpty() && isOperator(expressionStack.peek()) &&
				expressionArray[i] != "(" && expressionArray[i] != ")" &&
				expressionStack.peek() != "(" && expressionStack.peek() != ")")
			{
				throw ExceptionMalformedExpression();
			}

			//Keep count of each type of parenthesis, and there cannot be a close parentheses without a preceding non-paired open parentheses.
			if (expressionArray[i] == "(")
			{
				openParentheses++;
			}
			else if (expressionArray[i] == ")")
			{
				closeParentheses++;
				if (closeParentheses > openParentheses)
				{
					throw ExceptionMalformedExpression();
				}
			}

			//With the exception of ")", operators cannot be the last token
			if (i == expressionArraySize - 1 && expressionArray[i] != ")")
			{
				throw ExceptionMalformedExpression();
			}

			expressionStack.push(expressionArray[i]);
		}
		//Token is neither an operand nor an operator
		else
		{
			throw ExceptionMalformedExpression();
		}
	}

	//Ensure that every parenthesis has a paired partner
	if (openParentheses != closeParentheses)
	{
		throw ExceptionMalformedExpression();
	}

	delete [] expressionArray;
}