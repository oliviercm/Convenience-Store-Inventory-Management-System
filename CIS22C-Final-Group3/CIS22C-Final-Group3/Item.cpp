#include "Item.h"

Item::Item(const int& ui, const std::string& up, const std::string& na, const std::string& si, const int& ca, const double& wh, const double& re, const int& qu)
	: uid(ui), upc(up), name(na), size(si), category(ca), wholesale(wh), retail(re), quantity(qu)
{
	
}
Item::Item(int&& ui, std::string&& up, std::string&& na, std::string&& si, int&& ca, double&& wh, double&& re, int&& qu)
	: uid(ui), upc(up), name(na), size(si), category(ca), wholesale(wh), retail(re), quantity(qu)
{

}

Item& Item::operator=(const Item& item)
{
	uid = item.uid;
	name = item.name;
	size = item.size;
	category = item.category;
	wholesale = item.wholesale;
	retail = item.retail;
	quantity = item.quantity;

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Item& item)
{
	os << "UID:       " << item.uid << std::endl;
	os << "NAME:      " << item.name << std::endl;
	os << "SIZE:      " << item.size << std::endl;
	if (item.category == 1)
	{
		os << "CATEGORY:  " << "snack" << std::endl;
	}
	else if (item.category == 2)
	{
		os << "CATEGORY:  " << "drink" << std::endl;
	}
	else if (item.category == 3)
	{
		os << "CATEGORY:  " << "tobacco" << std::endl;
	}
	else if (item.category == 4)
	{
		os << "CATEGORY:  " << "lotto" << std::endl;
	}
	else if (item.category == 5)
	{
		os << "CATEGORY:  " << "misc" << std::endl;
	}
	os << "WHOLESALE: " << item.wholesale << std::endl;
	os << "RETAIL:    " << item.retail << std::endl;
	os << "QUANTITY:  " << item.quantity << std::endl;

	return os;
}