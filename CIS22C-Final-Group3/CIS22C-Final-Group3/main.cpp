/*
CIS 22C
Final Project:
Group 3:
Olivier Chan Sion Moy
Luis Guerrero
Hiren Rathod
Yue Pan
*/

#include <iostream>
#include <string>

#include "FileIO.h"
#include "Interface.h"
#include "Item.h"
#include "Input.h"
#include "List.h"
#include "HashTable.h"
#include "AVLTree.h"
#include "SortList.h"

using namespace std;

int main()
{
	//Prompt user for filepath to data file
	Interface::initialize();
	Interface::printHeader();
	
	std::string filepath;
	cout << "Enter path to data file: ";
	filepath = Input::getString();

	//Try loading the file into a list
	List<Item> itemList;
	try
	{
		FileIO::loadFileIntoList(itemList, filepath);
	}
	catch(std::invalid_argument e)
	{
		cerr << e.what() << endl;
		cout << "Quitting..." << endl;
		Interface::pause();
		return 0;
	}
	catch (...)
	{
		cerr << "ERROR: Data file corrupted." << endl;
		cout << "Quitting..." << endl;
		Interface::pause();
		return 0;
	}

	//Load the hash table from the list
	HashTable<int, Item> itemHashTable;

	for (int i = 0; i < itemList.getCount(); i++)
	{
		itemHashTable.add(itemList[i].uid, itemList[i]);
	}

	//Load the AVL tree from the list
	AVLTree<double> avlRetailTree;
	AVLTree<double> avlWholesaleTree;

	for (int i = 0; i < itemList.getCount(); i++)
	{
		avlRetailTree.add_avl(itemList[i].retail);
		avlWholesaleTree.add_avl(itemList[i].wholesale);
	}

	//Signal that load was successful
	cout << "Load successful." << endl;
	Interface::displayInventory(itemList);
	Interface::pause();
	Interface::clearScreen();

	//Display the main menu
	int inputMainMenu;
	do
	{
		Interface::displayMainMenu();
		Interface::promptOption();
		inputMainMenu = Input::getInt(1, 9);

		int inputSubMenu, inputAgain, positionOfItem = 0;

		switch (inputMainMenu)
		{
		case 1: //Add new data
		{
			do
			{
				Item newItem;
				Interface::addNewItem(itemList);
				Interface::displayInventory(itemList);
				cout << endl;

				cout << "Would you like to add another item? [1] Yes [2] No" << endl;
				inputAgain = Input::getInt(1, 2);
				Interface::clearScreen(true);
			} while (inputAgain == 1);

			break;
		}
		case 2: //Delete data
		{
			do
			{
				Interface::clearScreen(true);
				Interface::displayDeleteMenu();
				Interface::promptOption();
				inputSubMenu = Input::getInt(1, 4);

				switch (inputSubMenu)
				{
				case 1://deleteByUid
				{
					Interface::deleteByUid(itemList);
					Interface::displayInventory(itemList);
					Interface::pause();
				}
				Interface::clearScreen(true);
				break;
				case 2://deleteByName
				{
					Interface::deleteByName(itemList);
					Interface::displayInventory(itemList);
					Interface::pause();
				}
				Interface::clearScreen(true);
				break;
				case 3://deleteByUpc
				{
					Interface::deleteByUpc(itemList);
					Interface::displayInventory(itemList);
					Interface::pause();
				}
				Interface::clearScreen(true);
				break;
				default:
					break;
				}
			} while (inputSubMenu != 4);
		}
		Interface::clearScreen(true);
			break;
		case 3: //Search
		{
			do
			{
				Interface::clearScreen(true);
				Interface::displaySearchMenu();
				Interface::promptOption();
				inputSubMenu = Input::getInt(1, 3);

				switch (inputSubMenu)
				{
				case 1://searchByName
				{
					do
					{
						int beginningListOperations = Efficiency::globalListOperations;
						Item foundItem = Interface::searchByName(itemList);
						//Item wasn't found
						if (foundItem == Item())
						{
							cout << "Item not found." << endl;
						}
						//Item was found
						else
						{
							cout << foundItem << endl;
						}
						cout << "The last operation took " << Efficiency::globalListOperations - beginningListOperations << " List operations." << endl;
						cout << "Would you like to search for another item name? [1]YES [2]NO" << endl;
						inputAgain = Input::getInt(1, 2);
						Interface::clearScreen();
						Interface::displaySearchMenu();
					} while (inputAgain == 1);
				}
				Interface::clearScreen(true);
				break;
				case 2://searchByUpc
				{
					do
					{
						Item foundItem = Interface::searchByUpc(itemList);
						//Item wasn't found
						if (foundItem == Item())
						{
							cout << "Item not found." << endl;
						}
						//Item was found
						else
						{
							cout << foundItem << endl;
						}
						cout << "Would you like to search for another item name? [1]YES [2]NO" << endl;
						inputAgain = Input::getInt(1, 2);
						Interface::clearScreen();
						Interface::displaySearchMenu();
					} while (inputAgain == 1);
				}
				Interface::clearScreen(true);
				break;
				default:
					break;
				}
			} while (inputSubMenu != 3);
		}
		Interface::clearScreen(true);
			break;
		case 4: //List data in Hash Table Sequence
		{
			Interface::displayHashTable(itemHashTable);

			//cout << itemHashTable;

			Interface::pause();
		}
		Interface::clearScreen(true);
			break;
		case 5: //List data in Key Sequence
		{
			int beginningListOperations = Efficiency::globalListOperations;
			//Merge sort itemList
			SortList::mergeSortItemList(itemList);
			for (int i = 0; i < itemList.getCount(); i++)
			{
				//Print out each item
				cout << itemList[i] << endl;
			}
			cout << "The last operation took " << Efficiency::globalListOperations - beginningListOperations << " List operations." << endl;
			Interface::pause();
		}
		Interface::clearScreen(true);
			break;
		case 6: //Print Tree
			do
			{
				Interface::clearScreen(true);
				Interface::displayTypeTrees();
				Interface::promptOption();
				inputSubMenu = Input::getInt(1, 3);

				switch (inputSubMenu)
				{
				case 1:
				{
					
				}
					break;
				case 2: 
				{
					avlRetailTree.print_tree_avl();
				}
					break;
				default:
					break;
				}
			} while (inputSubMenu != 3);
			Interface::clearScreen(true);
			break;
		case 7: //Efficiency
		{

		}
			break;
		case 8: //Margins and profitability
		{

		}
			break;
		default:
			break;
		}
	} while (inputMainMenu != 9); //Quit

	Interface::pause();
	return 0;
}