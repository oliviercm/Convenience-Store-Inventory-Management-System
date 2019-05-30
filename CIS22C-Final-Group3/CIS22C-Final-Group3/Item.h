/********************************************************************************
************************************ Item ***************************************
*********************************************************************************
* WIP
* The purpose of this class is to provide a container for item attributes.
*****************
***** USAGE *****
*****************
* WIP
*********************************************************************************/

#pragma once

#include <string>

struct Item
{
private:
public:
	int uid;
	//Array& attributes;

	Item();
	~Item();

	Item& operator=(const Item&);

	friend std::ostream& operator<<(std::ostream& , const Item&);
};