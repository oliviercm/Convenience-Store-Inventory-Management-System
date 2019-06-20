/********************************************************************************
******************************** BSTTraversal ***********************************
*********************************************************************************
* Author: Olivier Chan - 100%
*
* The purpose of this class is to print out specialized BSTs for user interface.
* The method of printing is specialized - each function should only be used
* for its intended purpose.
*****************
***** USAGE *****
*****************
* Pass the correct type of BST into the functions.
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
	static void postorder(const BST_Node<int, Item>* root, int);
	static void postorder(const BST_Node<double, Item>* root, int);
public:
	static void inorder(const BST<int, Item>& bst);
	static void inorder(const BST<double, Item>& bst);
	static void postorder(const BST<int, Item>& bst);
	static void postorder(const BST<double, Item>& bst);
};