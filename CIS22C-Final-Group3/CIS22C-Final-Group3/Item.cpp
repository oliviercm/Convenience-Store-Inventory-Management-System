#include "Item.h"

Item::Item()
{

}

Item::~Item()
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
	os << "CATEGORY:  " << item.category << std::endl;
	os << "WHOLESALE: " << item.wholesale << std::endl;
	os << "RETAIL:    " << item.retail << std::endl;
	os << "QUANTITY:  " << item.quantity << std::endl;

	return os;
}