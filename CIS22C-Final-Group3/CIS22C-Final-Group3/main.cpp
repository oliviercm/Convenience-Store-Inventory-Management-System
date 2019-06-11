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

	Interface::pause();
	return 0;
}