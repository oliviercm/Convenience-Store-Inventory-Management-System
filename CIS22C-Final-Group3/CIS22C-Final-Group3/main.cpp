/*
CIS 22C
Final Project:
Group 3:
Olivier Chan Sion Moy
Luis Guerrero
Hiren Rathod
Yue Pan
*/

/********************************************************************************
********************************** main() ***************************************
*********************************************************************************
* Author: Olivier Chan - 50%
* Author: Luis Guerrero - 50%
*********************************************************************************/

#include <iostream>
#include <string>

//Utility
#include "FileIO.h"
#include "Interface.h"
#include "Input.h"
#include "BSTTraversal.h"

//ADTs
#include "Array.h"
#include "List.h"
#include "HashTable.h"
#include "BST.h"

#include "Item.h"

using namespace std;

int main()
{
	//Prompt user for filepath to data file
	Interface::initialize();
	Interface::printHeader();

	cout << "Enter path to data file: ";
	const std::string filepath = Input::getString();

	//Try loading the file into an array
	Array<Item> itemArray;
	try
	{
		FileIO::loadFileIntoArray(itemArray, filepath);
	}
	catch(std::invalid_argument& e)
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

	//Load ADTs from the array
	List<Item> itemList;
	HashTable<int, Item> itemHashTable;
	BST<int, Item> itemUidBst;
	BST<double, Item> itemMarginBst;
	for (int i = 0; i < itemArray.getSize(); i++)
	{
		Item& item = itemArray[i];
		
		itemList.insertLast(item);
		itemHashTable.add(item.uid, item);
		itemUidBst.insert(item.uid, item);
		itemMarginBst.insert(item.getMargin(), item);
	}

	//Signal that load was successful
	cout << "Load successful." << endl << endl;
	cout << "There were " << Efficiency::globalArrayOperations << " Array operations." << endl;
	cout << "There were " << Efficiency::globalListOperations << " List operations." << endl;
	cout << "There were " << Efficiency::globalHashOperations << " Hash operations." << endl;
	cout << "There were " << Efficiency::globalBinaryTreeOperations << " BST operations." << endl << endl;
	Interface::pause();
	Interface::clearScreen();

	//Display the main menu
	int inputMainMenu;
	do
	{
		Interface::clearScreen();
		Interface::displayMainMenu();
		Interface::promptOption();
		inputMainMenu = Input::getInt(0, 9);

		//variables to get user input
		int inputSubMenu, inputAgain;

		switch (inputMainMenu)
		{
			case 1: //Add new data
			{
				do
				{
					const int beginningArrayOperations = Efficiency::globalArrayOperations;
					const int beginningListOperations = Efficiency::globalListOperations;
					const int beginningHashOperations = Efficiency::globalHashOperations;
					const int beginningBinaryTreeOperations = Efficiency::globalBinaryTreeOperations;
					Item& newItem = itemArray.append(Interface::addNewItem(itemArray, itemList));
					itemList.insertLast(newItem);
					itemHashTable.add(newItem.uid, newItem);
					itemUidBst.insert(newItem.uid, newItem);
					itemMarginBst.insert(newItem.getMargin(), newItem);
					cout << "Item added: " << endl << endl;
					cout << newItem << endl;
					cout << "The last operation took " << Efficiency::globalArrayOperations - beginningArrayOperations << " Array operations." << endl;
					cout << "The last operation took " << Efficiency::globalListOperations - beginningListOperations << " List operations." << endl;
					cout << "The last operation took " << Efficiency::globalHashOperations - beginningHashOperations << " Hash operations." << endl;
					cout << "The last operation took " << Efficiency::globalBinaryTreeOperations - beginningBinaryTreeOperations << " BST operations." << endl << endl;
					cout << "Would you like to add another item? [1] Yes [2] No" << endl;
					inputAgain = Input::getInt(1, 2);
				} while (inputAgain == 1);

				break;
			}
			case 2: //Delete data
			{
				do
				{
					Interface::displayDeleteMenu();
					Interface::promptOption();
					inputSubMenu = Input::getInt(1, 4);

					switch (inputSubMenu)
					{
						case 1://Delete data -> deleteByUid
						{
							const int beginningListOperations = Efficiency::globalListOperations;
							const int beginningHashOperations = Efficiency::globalHashOperations;
							const int beginningBinaryTreeOperations = Efficiency::globalBinaryTreeOperations;
							Interface::deleteByUid(itemList, itemHashTable, itemUidBst, itemMarginBst);
							cout << "The last operation took " << Efficiency::globalListOperations - beginningListOperations << " List operations." << endl;
							cout << "The last operation took " << Efficiency::globalHashOperations - beginningHashOperations << " Hash operations." << endl;
							cout << "The last operation took " << Efficiency::globalBinaryTreeOperations - beginningBinaryTreeOperations << " BST operations." << endl << endl;
							Interface::pause();
							break;
						}
						case 2://Delete data -> deleteByName
						{
							const int beginningListOperations = Efficiency::globalListOperations;
							const int beginningHashOperations = Efficiency::globalHashOperations;
							const int beginningBinaryTreeOperations = Efficiency::globalBinaryTreeOperations;
							Interface::deleteByName(itemList, itemHashTable, itemUidBst, itemMarginBst);
							cout << "The last operation took " << Efficiency::globalListOperations - beginningListOperations << " List operations." << endl;
							cout << "The last operation took " << Efficiency::globalHashOperations - beginningHashOperations << " Hash operations." << endl;
							cout << "The last operation took " << Efficiency::globalBinaryTreeOperations - beginningBinaryTreeOperations << " BST operations." << endl << endl;
							Interface::pause();
							break;
						}
						case 3://Delete data -> deleteByUpc
						{
							const int beginningListOperations = Efficiency::globalListOperations;
							const int beginningHashOperations = Efficiency::globalHashOperations;
							const int beginningBinaryTreeOperations = Efficiency::globalBinaryTreeOperations;
							Interface::deleteByUpc(itemList, itemHashTable, itemUidBst, itemMarginBst);
							cout << "The last operation took " << Efficiency::globalListOperations - beginningListOperations << " List operations." << endl;
							cout << "The last operation took " << Efficiency::globalHashOperations - beginningHashOperations << " Hash operations." << endl;
							cout << "The last operation took " << Efficiency::globalBinaryTreeOperations - beginningBinaryTreeOperations << " BST operations." << endl << endl;
							Interface::pause();
							break;
						}
						default:
						{
							break;
						}
					}
				} while (inputSubMenu != 4);

				break;
			}
			case 3: //Search
			{
				const int beginningListOperations = Efficiency::globalListOperations;
				const int beginningHashOperations = Efficiency::globalHashOperations;
				Interface::searchForItem(itemHashTable);
				cout << "The last operation took " << Efficiency::globalListOperations - beginningListOperations << " List operations." << endl;
				cout << "The last operation took " << Efficiency::globalHashOperations - beginningHashOperations << " Hash operations." << endl << endl;

				Interface::pause();
				break;
			}
			case 4: //Print items sorted by UID
			{
				const int beginningBinaryTreeOperations = Efficiency::globalBinaryTreeOperations;
				Interface::clearScreen();
				BSTTraversal::inorder(itemUidBst);
				cout << "The last operation took " << Efficiency::globalBinaryTreeOperations - beginningBinaryTreeOperations << " BST operations." << endl << endl;

				Interface::pause();
				break;
			}
			case 5: //Print hash table
			{
				const int beginningListOperations = Efficiency::globalListOperations;
				const int beginningHashOperations = Efficiency::globalHashOperations;
				Interface::displayHashTable(itemHashTable);
				cout << "The last operation took " << Efficiency::globalListOperations - beginningListOperations << " List operations." << endl;
				cout << "The last operation took " << Efficiency::globalHashOperations - beginningHashOperations << " Hash operations." << endl << endl;

				Interface::pause();
				break;
			}
			case 6: //Print Tree
			{
				Interface::clearScreen();
				cout << "***************" << endl;
				cout << "*** UID BST ***" << endl;
				cout << "***************" << endl;
				BSTTraversal::postorder(itemUidBst);
				cout << endl;
				cout << "*************************" << endl;
				cout << "*** PROFIT MARGIN BST ***" << endl;
				cout << "*************************" << endl;
				BSTTraversal::postorder(itemMarginBst);
				Interface::pause();
				break;
			}
			case 7: //Efficiency
			{
				Interface::clearScreen();
				cout << "There are " << itemList.getCount() << " data entries." << endl;
				cout << endl;
				cout << "The total number of Array operations since launch is: " << Efficiency::globalArrayOperations << "." << endl;
				cout << "The total number of List operations since launch is: " << Efficiency::globalListOperations << "." << endl;
				cout << "The total number of Hash operations since launch is: " << Efficiency::globalHashOperations << "." << endl;
				cout << "The total number of BST operations since launch is: " << Efficiency::globalBinaryTreeOperations << "." << endl;
				cout << endl;
				cout << "The size of the hash table is " << itemHashTable.getSize() << "." << endl;
				cout << "The load factor of the hash table is " << itemHashTable.calcLoadFactor() << "." << endl;
				cout << "There are currently " << itemHashTable.getOffTable() << " hash collisions." << endl;
				cout << endl;
				cout << "The UID BST is " << itemUidBst.maxDepth() << " levels deep." << endl;
				cout << "The Profit Margin BST is " << itemMarginBst.maxDepth() << " levels deep." << endl;
				cout << endl;
				Interface::pause();
				break;
			}
			case 8: //Margins and profitability
			{
				Interface::clearScreen();
				const int beginningBinaryTreeOperations = Efficiency::globalBinaryTreeOperations;
				BSTTraversal::inorder(itemMarginBst);
				cout << "The last operation took " << Efficiency::globalBinaryTreeOperations - beginningBinaryTreeOperations << " BST operations." << endl << endl;
				Interface::pause();
				break;
			}
			case 9: //Save to file
			{
				//Save the list into file
				cout << "Saving to file..." << endl;
				FileIO::saveListIntoFile(itemList, filepath);
				cout << "Success." << endl;
				Interface::pause();
				break;
			}
			default:
			{
				break;
			}
		}
	} while (inputMainMenu != 0); //Quit

	FileIO::saveListIntoFile(itemList, filepath);

	Interface::displayGoodbye();
	Interface::pause();
	return 0;
}