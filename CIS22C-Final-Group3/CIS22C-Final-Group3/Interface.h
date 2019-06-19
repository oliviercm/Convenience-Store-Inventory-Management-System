/********************************************************************************
********************************* Interface *************************************
*********************************************************************************
* Author: Olivier Chan - 50%
* Author: Luis Guerrero - 50%
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
#include "AVLTree.h"
#include "HashTable.h"
#include "SortList.h"
#include "Array.h"


namespace Interface
{
	void clearScreen(const bool = true);
	void pause();
	void initialize();
	void printHeader();
	void promptOption();
	void displayMainMenu();
	void displayInventory(Array<Item>&);
	Item addNewItem(Array<Item>&);
	void displayDeleteMenu();
	Item deleteByUid(Array<Item>&);
	Item deleteByName(Array<Item>&);
	Item deleteByUpc(Array<Item>&);
	void displaySearchMenu();
	Item searchByName(Array<Item>&);
	Item searchByUpc(Array<Item>&);
	void displayHashTable(HashTable<int, Item>&);
	void displayKeySequence(Array<Item>&);
	void displayTypeTrees();
	void calculateProfit(AVLTree<double>&, AVLTree<double>&);
};