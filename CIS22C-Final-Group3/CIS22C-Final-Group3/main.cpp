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
#include "Stack.h"
#include "Queue.h"
#include "HashTable.h"

using namespace std;

int main()
{
	Interface::initialize();
	Interface::printHeader();
	
	std::string filepath;
	cout << "Enter path to data file: ";
	filepath = Input::getString();

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

	FileIO::saveListIntoFile(itemList, filepath);

	Interface::displayInventory(itemList);
	Interface::pause();
	
	HashTable<Item> itemHashTable;

	/*for (int i = 0; i < itemList.getCount(); i++)
	{
		itemHashTable.add(itemList[i].uid, itemList[i]);
	}*/

	int inputMainMenu;
	do
	{
		Interface::displayMainMenu();
		Interface::promptOption();
		inputMainMenu = Input::getInt(1, 9);

		int inputSubMenu, inputAgain, positionOfItem = 0;

		switch (inputMainMenu)
		{
		case 1:
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
		case 2:
		{
			do
			{
				Interface::clearScreen(true);
				Interface::displayDeleteMenu();
				Interface::promptOption();
				inputSubMenu = Input::getInt(1, 4);

				switch (inputSubMenu)
				{
				case 1:
				{
					Interface::deleteByUid(itemList);
					Interface::displayInventory(itemList);
					Interface::pause();
				}
				Interface::clearScreen(true);
				break;
				case 2:
				{
					Interface::deleteByName(itemList);
					Interface::displayInventory(itemList);
					Interface::pause();
				}
				Interface::clearScreen(true);
				break;
				case 3:
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
		case 3:
		{

		}
		Interface::clearScreen(true);
			break;
		case 4:
		{

		}
		Interface::clearScreen(true);
			break;
		case 5:
		{
			do
			{
				Interface::displaKeyMenu();
				Interface::promptOption();
				inputSubMenu = Input::getInt(1, 4);
				switch (inputSubMenu)
				{
				case 1:
				{

				}
				Interface::clearScreen(true);
					break;
				case 2:
				{

				}
				Interface::clearScreen(true);
					break;
				case 3:
				{

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
		case 6:
			do
			{
				Interface::clearScreen(true);
				Interface::displayTypeTrees();
				Interface::promptOption();
				inputSubMenu = Input::getInt(1, 3);

				switch (inputSubMenu)
				{
				case 1:
					break;
				case 2:
					break;
				default:
					break;
				}
			} while (inputSubMenu != 3);
			Interface::clearScreen(true);
			break;
		case 7:
		{

		}
			break;
		case 8:
		{

		}
			break;
		default:
			break;
		}
	} while (inputMainMenu != 9);

	Interface::pause();
	return 0;
}