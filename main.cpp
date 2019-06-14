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

	int inputMainMenu;
	do
	{
		Interface::displayMainMenu();
		Interface::promptOption();
		inputMainMenu = Input::getInt(1, 9);

		int inputSubMenu, inputAgain, intItemToDelete, positionOfItem = 0;
		string strItemToDelete;

		switch (inputMainMenu)
		{
		case 1:
		{
			do
			{
				/*
				Interface::clearScreen(true);
				cout << "Enter the 4-digit UID of the item" << endl;
				newUid = Input::getInt(1, 5999);
				string temp = to_string(newUid);
				while (temp.length() != 4)
				{
					cout << "Error: UID must be a 4-digits long, try again:" << endl;
					newUid = Input::getInt(1, 5999);
				}
				cout << "Enter the UPC of the item" << endl;
				newUpc = Input::getString();
				while (newUpc.length() != 13)
				{
					cout << "Error: UPC must be 13-digits long, try again:" << endl;
					newUpc = Input::getString();
				}
				cout << "Enter the name of the item" << endl;
				newName = Input::getString();
				cout << "Enter the size of the item" << endl;
				newSize = Input::getString();
				cout << "Enter the category of the item" << endl;
				newCategory = Input::getInt(1, 6);
				cout << "Enter the whole-sale of the item" << endl;
				newWholeSale = Input::getDouble(0.0, 100000.0);
				cout << "Enter the retail price of the item" << endl;
				newRetail = Input::getDouble(0.0, 100000.0);
				cout << "Enter the quantity of the tem" << endl;
				newQuantity = Input::getInt(1, 1000);
				Item newItem(newUid, newUpc, newName, newSize, newCategory, newWholeSale, newRetail, newQuantity);
				itemList.insertLast(newItem);
				for (int i = 0; i < itemList.getCount(); i++)
				{
					cout << itemList[i] << endl;
				}
				Interface::pause();
				cout << "Would you like to add another item? [1] Yes [2] No" << endl;
				inputAgain = Input::getInt(1, 2);
				Interface::clearScreen(true);
				*/
				Item newItem = Interface::addNewItem(itemList);
				itemList.insertLast(newItem);
				for (int i = 0; i < itemList.getCount(); i++)
				{
					cout << itemList[i] << endl;
				}
				cout << endl;
				cout << "Would you like to add another item? [1] Yes [2] No" << endl;
				inputAgain = Input::getInt(1, 2);
				Interface::clearScreen(true);
			} while (!inputAgain == 2);

			break;
		}
		case 2:
		{
			do
			{
				int i = 0;
				Interface::clearScreen(true);
				Interface::displayDeleteMenu();
				Interface::promptOption();
				inputSubMenu = Input::getInt(1, 4);
				switch (inputSubMenu)
				{
				case 1:
				{
					Interface::clearScreen(true);
					cout << "Enter the UID of the item you want to delete:" << endl;
					intItemToDelete = Input::getInt(1,5999);
					while (itemList[i].uid != intItemToDelete)
					{
						positionOfItem++;
						i++;
					}
					itemList.remove(positionOfItem);
					for (int i = 0; i < itemList.getCount(); i++)
					{
						cout << itemList[i] << endl;
					}
					Interface::pause();
				}
				Interface::clearScreen(true);
				break;
				case 2:
				{
					Interface::clearScreen(true);
					cout << "Enter the Name of the item you want to delete:" << endl;
					strItemToDelete = Input::getString();
					while (itemList[i].name != strItemToDelete)
					{
						positionOfItem++;
						i++;
					}
					itemList.remove(positionOfItem);
					for (int i = 0; i < itemList.getCount(); i++)
					{
						cout << itemList[i] << endl;
					}
					Interface::pause();
				}
				Interface::clearScreen(true);
				break;
				case 3:
				{
					cout << "Enter the UPC of the item you want to delete:" << endl;
					strItemToDelete = Input::getString();
					while (itemList[i].upc != strItemToDelete)
					{
						positionOfItem++;
						i++;
					}
					itemList.remove(positionOfItem);
					for (int i = 0; i < itemList.getCount(); i++)
					{
						cout << itemList[i] << endl;
					}
					Interface::pause();
				}
				Interface::clearScreen(true);
				break;
				default:
					break;
				}
			} while (!inputSubMenu == 4);
		}
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
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
			break;
		case 8:
			break;
		default:
			break;
		}
	} while (inputMainMenu != 9);

	Interface::pause();
	return 0;
}