#include "Interface.h"
#include "Input.h"
#include "Item.h"

#include <iostream>
#include <iomanip>
#include <string>

namespace Interface
{
	namespace
	{
		const std::string BARS_CHARACTER = "=";
		const int TERMINAL_WIDTH = 120;
		const int TERMINAL_HEIGHT = 60;

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
		const std::string addNewDataText = "[ 1 ] ADD NEW DATA";
		const std::string deleteDataText = "[ 2 ] DELETE DATA";
		const std::string searchText = "[ 3 ] SEARCH";
		const std::string listDataHashText = "[ 4 ] LIST DATA IN HASH TABLE SEQUENCE";
		const std::string listDataKeyText = "[ 5 ] LIST DATA IN KEY SEQUENCE";
		const std::string printTreeText = "[ 6 ] PRINT TREE";
		const std::string efficiencyText = "[ 7 ] EFFICIENCY";
		const std::string teamOptionText = "[ 8 ] MARGINS AND PROFITABILITY";
		const std::string quitText = "[ 9 ] QUIT";

		
		const size_t titleMargin = (TERMINAL_WIDTH + mainMenuText.length()) / 2;
		const size_t optionMargin = titleMargin - mainMenuText.length();

		std::cout << std::right;

		std::cout << std::setw(titleMargin) << mainMenuText << std::endl << std::endl << bars << std::endl << std::endl;

		std::cout << std::setw(optionMargin + addNewDataText.length()) << addNewDataText << std::endl << std::endl
			<< std::setw(optionMargin + deleteDataText.length()) << deleteDataText << std::endl << std::endl
			<< std::setw(optionMargin + searchText.length()) << searchText << std::endl << std::endl
			<< std::setw(optionMargin + listDataHashText.length()) << listDataHashText << std::endl << std::endl
			<< std::setw(optionMargin + listDataKeyText.length()) << listDataKeyText << std::endl << std::endl
			<< std::setw(optionMargin + printTreeText.length()) << printTreeText << std::endl << std::endl
			<< std::setw(optionMargin + efficiencyText.length()) << efficiencyText << std::endl << std::endl
			<< std::setw(optionMargin + teamOptionText.length()) << teamOptionText << std::endl << std::endl
			<< std::setw(optionMargin + quitText.length()) << quitText << std::endl << std::endl
			<< bars << std::endl << std::endl;

		return;

	}
	void displayInventory(List<Item>& itemList)
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

		//std::cout << std::endl << std::endl;

		std::cout << std::setw(uidColumnLength) << uidText
			<< std::setw(upcColumnLength) << upcText
			<< std::setw(nameColumnLength) << nameText
			<< std::setw(sizeColumnLength) << sizeText
			<< std::setw(categoryColumnLength) << categoryText
			<< std::setw(wholesaleColumnLength) << wholesaleText
			<< std::setw(retailColumnLength) << retailText
			<< std::setw(quantityColumnLength) << quantityText
			<< std::endl << std::endl;

		for (int i = 0; i < itemList.getCount(); i++)
		{

			std::cout << std::setw(uidColumnLength) << itemList[i].uid
				<< std::setw(upcColumnLength) << itemList[i].upc
				<< std::setw(nameColumnLength) << itemList[i].name.substr(0, 30)
				<< std::setw(sizeColumnLength) << itemList[i].size
				<< std::setw(categoryColumnLength) << itemList[i].category
				<< std::setw(wholesaleColumnLength) << itemList[i].wholesale
				<< std::setw(retailColumnLength) << itemList[i].retail
				<< std::setw(quantityColumnLength) << itemList[i].quantity;

			std::cout << std::endl << std::endl;
		}

	}
	void addNewItem(List<Item>& itemList)
	{
		int newUid, newCategory, newQuantity;
		std::string newUpc, newName, newSize;
		double newWholeSale, newRetail;
		bool found = false;

		Interface::clearScreen(true);

		const std::string bars = generateBars(TERMINAL_WIDTH);
		const std::string titleText = "[ ADD NEW DATA ]";

		const size_t titleMargin = (TERMINAL_WIDTH + titleText.length()) / 2;
		std::cout << std::setw(titleMargin) << titleText << std::endl << std::endl << bars << std::endl << std::endl;

		std::cout << "Enter the 4-digit UID of the item" << std::endl;
		newUid = Input::getInt(1, 5999);
		std::cout << std::endl;
		std::string temp = std::to_string(newUid);
		while (temp.length() != 4)
		{
			std::cout << "ERROR: UID must be a 4-digits long, try again:" << std::endl;
			newUid = Input::getInt(1, 5999);
			std::cout << std::endl;
			temp = std::to_string(newUid);
		}
		for (int i = 0; i < itemList.getCount(); i++)
		{
			while (itemList[i].uid == newUid)
			{
				std::cout << "ERROR: The UID you enter already exists, try another UID:" << std::endl;
				newUid = Input::getInt(1, 5999);
				std::cout << std::endl;
			}
		}
		std::cout << "Enter the UPC of the item" << std::endl;
		newUpc = Input::getString();
		std::cout << std::endl;
		while (newUpc.length() < 12)
		{
			std::cout << "ERROR: UPC must be 13-digits long, try again:" << std::endl;
			newUpc = Input::getString();
			std::cout << std::endl;
		}

		for (int i = 0; i < itemList.getCount(); i++)
		{
			while (itemList[i].upc == newUpc)
			{
				std::cout << "ERROR: The UPC you enter already exists, try another UPC:" << std::endl;
				newUpc = Input::getString();
				std::cout << std::endl;
			}
		}
		std::cout << "Enter the name of the item" << std::endl;
		newName = Input::getString();
		std::cout << std::endl;
		for (int i = 0; i < itemList.getCount(); i++)
		{
			while (itemList[i].name == newName)
			{
				std::cout << "ERROR: The name you enter already exists, try another name:" << std::endl;
				newName = Input::getString();
				std::cout << std::endl;
			}
		}

		std::cout << "Enter the size of the item" << std::endl;
		newSize = Input::getString();
		std::cout << std::endl;

		std::cout << "Enter the category of the item" << std::endl;
		newCategory = Input::getInt(1, 6);
		std::cout << std::endl;

		std::cout << "Enter the whole-sale of the item" << std::endl;
		newWholeSale = Input::getDouble(0.0, 100000.0);
		std::cout << std::endl;

		std::cout << "Enter the retail price of the item" << std::endl;
		newRetail = Input::getDouble(0.0, 100000.0);
		std::cout << std::endl;

		std::cout << "Enter the quantity of the tem" << std::endl;
		newQuantity = Input::getInt(1, 1000);
		std::cout << std::endl;

		Item newItem(newUid, newUpc, newName, newSize, newCategory, newWholeSale, newRetail, newQuantity);

		itemList.insertLast(newItem);

		return;
	}
	void displayDeleteMenu()
	{
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
	void deleteByUid(List<Item>& itemList)
	{
		int intItemToDelete, i = 0, positionOfItem = 0;
		bool found = false;
		Interface::clearScreen(true);
		std::cout << "Enter the UID of the item you want to delete:" << std::endl;
		intItemToDelete = Input::getInt(1, 5999);
		for (i = 0; i < itemList.getCount(); i++)
		{
			if (itemList[i].uid == intItemToDelete)
			{
				positionOfItem = i;
				found = true;
				break;
			}
		}
		if (found == true)
		{
			itemList.remove(positionOfItem);
		}
		else
		{
			std::cout << "ERROR: The UID you entered does not exists" << std::endl;
		}
		pause();

		return;
	}
	void deleteByName(List<Item>& itemList)
	{
		int i = 0, positionOfItem = 0;
		std::string strItemToDelete;
		bool found = false;
		Interface::clearScreen(true);
		std::cout << "Enter the name of the item you want to delete:" << std::endl;
		strItemToDelete = Input::getString();
		for (i = 0; i < itemList.getCount(); i++)
		{
			if (itemList[i].name == strItemToDelete)
			{
				positionOfItem = i;
				found = true;
				break;
			}
		}
		if (found == true)
		{
			itemList.remove(positionOfItem);
		}
		else
		{
			std::cout << "ERROR: The name you entered does not exists" << std::endl;
		}
		pause();

		return;
	}
	void deleteByUpc(List<Item>& itemList)
	{
		int i = 0, positionOfItem = 0;
		std::string strItemToDelete;
		bool found = false;
		Interface::clearScreen(true);
		std::cout << "Enter the UPC of the item you want to delete:" << std::endl;
		strItemToDelete = Input::getString();
		for (i = 0; i < itemList.getCount(); i++)
		{
			if (itemList[i].upc == strItemToDelete)
			{
				positionOfItem = i;
				found = true;
				break;
			}
		}
		if (found == true)
		{
			itemList.remove(positionOfItem);
		}
		else
		{
			std::cout << "ERROR: The UPC you entered does not exists" << std::endl;
		}
		pause();

		return;
	}
	void displaSearchMenu()
	{
		const std::string bars = generateBars(TERMINAL_WIDTH);
		const std::string sortText = "[ SORT ]";
		const std::string byNameText = "[ 1 ] BY NAME";
		const std::string byRetailText = "[ 2 ] BY UPC";
		//const std::string byQuantityText = "[ 3 ] BY QUANTITY";
		const std::string backtext = "[ 3 ] BACK";

		const size_t titleMargin = (TERMINAL_WIDTH + sortText.length()) / 2;
		const size_t optionMargin = titleMargin - sortText.length();

		std::cout << std::right;

		std::cout << std::setw(titleMargin) << sortText << std::endl << std::endl << bars << std::endl << std::endl;

		std::cout << std::setw(optionMargin + byNameText.length()) << byNameText << std::endl << std::endl
			<< std::setw(optionMargin + byRetailText.length()) << byRetailText << std::endl << std::endl
			<< std::setw(optionMargin + backtext.length()) << backtext << std::endl << std::endl
			<< bars << std::endl << std::endl;

		return;
	}
	Item searchByName(List<Item>& itemList, AVLTree<std::string>& avlTree)
	{
		Interface::clearScreen(true);

		std::string itemToSearch;
		Item itemFound;
		bool found = false;

		std::cout << "Enter the name of the item you want to search:" << std::endl;
		itemToSearch = Input::getString();

		for (int i = 0; i < avlTree.get_nodes_num_avl(); i++)
		{
			if (avlTree.search_avl(itemToSearch) == true)
			{
				itemFound = itemList[i];
				found = true;
			}
		}

		if (found = true)
		{
			return itemFound;
		}
	}
	void displayTypeTrees()
	{
		const std::string bars = generateBars(TERMINAL_WIDTH);
		const std::string typeTreesText = "[ TYPE OF TREES ]";
		const std::string bstText = "[ 1 ] BINARY SEARCH TREE";
		const std::string avlTreeText = "[ 2 ] AVL Tree";
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
}