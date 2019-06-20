#include <iostream>
#include <iomanip>
#include <string>

#include "Interface.h"
#include "Input.h"
#include "Item.h"
#include "HashTable.h"
#include "BST.h"
#include "BSTTraversal.h"

namespace Interface
{
	std::string generateBars(const int number)
	{
		std::string bars = std::string();
		const std::string bar = BARS_CHARACTER;

		for (int i = 0; i < number; i++)
		{
			bars.append(bar);
		}

		return bars;
	}

	void clearScreen(const bool displayHeader)
	{
		std::system("CLS");
		if (displayHeader)
		{
			printHeader();
		}
		return;
	}

	void pause()
	{
		std::cout << "Press ENTER to continue.";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	void initialize()
	{
		//Resize the terminal window
		const std::string systemResizeStr = "mode " + std::to_string(TERMINAL_WIDTH) + ", " + std::to_string(TERMINAL_HEIGHT);
		system(systemResizeStr.c_str());

		//Rename the window
		system("title Instaventory by Olivier Chan, Luis Guerrero, Hiren Rathod, and Yue Pan");

		//Format std::cout
		std::cout << std::fixed << std::setprecision(2);
	}

	void printHeader()
	{
		const std::string bars = generateBars(TERMINAL_WIDTH);
		const std::string header1 = R"(  _____              _                             _                      )";
		const std::string header2 = R"( |_   _|            | |                           | |                     )";
		const std::string header3 = R"(   | |   _ __   ___ | |_  __ _ __   __ ___  _ __  | |_  ___   _ __  _   _ )";
		const std::string header4 = R"(   | |  | '_ \ / __|| __|/ _` |\ \ / // _ \| '_ \ | __|/ _ \ | '__|| | | |)";
		const std::string header5 = R"(  _| |_ | | | |\__ \| |_| (_| | \ V /|  __/| | | || |_| (_) || |   | |_| |)";
		const std::string header6 = R"( |_____||_| |_||___/ \__|\__,_|  \_/  \___||_| |_| \__|\___/ |_|    \__, |)";
		const std::string header7 = R"(                                                                     __/ |)";
		const std::string header8 = R"(                                                                    |___/ )";

		std::cout << std::right;

		std::cout << std::setw((TERMINAL_WIDTH + header1.length()) / 2) << header1 << std::endl
			<< std::setw((TERMINAL_WIDTH + header2.length()) / 2) << header2 << std::endl
			<< std::setw((TERMINAL_WIDTH + header3.length()) / 2) << header3 << std::endl
			<< std::setw((TERMINAL_WIDTH + header4.length()) / 2) << header4 << std::endl
			<< std::setw((TERMINAL_WIDTH + header5.length()) / 2) << header5 << std::endl
			<< std::setw((TERMINAL_WIDTH + header6.length()) / 2) << header6 << std::endl
			<< std::setw((TERMINAL_WIDTH + header7.length()) / 2) << header7 << std::endl
			<< std::setw((TERMINAL_WIDTH + header8.length()) / 2) << header8 << std::endl << std::endl;

		std::cout << bars << std::endl << std::endl;

		return;
	}

	void promptOption()
	{
		std::cout << "Choose an option: ";
	}

	void displayMainMenu()
	{
		const std::string bars = generateBars(TERMINAL_WIDTH);
		const std::string mainMenuText = "[ MAIN MENU ]";
		const std::string addNewDataText = "[ 1 ] ADD ITEM";
		const std::string deleteDataText = "[ 2 ] DELETE ITEM";
		const std::string searchText = "[ 3 ] SEARCH BY UID";
		const std::string listDataKeyText = "[ 4 ] LIST DATA SORTED BY UID";
		const std::string listDataHashText = "[ 5 ] PRINT HASH TABLE";
		const std::string printTreeText = "[ 6 ] PRINT BINARY TREE";
		const std::string efficiencyText = "[ 7 ] EFFICIENCY";
		const std::string teamOptionText = "[ 8 ] MARGINS AND PROFITABILITY";
		const std::string saveText = "[ 9 ] SAVE DATA TO FILE";
		const std::string quitText = "[ 0 ] QUIT";


		const size_t titleMargin = (TERMINAL_WIDTH + mainMenuText.length()) / 2;
		const size_t optionMargin = titleMargin - mainMenuText.length();

		std::cout << std::right;

		std::cout << std::setw(titleMargin) << mainMenuText << std::endl << std::endl << bars << std::endl << std::endl;

		std::cout << std::setw(optionMargin + addNewDataText.length()) << addNewDataText << std::endl << std::endl
			<< std::setw(optionMargin + deleteDataText.length()) << deleteDataText << std::endl << std::endl
			<< std::setw(optionMargin + searchText.length()) << searchText << std::endl << std::endl
			<< std::setw(optionMargin + listDataKeyText.length()) << listDataKeyText << std::endl << std::endl
			<< std::setw(optionMargin + listDataHashText.length()) << listDataHashText << std::endl << std::endl
			<< std::setw(optionMargin + printTreeText.length()) << printTreeText << std::endl << std::endl
			<< std::setw(optionMargin + efficiencyText.length()) << efficiencyText << std::endl << std::endl
			<< std::setw(optionMargin + teamOptionText.length()) << teamOptionText << std::endl << std::endl
			<< std::setw(optionMargin + saveText.length()) << saveText << std::endl << std::endl
			<< std::setw(optionMargin + quitText.length()) << quitText << std::endl << std::endl
			<< bars << std::endl << std::endl;

		return;

	}
	//display inventory in the array
	void displayInventory(Array<Item>& itemArray)
	{
		const std::string uidText = "UID:";
		const std::string upcText = "UPC:";
		const std::string nameText = "NAME:";
		const std::string sizeText = "SIZE:";
		const std::string categoryText = "CATEGORY:";
		const std::string wholesaleText = "WHOLESALE:";
		const std::string retailText = "RETAIL:";
		const std::string quantityText = "QUANTITY:";

		const size_t columnSpacing = 3;
		const size_t uidColumnLength = 3 + columnSpacing;
		const size_t upcColumnLength = 13 + columnSpacing;
		const size_t sizeColumnLength = 7 + columnSpacing;
		const size_t categoryColumnLength = 9 + columnSpacing;
		const size_t wholesaleColumnLength = wholesaleText.length() + columnSpacing;
		const size_t retailColumnLength = retailText.length() + columnSpacing;
		const size_t quantityColumnLength = quantityText.length() + columnSpacing;

		const size_t nameColumnLength = ((TERMINAL_WIDTH - uidColumnLength - upcColumnLength - sizeColumnLength - categoryColumnLength - quantityColumnLength - wholesaleColumnLength - retailColumnLength) / 2) + 15;

		std::cout << std::left;

		std::cout << std::setw(uidColumnLength) << uidText
			<< std::setw(upcColumnLength) << upcText
			<< std::setw(nameColumnLength) << nameText
			<< std::setw(sizeColumnLength) << sizeText
			<< std::setw(categoryColumnLength) << categoryText
			<< std::setw(wholesaleColumnLength) << wholesaleText
			<< std::setw(retailColumnLength) << retailText
			<< std::setw(quantityColumnLength) << quantityText
			<< std::endl << std::endl;

		for (int i = 0; i < itemArray.getSize(); i++)
		{

			std::cout << std::setw(uidColumnLength) << itemArray[i].uid
				<< std::setw(upcColumnLength) << itemArray[i].upc
				<< std::setw(nameColumnLength) << itemArray[i].name.substr(0, 30)
				<< std::setw(sizeColumnLength) << itemArray[i].size;
			if (itemArray[i].category == 1)
			{
				std::cout << std::setw(categoryColumnLength) << "Snack";
			}
			else if (itemArray[i].category == 2)
			{
				std::cout << std::setw(categoryColumnLength) << "Drink";
			}
			else if (itemArray[i].category == 3)
			{
				std::cout << std::setw(categoryColumnLength) << "Tabacco";
			}
			else if (itemArray[i].category == 4)
			{
				std::cout << std::setw(categoryColumnLength) << "Lotto";
			}
			else if (itemArray[i].category == 5)
			{
				std::cout << std::setw(categoryColumnLength) << "Misc";
			}
			std::cout << std::setw(wholesaleColumnLength) << std::fixed << std::setprecision(2) << itemArray[i].wholesale
				<< std::setw(retailColumnLength) << std::fixed << std::setprecision(2) << itemArray[i].retail
				<< std::setw(quantityColumnLength) << itemArray[i].quantity;

			std::cout << std::endl << std::endl;
		}

	}
	Item addNewItem(Array<Item>& itemArray, List<Item>& itemList)
	{
		clearScreen();

		int newUid, newCategory, newQuantity;
		std::string newUpc, newName, newSize;
		double newWholeSale, newRetail;

		const std::string bars = generateBars(TERMINAL_WIDTH);
		const std::string titleText = "[ ADD NEW DATA ]";

		const size_t titleMargin = (TERMINAL_WIDTH + titleText.length()) / 2;
		std::cout << std::setw(titleMargin) << titleText << std::endl << std::endl << bars << std::endl << std::endl;

		bool valid;

		//Enter UID
		valid = false;
		while (!valid)
		{
			valid = true;
			
			std::cout << "Enter the UID of the item (0 - 9999)" << std::endl;
			newUid = Input::getInt(0, 9999);
			std::cout << std::endl;
			try
			{

				for (int i = 0; i < itemArray.getSize(); i++)
				{
					//Check if the UID already exists in the array
					if (itemArray[i].uid == newUid)
					{
						//The UID exists in the array, but we need to check that it also exists in the list
						for (int i = 0; i < itemList.getCount(); i++)
						{
							//Check if the duplicate UID is in the list - if it isn't then it means the duplicate UID has actually been deleted and it is safe to add the new item.
							if (itemList[i].uid == newUid)
							{
								std::cout << "ERROR: The UID you entered already exists, try another UID." << std::endl << std::endl;
								valid = false;
							}
						}
					}
				}
			}
			catch (std::out_of_range& e)
			{
				std::cout << e.what();
			}
		}

		//Enter UPC
		valid = false;
		while (!valid)
		{
			valid = true;

			std::cout << "Enter the UPC of the item (12 digits)" << std::endl;
			newUpc = Input::getString();
			std::cout << std::endl;

			//UPCs must be either blank or 12 digits long.
			if (newUpc.length() == 0 || newUpc.length() == 12)
			{
				for (int i = 0; i < itemArray.getSize(); i++)
				{
					//Check if the UPC already exists in the array
					if (itemArray[i].upc == newUpc)
					{
						//The UPC exists in the array, but we need to check that it also exists in the list
						for (int i = 0; i < itemList.getCount(); i++)
						{
							//Check if the duplicate UPC is in the list - if it isn't then it means the duplicate UPC has actually been deleted and it is safe to add the new item.
							if (itemList[i].upc == newUpc)
							{
								std::cout << "ERROR: The UPC you entered already exists, try another UPC." << std::endl << std::endl;
								valid = false;
							}
						}
					}
				}
			}
			else
			{
				std::cout << "ERROR: UPC must be 12 digits long or blank." << std::endl << std::endl;
				valid = false;
			}
		}

		std::cout << "Enter the name of the item" << std::endl;
		newName = Input::getString();
		std::cout << std::endl;

		std::cout << "Enter the size of the item" << std::endl;
		newSize = Input::getString();
		std::cout << std::endl;

		std::cout << "Enter the category of the item: [1]Snack [2]Drink [3]Tobacco [4]Lotto [5]Miscellaneous" << std::endl;
		newCategory = Input::getInt(1, 5);
		std::cout << std::endl;

		std::cout << "Enter the wholesale price of the item" << std::endl;
		newWholeSale = Input::getDouble();
		std::cout << std::endl;

		std::cout << "Enter the retail price of the item" << std::endl;
		newRetail = Input::getDouble();
		std::cout << std::endl;

		std::cout << "Enter the quantity of the item" << std::endl;
		newQuantity = Input::getInt();
		std::cout << std::endl;

		Item newItem = Item(newUid, newUpc, newName, newSize, newCategory, newWholeSale, newRetail, newQuantity);

		return newItem;
	}
	void displayDeleteMenu()
	{
		clearScreen();

		const std::string bars = generateBars(TERMINAL_WIDTH);
		const std::string deleteText = "[ DELETE ]";
		const std::string byUidText = "[ 1 ] BY UID";
		const std::string byNameText = "[ 2 ] BY NAME";
		const std::string byUpcText = "[ 3 ] BY UPC";
		const std::string backText = "[ 4 ] BACK";

		const size_t titleMargin = (TERMINAL_WIDTH + deleteText.length()) / 2;
		const size_t optionMargin = titleMargin - deleteText.length();

		std::cout << std::right;

		std::cout << std::setw(titleMargin) << deleteText << std::endl << std::endl << bars << std::endl << std::endl;

		std::cout << std::setw(optionMargin + byUidText.length()) << byUidText << std::endl << std::endl
			<< std::setw(optionMargin + byNameText.length()) << byNameText << std::endl << std::endl
			<< std::setw(optionMargin + byUpcText.length()) << byUpcText << std::endl << std::endl
			<< std::setw(optionMargin + backText.length()) << backText << std::endl << std::endl
			<< bars << std::endl << std::endl;

		return;
	}
	void deleteByUid(List<Item>& itemList, HashTable<int, Item>& itemHashTable, BST<int, Item>& itemUidBst, BST<double, Item>& itemMarginBst)
	{
		clearScreen();

		const std::string bars = generateBars(TERMINAL_WIDTH);
		const std::string deleteText = "[ DELETE ]";

		const size_t titleMargin = (TERMINAL_WIDTH + deleteText.length()) / 2;
		const size_t optionMargin = titleMargin - deleteText.length();

		std::cout << std::right;

		std::cout << std::setw(titleMargin) << deleteText << std::endl << std::endl << bars << std::endl << std::endl;

		std::cout << "Enter the UID of the item you want to delete:" << std::endl;
		const int uidToDelete = Input::getInt(1, 9999);

		//Check that the item exists
		for (int i = 0; i < itemList.getCount(); i++)
		{
			if (itemList[i].uid == uidToDelete)
			{
				const Item itemToDelete = itemList[i];
				itemList.remove(i);
				itemHashTable.remove(itemToDelete.uid, itemToDelete);
				itemUidBst.remove(itemToDelete.uid, itemToDelete);
				itemMarginBst.remove(itemToDelete.getMargin(), itemToDelete);
				std::cout << std::endl << "Item found: " << std::endl;
				std::cout << itemToDelete << std::endl;
				std::cout << "Item successfully deleted." << std::endl << std::endl;
				return;
			}
		}

		//The item doesn't exist
		std::cout << "ERROR: The UID you entered does not exist." << std::endl << std::endl;
	}
	void deleteByName(List<Item>& itemList, HashTable<int, Item>& itemHashTable, BST<int, Item>& itemUidBst, BST<double, Item>& itemMarginBst)
	{
		clearScreen();

		const std::string bars = generateBars(TERMINAL_WIDTH);
		const std::string deleteText = "[ DELETE ]";

		const size_t titleMargin = (TERMINAL_WIDTH + deleteText.length()) / 2;
		const size_t optionMargin = titleMargin - deleteText.length();

		std::cout << std::right;

		std::cout << std::setw(titleMargin) << deleteText << std::endl << std::endl << bars << std::endl << std::endl;

		std::cout << "Enter the name of the item you want to delete:" << std::endl << std::endl;
		const std::string nameToDelete = Input::getString();

		//Check that the item exists
		for (int i = 0; i < itemList.getCount(); i++)
		{
			if (itemList[i].name.find(nameToDelete) != std::string::npos)
			{
				const Item itemToDelete = itemList[i];
				itemList.remove(i);
				itemHashTable.remove(itemToDelete.uid, itemToDelete);
				itemUidBst.remove(itemToDelete.uid, itemToDelete);
				itemMarginBst.remove(itemToDelete.getMargin(), itemToDelete);
				std::cout << std::endl << "Item found: " << std::endl;
				std::cout << itemToDelete << std::endl;
				std::cout << "Item successfully deleted." << std::endl << std::endl;
				return;
			}
		}

		//The item doesn't exist
		std::cout << "ERROR: The name you entered does not exist." << std::endl << std::endl;
	}
	void deleteByUpc(List<Item>& itemList, HashTable<int, Item>& itemHashTable, BST<int, Item>& itemUidBst, BST<double, Item>& itemMarginBst)
	{
		clearScreen();

		const std::string bars = generateBars(TERMINAL_WIDTH);
		const std::string deleteText = "[ DELETE ]";

		const size_t titleMargin = (TERMINAL_WIDTH + deleteText.length()) / 2;
		const size_t optionMargin = titleMargin - deleteText.length();

		std::cout << std::right;

		std::cout << std::setw(titleMargin) << deleteText << std::endl << std::endl << bars << std::endl << std::endl;

		std::cout << "Enter the UPC of the item you want to delete:" << std::endl << std::endl;
		const std::string upcToDelete = Input::getString();

		//Check that the item exists
		for (int i = 0; i < itemList.getCount(); i++)
		{
			if (itemList[i].upc.find(upcToDelete) != std::string::npos)
			{
				const Item itemToDelete = itemList[i];
				itemList.remove(i);
				itemHashTable.remove(itemToDelete.uid, itemToDelete);
				itemUidBst.remove(itemToDelete.uid, itemToDelete);
				itemMarginBst.remove(itemToDelete.getMargin(), itemToDelete);
				std::cout << std::endl << "Item found: " << std::endl;
				std::cout << itemToDelete << std::endl;
				std::cout << "Item successfully deleted." << std::endl << std::endl;
				return;
			}
		}

		//The item doesn't exist
		std::cout << "ERROR: The name you entered does not exist." << std::endl << std::endl;
	}
	void searchForItem(HashTable<int, Item>& itemHashTable)
	{
		clearScreen();

		const std::string bars = generateBars(TERMINAL_WIDTH);
		const std::string sortText = "[ SEARCH ]";

		const size_t titleMargin = (TERMINAL_WIDTH + sortText.length()) / 2;
		const size_t optionMargin = titleMargin - sortText.length();

		std::cout << std::right;

		std::cout << std::setw(titleMargin) << sortText << std::endl << std::endl << bars << std::endl << std::endl;

		std::cout << "Enter the UID of the item to search for:" << std::endl;
		const int uidToFind = Input::getInt();

		//Try to find the item in the hash table
		HashList<int, Item>* list = itemHashTable.getListAtKey(uidToFind);
		for (int i = 0; i < list->getCount(); i++)
		{
			if (list->getData(i).uid = uidToFind)
			{
				std::cout << std::endl << "Found item: " << std::endl << std::endl << list->getData(i) << std::endl;
				return;
			}
		}

		//The item doesn't exist
		std::cout << "ERROR: The UID you entered does not exist." << std::endl << std::endl;
	}
	Item searchByName(Array<Item>& itemArray)
	{
		clearScreen(true);

		const std::string bars = generateBars(TERMINAL_WIDTH);
		const std::string searchByNameText = "[ SEARCH NAME ]";

		const size_t titleMargin = (TERMINAL_WIDTH + searchByNameText.length()) / 2;

		std::cout << std::right;

		std::cout << std::setw(titleMargin) << searchByNameText << std::endl << std::endl << bars << std::endl << std::endl;

		std::cout << "Enter the name of the item you want to search:" << std::endl << std::endl;
		const std::string userInputName = Input::getString();

		for (int i = 0; i < itemArray.getSize(); i++)
		{
			if (itemArray[i].name.find(userInputName) != std::string::npos)
			{
				return itemArray[i];
			}
		}

		return Item();
	}
	Item searchByUpc(Array<Item>& itemArray)
	{
		clearScreen(true);

		const std::string bars = generateBars(TERMINAL_WIDTH);
		const std::string searchByUpcText = "[ SEARCH UPC ]";

		const size_t titleMargin = (TERMINAL_WIDTH + searchByUpcText.length()) / 2;

		std::cout << std::right;

		std::cout << std::setw(titleMargin) << searchByUpcText << std::endl << std::endl << bars << std::endl << std::endl;

		std::cout << "Enter the UPC of the item you want to search:" << std::endl << std::endl;
		const std::string userInputUpc = Input::getString();

		for (int i = 0; i < itemArray.getSize(); i++)
		{
			if (itemArray[i].upc.find(userInputUpc) != std::string::npos)
			{
				return itemArray[i];
			}
		}

		return Item();
	}
	void displayHashTable(HashTable<int, Item>& itemHashTable)
	{
		clearScreen();

		const std::string bars = generateBars(TERMINAL_WIDTH);
		const std::string titleText = "[ HASH TABLE ]";
		const std::string uidText = "UID:";
		const std::string upcText = "UPC:";
		const std::string nameText = "NAME:";
		const std::string sizeText = "SIZE:";
		const std::string categoryText = "CATEGORY:";
		const std::string wholesaleText = "WHOLESALE:";
		const std::string retailText = "RETAIL:";
		const std::string quantityText = "QUANTITY:";

		const size_t columnSpacing = 3;
		const size_t uidColumnLength = 3 + columnSpacing;
		const size_t upcColumnLength = 13 + columnSpacing;
		const size_t sizeColumnLength = 7 + columnSpacing;
		const size_t categoryColumnLength = 9 + columnSpacing;
		const size_t wholesaleColumnLength = wholesaleText.length() + columnSpacing;
		const size_t retailColumnLength = retailText.length() + columnSpacing;
		const size_t quantityColumnLength = quantityText.length() + columnSpacing;

		const size_t titleMargin = (TERMINAL_WIDTH + titleText.length()) / 2;
		const size_t nameColumnLength = ((TERMINAL_WIDTH - uidColumnLength - upcColumnLength - sizeColumnLength - categoryColumnLength - quantityColumnLength - wholesaleColumnLength - retailColumnLength) / 2) + 25;

		std::cout << std::setw(titleMargin) << titleText << std::endl << std::endl << bars << std::endl << std::endl;

		std::cout << std::left;

		std::cout << std::setw(uidColumnLength) << uidText
			<< std::setw(upcColumnLength) << upcText
			<< std::setw(nameColumnLength) << nameText
			<< std::setw(sizeColumnLength) << sizeText
			<< std::setw(categoryColumnLength) << categoryText
			<< std::setw(wholesaleColumnLength) << wholesaleText
			<< std::setw(retailColumnLength) << retailText
			<< std::setw(quantityColumnLength) << quantityText
			<< std::endl << std::endl;

		//Loop through each linked list inside the hash table
		for (int i = 0; i < itemHashTable.getSize(); i++)
		{
			//Get the linked list at hash table array position i
			HashList<int, Item>* list = itemHashTable.getListAtKey(i);
			std::cout << "[" << i << "]" << std::endl;
			//Loop through each item inside the linked list
			for (int i = 0; i < list->getCount(); i++)
			{
				Item& item = list->getData(i);

				//Print the item out
				std::cout << std::setw(uidColumnLength) << item.uid
					<< std::setw(upcColumnLength) << item.upc
					<< std::setw(nameColumnLength) << item.name.substr(0, 55)
					<< std::setw(sizeColumnLength) << item.size;
				if (item.category == 1)
				{
					std::cout << std::setw(categoryColumnLength) << " Snack";
				}
				else if (item.category == 2)
				{
					std::cout << std::setw(categoryColumnLength) << " Drink";
				}
				else if (item.category == 3)
				{
					std::cout << std::setw(categoryColumnLength) << " Tobacco";
				}
				else if (item.category == 4)
				{
					std::cout << std::setw(categoryColumnLength) << " Lotto";
				}
				else if (item.category == 5)
				{
					std::cout << std::setw(categoryColumnLength) << " Misc";
				}
				std::cout << std::setw(wholesaleColumnLength) << std::fixed << std::setprecision(2) << item.wholesale
					<< std::setw(retailColumnLength) << std::fixed << std::setprecision(2) << item.retail
					<< "  " << std::setw(quantityColumnLength) << item.quantity;

				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
	}
	void displayKeySequence(BST<int, Item>& itemUidBst)
	{
		clearScreen();

		const std::string bars = generateBars(TERMINAL_WIDTH);
		const std::string titleText = "[LIST BY UID]";
		const std::string uidText = "UID:";
		const std::string upcText = "UPC:";
		const std::string nameText = "NAME:";
		const std::string sizeText = "SIZE:";
		const std::string categoryText = "CATEGORY:";
		const std::string wholesaleText = "WHOLESALE:";
		const std::string retailText = "RETAIL:";
		const std::string quantityText = "QUANTITY:";

		const size_t columnSpacing = 3;
		const size_t uidColumnLength = 3 + columnSpacing;
		const size_t upcColumnLength = 13 + columnSpacing;
		const size_t sizeColumnLength = 9 + columnSpacing;
		const size_t categoryColumnLength = 9 + columnSpacing;
		const size_t wholesaleColumnLength = wholesaleText.length() + columnSpacing;
		const size_t retailColumnLength = retailText.length() + columnSpacing;
		const size_t quantityColumnLength = quantityText.length() + columnSpacing;

		const size_t titleMargin = (TERMINAL_WIDTH + titleText.length()) / 2;
		const size_t nameColumnLength = ((TERMINAL_WIDTH - uidColumnLength - upcColumnLength - sizeColumnLength - categoryColumnLength - quantityColumnLength - wholesaleColumnLength - retailColumnLength) / 2) + 25;

		std::cout << std::setw(titleMargin) << titleText << std::endl << std::endl << bars << std::endl << std::endl;

		std::cout << std::left;

		std::cout << std::setw(uidColumnLength) << uidText
			<< std::setw(upcColumnLength) << upcText
			<< std::setw(nameColumnLength) << nameText
			<< std::setw(sizeColumnLength) << sizeText
			<< std::setw(categoryColumnLength) << categoryText
			<< std::setw(wholesaleColumnLength) << wholesaleText
			<< std::setw(retailColumnLength) << retailText
			<< std::setw(quantityColumnLength) << quantityText
			<< std::endl << std::endl;
		/*
		for (int i = 0; i < itemArray.getSize(); i++)
		{
			//Print out each item
			std::cout << std::setw(uidColumnLength) << itemArray[i].uid
				<< std::setw(upcColumnLength) << itemArray[i].upc
				<< std::setw(nameColumnLength) << itemArray[i].name.substr(0, 55)
				<< std::setw(sizeColumnLength) << itemArray[i].size;
			if (itemArray[i].category == 1)
			{
				std::cout << std::setw(categoryColumnLength) << " Snack";
			}
			else if (itemArray[i].category == 2)
			{
				std::cout << std::setw(categoryColumnLength) << " Drink";
			}
			else if (itemArray[i].category == 3)
			{
				std::cout << std::setw(categoryColumnLength) << " Tobacco";
			}
			else if (itemArray[i].category == 4)
			{
				std::cout << std::setw(categoryColumnLength) << " Lotto";
			}
			else if (itemArray[i].category == 5)
			{
				std::cout << std::setw(categoryColumnLength) << " Misc";
			}
			std::cout  << std::setw(wholesaleColumnLength) << std::fixed << std::setprecision(2) << itemArray[i].wholesale
				<< std::setw(retailColumnLength) << std::fixed << std::setprecision(2) << itemArray[i].retail
				<< "   " << std::setw(quantityColumnLength) << itemArray[i].quantity;

			std::cout << std::endl << std::endl;
		}
		*/
	}
	void displayTypeTrees()
	{
		const std::string bars = generateBars(TERMINAL_WIDTH);
		const std::string typeTreesText = "[ TYPE OF TREES ]";
		const std::string bstText = "[ 1 ] AVL Tree WholeSale";
		const std::string avlTreeText = "[ 2 ] AVL Tree Retail";
		const std::string backtext = "[ 3 ] BACK";

		const size_t titleMargin = (TERMINAL_WIDTH + typeTreesText.length()) / 2;
		const size_t optionMargin = titleMargin - typeTreesText.length();

		std::cout << std::right;

		std::cout << std::setw(titleMargin) << typeTreesText << std::endl << std::endl << bars << std::endl << std::endl;

		std::cout << std::setw(optionMargin + bstText.length()) << bstText << std::endl << std::endl
			<< std::setw(optionMargin + avlTreeText.length()) << avlTreeText << std::endl << std::endl
			<< std::setw(optionMargin + backtext.length()) << backtext << std::endl << std::endl
			<< bars << std::endl << std::endl;

		return;
	}
	void displayMarginProfit(Array<Item>& itemArray, BST<double, Item>& itemMarginBst)
	{
		BSTTraversal::inorder(itemMarginBst);
		const std::string bars = generateBars(TERMINAL_WIDTH);
		const std::string typeTreesText = "[ MARGINS AND PROFITS ]";
		const std::string uidText = "UID:";
		const std::string nameText = "NAME:";
		const std::string profirMarginText = "PROFIT MARGIN:";
		const std::string profitText = "PROFIT:";

		const size_t columnSpacing = 3;
		const size_t uidColumnLength = 3 + columnSpacing;
		const size_t profitMarginColumnLength = profirMarginText.length() + columnSpacing;
		const size_t profitColumnLength = profitText.length() + columnSpacing;

		const size_t titleMargin = (TERMINAL_WIDTH + typeTreesText.length()) / 2;
		const size_t nameColumnLength = ((TERMINAL_WIDTH - uidColumnLength - profitMarginColumnLength - profitColumnLength) / 2) + 25;

		std::cout << std::right;

		std::cout << std::setw(titleMargin) << typeTreesText << std::endl << std::endl << bars << std::endl << std::endl;

		std::cout << std::left;

		std::cout << std::setw(uidColumnLength) << uidText
			<< std::setw(nameColumnLength) << nameText
			<< std::setw(profitMarginColumnLength) << profirMarginText
			<< std::setw(profitColumnLength) << profitText
			<< std::endl << std::endl;

		for (int i = 0; i < itemArray.getSize(); i++)
		{
			//Print out each item
			std::cout << std::setw(uidColumnLength) << itemArray[i].uid
				<< std::setw(nameColumnLength) << itemArray[i].name.substr(0, 55);
			std::cout << std::setw(profitMarginColumnLength) << std::fixed << std::setprecision(2) << itemArray[i].getMargin()
				<< std::setw(profitColumnLength) << std::fixed << std::setprecision(2) << itemArray[i].retail - itemArray[i].wholesale;

			std::cout << std::endl << std::endl;
		}
		return;

	}
	void displayGoodbye()
	{
		clearScreen(false);

		std::cout << std::left;

		std::cout << R"(
  _______   _                       _                                   __                                  _                 
 |__   __| | |                     | |                                 / _|                                (_)                
    | |    | |__     __ _   _ __   | | __    _   _    ___    _   _    | |_    ___    _ __     _   _   ___   _   _ __     __ _ 
    | |    | '_ \   / _` | | '_ \  | |/ /   | | | |  / _ \  | | | |   |  _|  / _ \  | '__|   | | | | / __| | | | '_ \   / _` |
    | |    | | | | | (_| | | | | | |   <    | |_| | | (_) | | |_| |   | |   | (_) | | |      | |_| | \__ \ | | | | | | | (_| |
    |_|    |_| |_|  \__,_| |_| |_| |_|\_\    \__, |  \___/   \__,_|   |_|    \___/  |_|       \__,_| |___/ |_| |_| |_|  \__, |
                                              __/ |                                                                      __/ |
                                             |___/                                                                      |___/ 
  _____                 _                                    _                              
 |_   _|               | |                                  | |                             
   | |    _ __    ___  | |_    __ _  __   __   ___   _ __   | |_    ___    _ __   _   _     
   | |   | '_ \  / __| | __|  / _` | \ \ / /  / _ \ | '_ \  | __|  / _ \  | '__| | | | |    
  _| |_  | | | | \__ \ | |_  | (_| |  \ V /  |  __/ | | | | | |_  | (_) | | |    | |_| |  _ 
 |_____| |_| |_| |___/  \__|  \__,_|   \_/    \___| |_| |_|  \__|  \___/  |_|     \__, | (_)
                                                                                   __/ |    
                                                                                  |___/     
   ___                      _              _     _             _ 
  / __|  _ _   ___   __ _  | |_   ___   __| |   | |__   _  _  (_)
 | (__  | '_| / -_) / _` | |  _| / -_) / _` |   | '_ \ | || |  _ 
  \___| |_|   \___| \__,_|  \__| \___| \__,_|   |_.__/  \_, | (_)
                                                        |__/     
   ___    _   _         _                  ___   _                  
  / _ \  | | (_) __ __ (_)  ___   _ _     / __| | |_    __ _   _ _  
 | (_) | | | | | \ V / | | / -_) | '_|   | (__  | ' \  / _` | | ' \ 
  \___/  |_| |_|  \_/  |_| \___| |_|      \___| |_||_| \__,_| |_||_|
  _             _           ___                                            
 | |     _  _  (_)  ___    / __|  _  _   ___   _ _   _ _   ___   _ _   ___ 
 | |__  | || | | | (_-<   | (_ | | || | / -_) | '_| | '_| / -_) | '_| / _ \
 |____|  \_,_| |_| /__/    \___|  \_,_| \___| |_|   |_|   \___| |_|   \___/
  _  _   _                        ___          _     _               _ 
 | || | (_)  _ _   ___   _ _     | _ \  __ _  | |_  | |_    ___   __| |
 | __ | | | | '_| / -_) | ' \    |   / / _` | |  _| | ' \  / _ \ / _` |
 |_||_| |_| |_|   \___| |_||_|   |_|_\ \__,_|  \__| |_||_| \___/ \__,_|
 __   __                 ___               
 \ \ / /  _  _   ___    | _ \  __ _   _ _  
  \ V /  | || | / -_)   |  _/ / _` | | ' \ 
   |_|    \_,_| \___|   |_|   \__,_| |_||_|)" << std::endl << std::endl << std::endl;
	}
}
