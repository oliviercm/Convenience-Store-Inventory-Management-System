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
#include "List.h"
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
	Item addNewItem(const List<Item>& itemList);
	void displayDeleteMenu();
	void displayTypeTrees();
};