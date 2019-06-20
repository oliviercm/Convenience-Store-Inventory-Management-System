#include <iostream>

#include "BSTTraversal.h"
#include "BST.h"
#include "BST_Node.h"
#include "Item.h"

//Printing out the UID tree
void BSTTraversal::inorder(const BST_Node<int, Item>* root)
{
	if (root == nullptr)
	{
		return;
	}

	inorder(root->left);
	std::cout << root->value << std::endl;
	inorder(root->right);
}

void BSTTraversal::inorder(const BST<int, Item>& bst)
{
	inorder(bst.getHead());
}

//Printing out the profit margin tree
void BSTTraversal::inorder(const BST_Node<double, Item>* root)
{
	if (root == nullptr)
	{
		return;
	}

	inorder(root->left);
	std::cout << "The item " << root->value.uid << " " << root->value.name << " has a profit margin of: " << root->key << std::endl;
	inorder(root->right);
}

void BSTTraversal::inorder(const BST<double, Item>& bst)
{
	inorder(bst.getHead());
}