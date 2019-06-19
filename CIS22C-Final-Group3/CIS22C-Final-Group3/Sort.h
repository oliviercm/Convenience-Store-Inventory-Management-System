/********************************************************************************
************************************ Sort ***************************************
*********************************************************************************
* Author: Olivier Chan - 100%
*
* This function is used to merge sort an Array of Items by UID.
*****************
***** USAGE *****
*****************
* Pass the Array to sort into mergeSortItemArray()
* 
* Warning: This function edits the passed Array!
* In order to prevent invalidating references to any data stored in the master array,
* pass a copy of the array to sort!
*********************************************************************************/

#pragma once

#include "Array.h"
#include "Item.h"

namespace Sort
{
	void mergeSortItemArray(Array<Item>&);
}