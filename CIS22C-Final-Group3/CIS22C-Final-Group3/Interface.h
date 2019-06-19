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
#include "BinarySearchTree.h"
#include "HashTable.h"
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
	Item addNewItem(List<Item>&);
	void displayDeleteMenu();
	void deleteByUid(List<Item>&, HashTable<int, Item>&, BinarySearchTree<Item>&);
	void deleteByName(List<Item>&, HashTable<int, Item>&, BinarySearchTree<Item>&);
	void deleteByUpc(List<Item>&, HashTable<int, Item>&, BinarySearchTree<Item>&);
	void searchForItem(HashTable<int, Item>&);
	Item searchByName(Array<Item>&);
	Item searchByUpc(Array<Item>&);
	void displayHashTable(HashTable<int, Item>&);
	void displayKeySequence(Array<Item>&);
	void displayTypeTrees();
};