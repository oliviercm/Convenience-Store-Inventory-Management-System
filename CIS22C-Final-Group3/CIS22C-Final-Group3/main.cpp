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
#include "UserInput.h"
#include "Array.h"

using namespace std;

int main()
{
	Interface::printHeader();
	
	//std::string filepath = "items.txt";
	//cout << FileIO::fileToString(filepath) << endl;
	
	Array<int> myArray = Array<int>();

	myArray.append(10);
	cout << myArray[0] << endl;

	system("pause");
	return 0;
}