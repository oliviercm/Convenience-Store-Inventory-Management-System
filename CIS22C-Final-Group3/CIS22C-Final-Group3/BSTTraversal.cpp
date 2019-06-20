#include <iostream>
#include <iomanip>

#include "BSTTraversal.h"
#include "BST.h"
#include "BST_Node.h"
#include "Item.h"

#include "Interface.h"
#include "Efficiency.h"

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

	Efficiency::globalBinaryTreeOperations++;
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
	Item& item = root->value;
	//Print out each item
	std::cout << std::setw(6) << item.uid
		<< std::setw(88) << item.name;
	std::cout << std::setw(20) << std::fixed << std::setprecision(2) << item.getMargin();
	std::cout << std::setw(10) << std::fixed << std::setprecision(2) << item.retail - item.wholesale;
	std::cout << std::endl << std::endl;
	inorder(root->right);

	Efficiency::globalBinaryTreeOperations++;
}

void BSTTraversal::inorder(const BST<double, Item>& bst)
{
	Interface::clearScreen();
	
	const std::string bars = Interface::generateBars(Interface::TERMINAL_WIDTH);
	const std::string typeTreesText = "[ MARGINS AND PROFITS ]";
	const std::string uidText = "UID:";
	const std::string nameText = "NAME:";
	const std::string profirMarginText = "PROFIT MARGIN:(%)";
	const std::string profitText = "PROFIT:";

	const size_t columnSpacing = 3;
	const size_t uidColumnLength = 3 + columnSpacing;
	const size_t profitMarginColumnLength = profirMarginText.length() + columnSpacing + 5;
	const size_t profitColumnLength = profitText.length() + columnSpacing;

	const size_t titleMargin = (Interface::TERMINAL_WIDTH + typeTreesText.length()) / 2;
	const size_t nameColumnLength = ((Interface::TERMINAL_WIDTH - uidColumnLength - profitMarginColumnLength - profitColumnLength) / 2) + 23;

	std::cout << std::right;

	std::cout << std::setw(titleMargin) << typeTreesText << std::endl << std::endl << bars << std::endl << std::endl;

	std::cout << std::left;

	std::cout << std::setw(uidColumnLength) << uidText
		<< std::setw(nameColumnLength) << nameText
		<< std::setw(profitMarginColumnLength) << profirMarginText
		<< std::setw(profitColumnLength) << profitText
		<< std::endl << std::endl;
	
	inorder(bst.getHead());
}