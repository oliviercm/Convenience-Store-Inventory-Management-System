/********************************************************************************
******************************** Efficiency *************************************
*********************************************************************************
* Author: Olivier Chan - 100%
*
* The purpose of this class is to store global efficiency counters.
*****************
***** USAGE *****
*****************
* Access and increment Efficiency's static members when required.
*********************************************************************************/

#pragma once

class Efficiency
{
public:
	static int globalArrayOperations;
	static int globalListOperations;
	static int globalHashOperations;
	static int globalBinaryTreeOperations;
};