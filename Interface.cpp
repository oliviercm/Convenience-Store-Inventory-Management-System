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
		const std::string findDataRecordText = "[ 3 ] FIND DATA RECORD";
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
			<< std::setw(optionMargin + findDataRecordText.length()) << findDataRecordText << std::endl << std::endl
			<< std::setw(optionMargin + listDataHashText.length()) << listDataHashText << std::endl << std::endl
			<< std::setw(optionMargin + listDataKeyText.length()) << listDataKeyText << std::endl << std::endl
			<< std::setw(optionMargin + printTreeText.length()) << printTreeText << std::endl << std::endl
			<< std::setw(optionMargin + efficiencyText.length()) << efficiencyText << std::endl << std::endl
			<< std::setw(optionMargin + teamOptionText.length()) << teamOptionText << std::endl << std::endl
			<< std::setw(optionMargin + quitText.length()) << quitText << std::endl << std::endl
			<< bars << std::endl << std::endl;

		return;

	}
	void displayInventory()
	{
	}
	Item addNewItem(const List<Item>& itemList)
	{
		int newUid, newCategory, newQuantity, inputAgain;
		std::string newUpc, newName, newSize;
		double newWholeSale, newRetail;

		Interface::clearScreen(true);

		const std::string bars = generateBars(TERMINAL_WIDTH);
		const std::string titleText = "[ ADD NEW DATA ]";

		const size_t titleMargin = (TERMINAL_WIDTH + titleText.length()) / 2;
		std::cout << std::setw(titleMargin) << titleText << std::endl << std::endl << bars << std::endl << std::endl;

		std::cout << "Enter the 4-digit UID of the item" << std::endl;
		newUid = Input::getInt(1, 5999);
		std::string temp = std::to_string(newUid);
		while (temp.length() != 4)
		{
			std::cout << "ERROR: UID must be a 4-digits long, try again:" << std::endl;
			newUid = Input::getInt(1, 5999);
			temp = std::to_string(newUid);
		}

		std::cout << "Enter the UPC of the item" << std::endl;
		newUpc = Input::getString();
		while (newUpc.length() != 13)
		{
			std::cout << "ERROR: UPC must be 13-digits long, try again:" << std::endl;
			newUpc = Input::getString();
		}

		std::cout << "Enter the name of the item" << std::endl;
		newName = Input::getString();

		std::cout << "Enter the size of the item" << std::endl;
		newSize = Input::getString();

		std::cout << "Enter the category of the item" << std::endl;
		newCategory = Input::getInt(1, 6);

		std::cout << "Enter the whole-sale of the item" << std::endl;
		newWholeSale = Input::getDouble(0.0, 100000.0);

		std::cout << "Enter the retail price of the item" << std::endl;
		newRetail = Input::getDouble(0.0, 100000.0);

		std::cout << "Enter the quantity of the tem" << std::endl;
		newQuantity = Input::getInt(1, 1000);

		Item newItem(newUid, newUpc, newName, newSize, newCategory, newWholeSale, newRetail, newQuantity);

		return newItem;
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