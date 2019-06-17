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
	void displaSearchMenu();
	Item searchByName(List<Item>&, AVLTree<std::string>&);
	void displayTypeTrees();
};