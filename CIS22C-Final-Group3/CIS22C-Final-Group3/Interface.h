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
	void clearScreen(const bool = true);
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
<<<<<<< HEAD
	void displaSearchMenu();
	size_t searchByName(List<Item>&);
=======
	void displaySearchMenu();
	Item searchByName(List<Item>&, AVLTree<std::string>&);
>>>>>>> df477ad2409859a1b1397ce07b623ae618a56321
	void displayTypeTrees();
};