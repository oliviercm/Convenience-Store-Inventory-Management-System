/********************************************************************************
********************************* Interface *************************************
*********************************************************************************
* Author: Olivier Chan - 30%
* Author: Luis Guerrero - 70%
*
* The purpose of this namespace is to display user interface.
*****************
***** USAGE *****
*****************
* This is a general utility namespace used for displaying various prompts, menus,
* options, and other user interfaces.
* 
* The primary purpose of this namespace is to keep most interface data in one location,
* to prevent unneccessary clutter in main().
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