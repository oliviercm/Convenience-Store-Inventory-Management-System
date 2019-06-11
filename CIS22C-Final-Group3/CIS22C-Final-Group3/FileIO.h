/********************************************************************************
*********************************** FileIO **************************************
*********************************************************************************
* Author: Olivier Chan - 100%
*
* The purpose of these functions are to handle saving and loading data from files.
*****************
***** USAGE *****
*****************
* WIP
*********************************************************************************/

#pragma once

#include <string>
#include "Item.h"
#include "List.h"

namespace FileIO
{
	/**
	* @author Olivier Chan
	*
	* @brief Populates the passed empty List with all Items that can be loaded from the given file path.
	*
	* @pre list must be empty. filePath must point to a file that is correctly formatted following the documentation.
	* @post list will contain all Item objects that could be constructed from the file.
	*
	* @param list The List to populate.
	* @param filePath The filepath of the file containing the Item data.
	*/
	void loadFileIntoList(List<Item>& list, const std::string& filePath);
	/**
	* @author Olivier Chan
	*
	* @brief Serializes the list of items into a file at the given filepath.
	*
	* @pre list should contain any number of Items. filePath should point to the current data file location.
	* @post The file at filePath will be overwritten to contain the contents of list, serialized into database format following documentation.
	*
	* @param list The List to serialize.
	* @param filePath The filepath of the file to save the serialized data.
	*/
	void saveListIntoFile(List<Item>& list, const std::string& filePath);
};