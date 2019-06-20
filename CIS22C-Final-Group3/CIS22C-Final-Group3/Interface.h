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

//ADTs
#include "Array.h"
#include "List.h"
#include "HashTable.h"
#include "BST.h"

namespace Interface
{
	const std::string BARS_CHARACTER = "=";
	const int TERMINAL_WIDTH = 160;
	const int TERMINAL_HEIGHT = 60;

	std::string generateBars(const int number);

	/**
	* clearScreen
	*
	* @brief Clears the screen and prints the header.
	*
	* @param bool.
	*/
	void clearScreen(const bool = true);
	/**
	* pause
	*
	* @brief Puase the program until the ENTER key is pressed.
	*
	* @param None.
	*/
	void pause();
	/**
	* initialize
	*
	* @brief Sets the dimensions of the screen.
	*
	* @param None.
	*/
	void initialize();
	/**
	* printHeader
	*
	* @brief Prints the name of the convenience store.
	*
	* @param None.
	*/
	void printHeader();
	/**
	* promptOption
	*
	* @brief Displays " choose option".
	*
	* @param None.
	*/
	void promptOption();
	/**
	* displayMainMenu
	*
	* @brief Displays the main options from the main menu.
	*
	* @param None.
	*/
	void displayMainMenu();
	/**
	* displatInventory
	*
	* @brief Displays the items from the Array.
	*
	* @param The reference of array of items.
	*/
	void displayInventory(Array<Item>&);
	/**
	* addNewItem
	*
	* @brief Adds an item created by the item contructor and stores in a List, Hash table, and BST
	*
	* @param The reference of the list of items.
	*/
	Item addNewItem(Array<Item>&, List<Item>&);
	/**
	* displayDeleteMenu
	*
	* @brief Displays the options on how an item could be deleted.
	*
	* @param None.
	*/
	void displayDeleteMenu();
	/**
	* deleteByUid
	*
	* @brief Deletes the item found in the list, hash table, and BST by UID.
	*
	* @param The reference of the List , hash table, and BST of items.
	*/
	void deleteByUid(List<Item>&, HashTable<int, Item>&, BST<int, Item>&, BST<double, Item>&);
	/**
	* deleteByName
	*
	* @brief Deletes the item found in list, hash table and BST by name.
	*
	* @param The reference of the List , hash table, and BST of items.
	*/
	void deleteByName(List<Item>&, HashTable<int, Item>&, BST<int, Item>&, BST<double, Item>&);
	/**
	* deleteByUpc
	*
	* @brief Deletes the item found in list, hash table and BST by UPC.
	*
	* @param The reference of the List , hash table, and BST of items.
	*/
	void deleteByUpc(List<Item>&, HashTable<int, Item>&, BST<int, Item>&, BST<double, Item>&);
	/**
	* searchForItem
	*
	* @brief Searchs for an item in hash table and if found it displays the item.
	*
	* @param The reference of the hash table of int items.
	*/
	void searchForItem(HashTable<int, Item>&);
	Item searchByName(Array<Item>&);
	Item searchByUpc(Array<Item>&);
	/**
	* displayHashTable
	*
	* @brief Displays the order of the hash table slot by slot with collisions.
	*
	* @param The reference of the hash table of int items.
	*/
	void displayHashTable(HashTable<int, Item>&);
	/**
	* displaysKeySequence
	*
	* @brief Displays the items from the array by sorted UID of the items.
	*
	* @param The reference of the array of items.
	*/
	void displayKeySequence(Array<Item>&);
	void displayMarginProfit(Array<Item>& itemArray, BST<double, Item>&);
	void displayTypeTrees();
	/**
	* displayGoodbye
	*
	* @brief Displays goodbye message.
	*
	* @param None.
	*/
	void displayGoodbye();
};