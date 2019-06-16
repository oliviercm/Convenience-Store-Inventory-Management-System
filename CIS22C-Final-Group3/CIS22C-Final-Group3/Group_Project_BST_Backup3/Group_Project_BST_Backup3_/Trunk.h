#pragma once
#ifndef TRUNK_H
#define TRUNK_H

#include <string>

struct Trunk
{
	Trunk * prev;
	std::string str;

	Trunk(Trunk * i_prev, std::string i_str)
	{
		prev = i_prev;
		str = i_str;
	}
};

#endif