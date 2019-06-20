#pragma once

#include "BST.h"
#include "BST_Node.h"
#include "Item.h"

class BSTTraversal
{
private:
	static void inorder(const BST_Node<int, Item>* root);
	static void inorder(const BST_Node<double, Item>* root);
public:
	static void inorder(const BST<int, Item>& bst);
	static void inorder(const BST<double, Item>& bst);
};