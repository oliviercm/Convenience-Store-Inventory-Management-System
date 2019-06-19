#include "FileIO.h"

#include <fstream>

namespace FileIO
{
	namespace
	{
		const std::string DELIM_ITEM = "item";
		const std::string DELIM_UID = "UID";
		const std::string DELIM_UPC = "UPC";
		const std::string DELIM_NAME = "name";
		const std::string DELIM_SIZE = "size";
		const std::string DELIM_CATEGORY = "category";
		const std::string DELIM_WHOLESALE = "wholesale";
		const std::string DELIM_RETAIL = "retail";
		const std::string DELIM_QUANTITY = "quantity";
		
		/**
		* @author Olivier Chan
		*
		* @brief Returns a substring of the passed string starting at the (skip + 1)th instance of "<delimiter>" and ending after the subsequent instance of "</delimiter>".
		*	The angle brackets and delimiters are removed from the substring.
		*	If skip is greater than the number of delimiters in the string, an empty string is returned.
		*
		* @detail Example: parseString("<txt>Foo</txt> <txt>Bar</txt>", "txt", 0) will return "Foo".
		*
		* @param str The string to parse. The string should contain "<delimiter>" and "</delimiter>" tags.
		*
		* @param delimiter The string to act as a delimiter. This function adds angle brackets around the delimiter, so they should not be included in the passed delimiter.
		*
		* @param skip The number of times to skip an instance of the delimiter.
		*
		* @return A substring of the passed string starting at the (skip + 1)th instance of "<delimiter>" and ending after the subsequent instance of "</delimiter>".
		*	The angle brackets and delimiters are removed from the substring.
		*	If skip is greater than the number of delimiters in the string, an empty string is returned.
		*/
		std::string parseString(const std::string& str, const std::string& delimiter, const int skip)
		{
			const std::string delimitBeg = "<" + delimiter + ">";
			const std::string delimitEnd = "</" + delimiter + ">";

			//Set the starting position to after the (skip)th delimiter
			size_t startingPos = 0;
			for (int i = 0; i < skip; i++)
			{
				const size_t delimiterPos = str.find(delimitEnd, startingPos);
				if (delimiterPos != std::string::npos)
				{
					startingPos = str.find(delimitEnd, startingPos) + delimitEnd.length();
				}
				else
				{
					//The starting position is after the last delimiter, return an empty string
					throw std::invalid_argument("Passed end of string.");
				}
			}

			//From the starting position, find the positions of the first instances of the beginning and ending delimiters
			const size_t delimitBegPos = str.find(delimitBeg, startingPos);
			const size_t delimitEndPos = str.find(delimitEnd, startingPos);

			//Return the substring between the beginning and ending delimiters
			return str.substr(delimitBegPos + delimitBeg.length(), delimitEndPos - delimitBegPos - delimitBeg.length());
		}
		std::string parseString(const std::string& str, const std::string& delimiter)
		{
			const std::string delimitBeg = "<" + delimiter + ">";
			const std::string delimitEnd = "</" + delimiter + ">";

			//Find the positions of the first instances of the beginning and ending delimiters
			const size_t delimitBegPos = str.find(delimitBeg);
			const size_t delimitEndPos = str.find(delimitEnd);

			if (delimitBegPos != std::string::npos)
			{
				return str.substr(delimitBegPos + delimitBeg.length(), delimitEndPos - delimitBegPos - delimitBeg.length());
			}
			else
			{
				//The delimiter doesn't exist in the string, return an empty string
				return std::string();
			}
		}
		/**
		* @author Olivier Chan
		*
		* @brief Returns the contents of the file located at path as a string. If the file at path doesn't exist, returns an empty string.
		*
		* @param path The path of the file to convert contents to a string.
		*
		* @return The contents of the file from path as a string. If the file at path doesn't exist, returns an empty string.
		*/
		std::string fileToString(const std::string& path)
		{
			std::ifstream in(path, std::ios::ate);

			if (in)
			{
				std::string str;

				//Reserve space in the string to store the entire file, not strictly required
				str.reserve(static_cast<size_t>(in.tellg()));
				in.seekg(0, std::ios::beg);

				//Store the entire file in the string by iterating from beginning to end
				str.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

				return str;
			}
			else
			{
				//If the file doesn't exist or isn't openable, throw an exception
				throw std::invalid_argument("ERROR: File doesn't exist or is unopenable.");
			}
		}
		/**
		* getNumBooksInString
		*
		* @brief Returns the number of books in the string based on the book delimiter.
		*
		* @param str The string to search for books. In almost every case this should be the inventory string.
		*
		* @return Number of books in the string.
		*/
		int getNumItemsInString(const std::string& str)
		{
			int count = 0;
			size_t pos = 0;
			const std::string delimiter = "<" + DELIM_ITEM + ">";

			pos = str.find(delimiter, pos);
			while (pos != std::string::npos)
			{
				count++;
				pos = str.find(delimiter, pos + delimiter.length());
			}

			return count;
		}
		/**
		* @brief Turns an item into a string, formatted into the form used in the inventory file.
		*
		* @param item The item to turn into a string.
		*
		* @return The item as a database formatted string.
		*/
		std::string itemToString(const Item& item)
		{
			std::string wholesaleString = std::to_string(item.wholesale);
			wholesaleString = wholesaleString.substr(0, wholesaleString.find('.') + 3);

			std::string retailString = std::to_string(item.retail);
			retailString = retailString.substr(0, retailString.find('.') + 3);

			std::string itemString =
				"<" + DELIM_ITEM + ">" + "\n"
				+ "\t" + "<" + DELIM_UID + ">" + std::to_string(item.uid) + "</" + DELIM_UID + ">" + "\n"
				+ "\t" + "<" + DELIM_UPC + ">" + item.upc + "</" + DELIM_UPC + ">" + "\n"
				+ "\t" + "<" + DELIM_NAME + ">" + item.name + "</" + DELIM_NAME + ">" + "\n"
				+ "\t" + "<" + DELIM_SIZE + ">" + item.size + "</" + DELIM_SIZE + ">" + "\n"
				+ "\t" + "<" + DELIM_CATEGORY + ">" + std::to_string(item.category) + "</" + DELIM_CATEGORY + ">" + "\n"
				+ "\t" + "<" + DELIM_WHOLESALE + ">" + wholesaleString + "</" + DELIM_WHOLESALE + ">" + "\n"
				+ "\t" + "<" + DELIM_RETAIL + ">" + retailString + "</" + DELIM_RETAIL + ">" + "\n"
				+ "\t" + "<" + DELIM_QUANTITY + ">" + std::to_string(item.quantity) + "</" + DELIM_QUANTITY + ">" "\n"
				"</" + DELIM_ITEM + ">" + "\n";

			return itemString;
		}
	}
	
	void loadFileIntoArray(Array<Item>& arr, const std::string& filePath)
	{
		if (arr.getSize() > 0)
		{
			throw std::invalid_argument("ERROR: Array is not empty.");
		}

		const std::string itemsString = fileToString(filePath);
		const int numItems = getNumItemsInString(itemsString);

		for (int i = 0; i < numItems; i++)
		{
			const std::string itemString = parseString(itemsString, DELIM_ITEM, i);
			int uid;
			std::string upc;
			std::string name;
			std::string size;
			int category;
			double wholesale;
			double retail;
			int quantity;

			//UID - must be validated
			const std::string uidString = parseString(itemString, DELIM_UID);
			if (uidString.empty())
			{
				throw std::runtime_error("ERROR: Database file corrupted - UID missing.");
			}
			else
			{
				try
				{
					uid = std::stoi(uidString);
				}
				catch (...)
				{
					throw std::runtime_error("ERROR: Database file corrupted - UID corrupted.");
				}
			}
			//UPC
			upc = parseString(itemString, DELIM_UPC);
			//Name
			name = parseString(itemString, DELIM_NAME);
			//Size
			size = parseString(itemString, DELIM_SIZE);
			//Category
			const std::string categoryString = parseString(itemString, DELIM_CATEGORY);
			if (categoryString.empty())
			{
				category = 0;
			}
			else
			{
				try
				{
					category = std::stoi(categoryString);
				}
				catch (...)
				{
					throw std::runtime_error("ERROR: Database file corrupted - Category corrupted.");
				}
			}
			//Wholesale
			const std::string wholesaleString = parseString(itemString, DELIM_WHOLESALE);
			if (wholesaleString.empty())
			{
				wholesale = 0;
			}
			else
			{
				try
				{
					wholesale = std::stod(wholesaleString);
				}
				catch (...)
				{
					throw std::runtime_error("ERROR: Database file corrupted - Wholesale price corrupted.");
				}
			}
			//Retail
			const std::string retailString = parseString(itemString, DELIM_RETAIL);
			if (retailString.empty())
			{
				retail = 0;
			}
			else
			{
				try
				{
					retail = std::stod(retailString);
				}
				catch (...)
				{
					throw std::runtime_error("ERROR: Database file corrupted - Retail price corrupted.");
				}
			}
			//Quantity
			const std::string quantityString = parseString(itemString, DELIM_QUANTITY);
			if (quantityString.empty())
			{
				quantity = 0;
			}
			else
			{
				try
				{
					quantity = std::stoi(quantityString);
				}
				catch (...)
				{
					throw std::runtime_error("ERROR: Database file corrupted - Quantity corrupted.");
				}
			}

			arr.append(Item(std::move(uid), std::move(upc), std::move(name), std::move(size), std::move(category), std::move(wholesale), std::move(retail), std::move(quantity)));
		}
	}
	void saveListIntoFile(List<Item>& list, const std::string& filePath)
	{
		std::string itemsString = std::string();

		for (int i = 0; i < list.getCount(); i++)
		{
			itemsString.append(itemToString(list[i]));
		}

		std::ofstream os;

		os.open(filePath);

		os << itemsString;

		os.close();
	}
}