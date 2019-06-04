/********************************************************************************
********************************* UserInput *************************************
*********************************************************************************
* WIP
* The purpose of this class is to handle and validate user input.
*****************
***** USAGE *****
*****************
* WIP
*********************************************************************************/

#pragma once

#include <iostream>
#include <string>

class UserInput
{
private:
public:
	static int getUserInputInt(const int = INT_MIN, const int = INT_MAX);
	static double getUserInputDouble(const double = DBL_MIN, const double = DBL_MAX);
	static std::string getUserInputString();
};