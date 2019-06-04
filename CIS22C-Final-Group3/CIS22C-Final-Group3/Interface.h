/********************************************************************************
********************************* Interface *************************************
*********************************************************************************
* WIP
* The purpose of this class is to display user interface.
*****************
***** USAGE *****
*****************
* WIP
*********************************************************************************/

#pragma once

#include <iostream>
#include <iomanip>
#include <string>

class Interface
{
protected:
	static const int TERMINAL_WIDTH = 120;
	static const int TERMINAL_HEIGHT = 60;
	static std::string BARS_CHARACTER;
	static std::string generateBars(int);
public:
	static void clearScreen(bool);
	static void pause();
	static void initialize();
	static void printHeader();
};