/********************************************************************************
*********************************** Input ***************************************
*********************************************************************************
** Author: Olivier Chan - 75%
* Author: Luis Guerrero - 25%
*
* The purpose of this class is to handle and validate user input.
*****************
***** USAGE *****
*****************
* WIP
*********************************************************************************/

#pragma once

#include <string>

namespace Input
{
	int getInt(int = INT_MIN, int = INT_MAX);
	double getDouble(double = DBL_MIN, double = DBL_MAX);
	std::string getString();
};