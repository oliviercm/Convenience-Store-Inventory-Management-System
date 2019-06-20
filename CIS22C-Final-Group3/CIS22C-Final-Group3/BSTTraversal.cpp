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

	const std::string marginString = static_cast<int>(item.getMargin()) <= 0 ? std::string("N/A") : std::to_string(static_cast<int>(item.getMargin())) + "%";

	std::cout << std::setw(6) << item.uid
		<< std::setw(88) << item.name;
	std::cout << std::setw(3) << std::fixed << std::setprecision(2) << marginString;
	std::cout << std::setw(18) << std::fixed << std::setprecision(2) << std::right << "$" << item.retail - item.wholesale << std::left;
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
	const std::string profirMarginText = "PROFIT MARGIN:";
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

void BSTTraversal::postorder(const BST_Node<int, Item>* root, int indent)
{
	if (root == nullptr)
	{
		return;
	}

	if (root->right)
	{
		postorder(root->right, indent + 8);
	}
	std::cout << std::setw(indent) << ' ';
	if (root->right)
	{
		std::cout << "/\n" << std::setw(indent) << ' ';
	}
	std::cout << root->key << "\n ";
	if (root->left)
	{
		std::cout << std::setw(indent) << ' ' << " \\\n";
		postorder(root->left, indent + 8);
	}

	Efficiency::globalBinaryTreeOperations++;
}

void BSTTraversal::postorder(const BST<int, Item>& bst)
{
	postorder(bst.getHead(), 0);
}

void BSTTraversal::postorder(const BST_Node<double, Item>* root, int indent)
{
	if (root == nullptr)
	{
		return;
	}

	if (root->right)
	{
		postorder(root->right, indent + 8);
	}
	std::cout << std::setw(indent) << ' ';
	if (root->right)
	{
		std::cout << "/\n" << std::setw(indent) << ' ';
	}
	std::cout << root->key << "\n ";
	if (root->left)
	{
		std::cout << std::setw(indent) << ' ' << " \\\n";
		postorder(root->left, indent + 8);
	}

	Efficiency::globalBinaryTreeOperations++;
}

void BSTTraversal::postorder(const BST<double, Item>& bst)
{
	postorder(bst.getHead(), 0);
}