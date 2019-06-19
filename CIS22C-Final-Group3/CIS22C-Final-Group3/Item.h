/********************************************************************************
************************************ Item ***************************************
*********************************************************************************
* Author: Olivier Chan - 100%
*
* The purpose of this class is to provide a container for item attributes.
*****************
***** USAGE *****
*****************
* At minimum, an Item defined in the data file MUST have a UID and a name. Otherwise,
* the data file will be detected as corrupted and program execution will halt.
* 
* UPCs are not mandatory. This is because some items must be in the system, but
* don't have UPCs (e.g. Mega Millions tickets)
* The same logic applies to size, wholesale, retail, and quantity.
* 
* If an item is defined without a category in the data file, the default category 0
* will be assigned to it.
* 
* Wholesale and retail prices are not checked for negative values. This is because
* there are conceivable situations when a price may be negative.
* 
* The same applies for quantity. The most likely reason this may happen is because
* of theft, or an invoice or inventory report was inaccurate.
*********************************************************************************/

#pragma once

#include <string>

struct Item
{
public:
	int uid;
	std::string upc;
	std::string name;
	std::string size;
	int category;
	double wholesale;
	double retail;
	int quantity;

	Item() = default;
	Item(const Item&) = default;
	virtual ~Item() = default;

	Item(const int&, const std::string&, const std::string&, const std::string&, const int&, const double&, const double&, const int&); //Parameter order follows the same order as the declaration order in this header
	Item(int&&, std::string&&, std::string&&, std::string&&, int&&, double&&, double&&, int&&); //Parameter order follows the same order as the declaration order in this header

	double getMargin() const;
	
	Item& operator=(const Item&) = default;
	

	//Compares equality of all attributes
	bool operator==(const Item&) const;
	bool operator!=(const Item&) const;

	//Compares profit margins (margin = wholesale / retail)
	bool operator<(const Item&) const;
	bool operator<=(const Item&) const;
	bool operator>(const Item&) const;
	bool operator>=(const Item&) const;

	friend std::ostream& operator<<(std::ostream& , const Item&);
};