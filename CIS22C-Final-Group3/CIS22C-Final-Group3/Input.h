/********************************************************************************
*********************************** Input ***************************************
*********************************************************************************
* Author: Olivier Chan - 75%
* Author: Luis Guerrero - 25%
*
* The purpose of this class is to handle and validate user input.
*****************
***** USAGE *****
*****************
* getInt, getDouble, and getString will not display initial prompts.
* However, any input validation errors will print out an error message.
* 
* Use these functions to assign user-inputted values to variables when needed.
*********************************************************************************/

#pragma once

#include <string>

namespace Input
{
	int getInt(int = INT_MIN, int = INT_MAX);
	double getDouble(double = DBL_MIN, double = DBL_MAX);
	std::string getString();
};