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
#include "List.h"

namespace Interface
{
	void clearScreen(bool);
	void pause();
	void initialize();
	void printHeader();
	void promptOption();
	void displayMainMenu();
	void displayInventory(List<Item>&);
	void addNewItem(List<Item>&);
	void displayDeleteMenu();
	void deleteByUid(List<Item>&);
	void deleteByName(List<Item>&);
	void deleteByUpc(List<Item>&);
	void displayTypeTrees();
};