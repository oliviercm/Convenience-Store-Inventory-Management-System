/********************************************************************************
********************************* Interface *************************************
*********************************************************************************
* Author: Olivier Chan - 75%
* Author: Luis Guerrero - 25%
*
* The purpose of this class is to display user interface.
*****************
***** USAGE *****
*****************
* WIP
*********************************************************************************/

#pragma once
#include "Item.h"

namespace Interface
{
	void clearScreen(bool);
	void pause();
	void initialize();
	void printHeader();
	void promptOption();
	void displayMainMenu();
	void displayInventory();
	Item addNewItem();
	void displayDeleteMenu();
	void displayTypeTrees();
};