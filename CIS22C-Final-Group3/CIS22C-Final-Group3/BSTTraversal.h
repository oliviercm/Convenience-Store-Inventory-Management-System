/********************************************************************************
******************************** BSTTraversal ***********************************
*********************************************************************************
* Author: Olivier Chan - 100%
*
* The purpose of this class is to print out specialized BSTs for user interface.
*****************
***** USAGE *****
*****************
* Pass the correct type of BST into inorder()
*********************************************************************************/

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