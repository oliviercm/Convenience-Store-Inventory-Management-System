#pragma once
#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node
{
	T value;
	struct Node * next;
};

#endif