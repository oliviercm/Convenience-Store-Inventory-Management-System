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
#include "BinarySearchTree.h"
#include "BinaryTreeNode.h"

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
	AVLTree<int> avlUidTree;

	for (int i = 0; i < itemList.getCount(); i++)
	{
		avlRetailTree.add_avl(itemList[i].retail);
		avlWholesaleTree.add_avl(itemList[i].wholesale);
		avlUidTree.add_avl(itemList[i].uid);
	}

	//Signal that load was successful
	cout << "Load successful." << endl;
	//Interface::displayInventory(itemList);
	Interface::pause();
	Interface::clearScreen();

	//Display the main menu
	int inputMainMenu;
	do
	{
		Interface::displayMainMenu();
		Interface::promptOption();
		inputMainMenu = Input::getInt(1, 9);

		//variables to get user input
		int inputSubMenu, inputAgain;

		switch (inputMainMenu)
		{
		case 1: //Add new data
		{
			do
			{
				Item newItem;
				Interface::addNewItem(itemList);
				FileIO::saveListIntoFile(itemList, filepath);
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
					FileIO::saveListIntoFile(itemList, filepath);
					cout << endl;
					Interface::displayInventory(itemList);
					Interface::pause();
				}
				Interface::clearScreen(true);
				break;
				case 2://deleteByName
				{
					Interface::deleteByName(itemList);
					FileIO::saveListIntoFile(itemList, filepath);
					cout << endl;
					Interface::displayInventory(itemList);
					Interface::pause();
				}
				Interface::clearScreen(true);
				break;
				case 3://deleteByUpc
				{
					Interface::deleteByUpc(itemList);
					FileIO::saveListIntoFile(itemList, filepath);
					cout << endl;
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
					cout << "The last operation took " << Efficiency::globalListOperations - beginningListOperations << " List operations." << endl << endl;
					Interface::pause();
				}
				Interface::clearScreen(true);
				break;
				case 2://searchByUpc
				{
	
					int beginningListOperations = Efficiency::globalListOperations;
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
					cout << "The last operation took " << Efficiency::globalListOperations - beginningListOperations << " List operations." << endl << endl;
					Interface::pause();
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
			Interface::clearScreen(true);
			Interface::displayHashTable(itemHashTable);
		}
			break;
		case 5: //List data in Key Sequence
		{
			Interface::clearScreen(true);
			int beginningListOperations = Efficiency::globalListOperations;
			Interface::displayKeySequence(itemList);
			cout << "The last operation took " << Efficiency::globalListOperations - beginningListOperations << " List operations." << endl << endl;
			Interface::pause();
			Interface::clearScreen(true);
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
				case 1://Prints wholesale tree
				{
					avlWholesaleTree.print_tree_avl();
					cout << endl;
					Interface::pause();
				}
					break;
				case 2: //Prints retail tree
				{
					avlRetailTree.print_tree_avl();
					cout << endl;
					Interface::pause();
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