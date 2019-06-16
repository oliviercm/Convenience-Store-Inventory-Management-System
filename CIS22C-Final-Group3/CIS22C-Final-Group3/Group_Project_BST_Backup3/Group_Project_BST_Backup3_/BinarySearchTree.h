#pragma once
#ifndef BINARYSEARCHTREE
#define BINARYSEARCHTREE

#include <iostream>
#include <iomanip>

#include "BinaryTreeNode.h"
#include "Stack.h"
#include "Trunk.h"

template <typename T>
class BinarySearchTree
{
protected:
	BinaryTreeNode<T> * root_ptr;
	int nodes_num;

	void add_r(BinaryTreeNode<T> *, BinaryTreeNode<T> *);
	int max(int, int);
	int get_height_r(BinaryTreeNode<T> *);
	bool search_r(BinaryTreeNode<T> *, BinaryTreeNode<T> *);
	void preorder_traverse_r(BinaryTreeNode<T> *, void visit(T &));
	void inorder_traverse_r(BinaryTreeNode<T> *, void visit(T &));
	void postorder_traverse_r(BinaryTreeNode<T> *, void visit(T &));
	void breath_first_traverse_r(BinaryTreeNode<T> *, void visit(T &));
	void clear_r(BinaryTreeNode<T> *);
	BinaryTreeNode<T> * remove_addr_r(BinaryTreeNode<T> *, BinaryTreeNode<T> *, const T &);
	BinaryTreeNode<T> * leftmost_leaf_parent(BinaryTreeNode<T> *);
	void show_trunks(Trunk *);
	void print_tree_r(BinaryTreeNode<T> *, Trunk *, bool);
public:
	BinarySearchTree();

	virtual ~BinarySearchTree();

	BinaryTreeNode<T> * get_root_add();
	void add(const T &);
	bool remove(const T &);
	/*
	Task: Tests whether this binary tree is empty.
	Pre: None.
	Post: True if the binary tree is empty; otherwise false.
	*/
	bool isEmpty();
	/*
	Task: Gets the height of this binary tree.
	Pre: None.
	Post: The height of the binary tree.
	*/
	int get_height();
	/*
	Task: Gets the number of nodes in this binary tree.
	Pre: None.
	Post: The number of nodes in the binary tree.
	*/
	int get_nodes_num();
	/*
	Task:Gets the data that is in the root of this binary tree.
	Pre: None. Assume the tree is not empty.
	Post: The root's data.
	*/
	BinaryTreeNode<T> get_root_data();
	/*
	Task: Removes all nodes from this binary tree.
	Pre: None.
	Post: None.(The binary Tree is empty.)
	*/
	void clear();
	/*
	Tasks: Tests whether the given data item occurs in this binary tree.
	Pre: data is the data item.
	Post: True if the binary tree contains the given data item, or false if not.
	*/
	bool search(const T & i_item);
	/*
	Task: Traverses this binary tree in prorder and calls the function visit once for each node.
	Pre: visit is a client-defined funcction that performs an operation on or with the data in each visited node.
	Post: None.
	*/
	void preorder_traverse(void visit(T &));
	/*
	Task: Traverses this binary tree in inorder and calls the function visit once for each node.
	Pre: visit is a client-defined funcction that performs an operation on or with the data in each visited node.
	Post: None.
	*/
	void inorder_traverse(void visit(T &));
	/*
	Task: Traverses this binary tree in postorder and calls the function visit once for each node.
	Pre: visit is a client-defined funcction that performs an operation on or with the data in each visited node.
	Post: None.
	*/
	void postorder_traverse(void visit(T &));
	/*
	Task: Traverses this binary tree in breath-first order and calls the function visit once for each node.
	Pre: visit is a client-defined funcction that performs an operation on or with the data in each visited node.
	Post: None.
	*/
	void breath_first_traverse(void visit(T &));

	void print_tree();
};

template <typename T>
BinaryTreeNode<T> * BinarySearchTree<T>::get_root_add()
{
	return root_ptr;
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree()
{
	root_ptr = nullptr;
	nodes_num = 0;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	clear();
}

template <typename T>
void BinarySearchTree<T>::add_r(BinaryTreeNode<T> * r_ptr, BinaryTreeNode<T> * i_ptr)
{
	if (r_ptr == nullptr)
	{
		this->root_ptr = i_ptr;
		return;
	}
	else if (r_ptr->datum > i_ptr->datum)
	{
		if (r_ptr->left_ptr == nullptr)
		{
			r_ptr->left_ptr = i_ptr;
			return;
		}
		else
		{
			r_ptr = r_ptr->left_ptr;
			add_r(r_ptr, i_ptr);
		}
	}
	else
	{
		if (r_ptr->right_ptr == nullptr)
		{
			r_ptr->right_ptr = i_ptr;
			return;
		}
		else
		{
			r_ptr = r_ptr->right_ptr;
			add_r(r_ptr, i_ptr);
		}
	}
}

template <typename T>
void BinarySearchTree<T>::add(const T & i_item)
{
	BinaryTreeNode<T> * new_ptr = new BinaryTreeNode<T>(i_item);
	add_r(root_ptr, new_ptr);
	nodes_num += 1;
	new_ptr = nullptr;
}

template <typename T>
BinaryTreeNode<T> * BinarySearchTree<T>::remove_addr_r(BinaryTreeNode<T> * rp_ptr, BinaryTreeNode<T> * r_ptr, const T & i_item)
{
	while (r_ptr->datum != i_item)
	{
		if (r_ptr->datum > i_item)
		{
			if (r_ptr->left_ptr == nullptr)
			{
				return nullptr;
			}
			else
			{
				rp_ptr = r_ptr;
				r_ptr = r_ptr->left_ptr;
			}
		}
		else // r_ptr->datum < i_item
		{
			if (r_ptr->right_ptr == nullptr)
			{
				return nullptr;
			}
			else
			{
				rp_ptr = r_ptr;
				r_ptr = r_ptr->right_ptr;
			}
		}
	}
	return rp_ptr;
}

template <typename T>
BinaryTreeNode<T> * BinarySearchTree<T>::leftmost_leaf_parent(BinaryTreeNode<T> * dele_ptr)
{
	Stack<BinaryTreeNode<T> *> addr_stack;
	addr_stack.push(dele_ptr);
	dele_ptr = dele_ptr->right_ptr;
	while (dele_ptr->left_ptr != nullptr)
	{
		addr_stack.push(dele_ptr);
		dele_ptr = dele_ptr->left_ptr;
	}
	return addr_stack.peek();
}

template <typename T>
bool BinarySearchTree<T>::remove(const T & i_item)
{
	// get address of parent node of the deleting node
	BinaryTreeNode<T> * dele_addr_parent = remove_addr_r(root_ptr, root_ptr, i_item), *dele_addr = nullptr, *lmlp = nullptr;
	// get address of the deleting node
	if (dele_addr_parent == nullptr)
	{
		return false;
	}
	else if (dele_addr_parent == root_ptr && dele_addr_parent->datum == i_item)
	{
		dele_addr = dele_addr_parent;
	}
	else
	{
		if (dele_addr_parent->datum > i_item)
		{
			dele_addr = dele_addr_parent->left_ptr;
		}
		else
		{
			dele_addr = dele_addr_parent->right_ptr;
		}
	}
	// eliminate deleting node
	if (dele_addr == root_ptr)
	{
    	if (dele_addr->left_ptr == nullptr && dele_addr->right_ptr == nullptr)
		{
			delete root_ptr;
			root_ptr = nullptr;
		}
    	else if (dele_addr->left_ptr != nullptr && dele_addr->right_ptr != nullptr)
		{
			lmlp = leftmost_leaf_parent(dele_addr);
			if (lmlp == dele_addr)
			{
				BinaryTreeNode<T> * temp = dele_addr->right_ptr;
				dele_addr->datum = dele_addr->right_ptr->datum;
				dele_addr->right_ptr = dele_addr->right_ptr->right_ptr;
				delete temp;
				temp = nullptr; 
			}
			else
			{
				BinaryTreeNode<T> * temp = lmlp->left_ptr;
				dele_addr->datum = lmlp->left_ptr->datum;
				lmlp->left_ptr = lmlp->left_ptr->right_ptr;
				delete temp;
				temp = nullptr;
			}
		}
  	    else if (dele_addr->right_ptr != nullptr)
		{
			root_ptr = dele_addr->right_ptr;
			delete dele_addr;
		}
 	    else
		{
			root_ptr = dele_addr->left_ptr;
			delete dele_addr;
		}
	}
	else
	{
 	    if (dele_addr->left_ptr == nullptr && dele_addr->right_ptr == nullptr)
		{
			if (dele_addr_parent->left_ptr == dele_addr)
			{
				delete dele_addr_parent->left_ptr;
				dele_addr_parent->left_ptr = nullptr;
			}
			else
			{
				delete dele_addr_parent->right_ptr;
				dele_addr_parent->right_ptr = nullptr;
			}
		}
 	    else if (dele_addr->left_ptr != nullptr && dele_addr->right_ptr != nullptr)
		{
			lmlp = leftmost_leaf_parent(dele_addr);
			if (lmlp == dele_addr)
			{
				BinaryTreeNode<T> * temp = lmlp->right_ptr;
				dele_addr->datum = dele_addr->right_ptr->datum;
				dele_addr->right_ptr = dele_addr->right_ptr->right_ptr;
				delete temp;
				temp = nullptr;
			}
			else
			{
				BinaryTreeNode<T> * temp = lmlp->left_ptr;
				dele_addr->datum = lmlp->left_ptr->datum;
				lmlp->left_ptr = lmlp->left_ptr->right_ptr;
				delete temp;
				temp = nullptr;
			}
		}
   	    else if (dele_addr->right_ptr != nullptr)
		{
			if (dele_addr_parent->left_ptr == dele_addr)
			{
				dele_addr_parent->left_ptr = dele_addr->right_ptr;
				delete dele_addr;
			}
			else
			{
				dele_addr_parent->right_ptr = dele_addr->right_ptr;
				delete dele_addr;
			}
		}
   	    else
		{
			if (dele_addr_parent->left_ptr == dele_addr)
			{
				dele_addr_parent->left_ptr = dele_addr->left_ptr;
				delete dele_addr;
			}
			else
			{
				dele_addr_parent->right_ptr = dele_addr->left_ptr;
				delete dele_addr;
			}
		}
	}
	dele_addr_parent = nullptr;
	dele_addr = nullptr;
	lmlp = nullptr;
	nodes_num -= 1;
	return true;
}

template <typename T>
bool BinarySearchTree<T>::isEmpty()
{
	if (nodes_num == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <typename T>
int BinarySearchTree<T>::max(int x1, int x2)
{
	if (x1 >= x2)
	{
		return x1;
	}
	else
	{
		return x2;
	}
}

template <typename T>
int BinarySearchTree<T>::get_height_r(BinaryTreeNode<T> * r_ptr)
{
	if (r_ptr == nullptr)
	{
		return 0;
	}
	else
	{
		return 1 + max(get_height_r(r_ptr->left_ptr), get_height_r(r_ptr->right_ptr));
	}
}

template <typename T>
int BinarySearchTree<T>::get_height()
{
	return get_height_r(root_ptr);
}

template <typename T>
int BinarySearchTree<T>::get_nodes_num()
{
	return nodes_num;
}

template <typename T>
BinaryTreeNode<T> BinarySearchTree<T>::get_root_data()
{
	return *root_ptr;
}

template <typename T>
void BinarySearchTree<T>::clear_r(BinaryTreeNode<T> * r_ptr)
{
	if (r_ptr == nullptr)
	{
		return;
	}
	else if (r_ptr->left_ptr == nullptr && r_ptr->right_ptr == nullptr)
	{
		delete r_ptr;
	}
	else
	{
		clear_r(r_ptr->left_ptr);
		clear_r(r_ptr->right_ptr);
		delete r_ptr;
	}
}

template <typename T>
void BinarySearchTree<T>::clear()
{
	clear_r(root_ptr);
	root_ptr = nullptr;
	nodes_num = 0;
	return;
}

template <typename T>
bool BinarySearchTree<T>::search_r(BinaryTreeNode<T> * r_ptr, BinaryTreeNode<T> * i_ptr)
{
	if (r_ptr == nullptr)
	{
		return false;
	}
	else
	{
		if (r_ptr->datum == i_ptr->datum)
		{
			return true;
		}
		else if (r_ptr->datum > i_ptr->datum)
		{
			return search_r(r_ptr->left_ptr, i_ptr);
		}
		else
		{
			return search_r(r_ptr->right_ptr, i_ptr);
		}
	}
}

template <typename T>
bool BinarySearchTree<T>::search(const T & i_item)
{
	BinaryTreeNode<T> * new_ptr = new BinaryTreeNode<T>(i_item);
	return search_r(root_ptr, new_ptr);
}

template <typename T>
void BinarySearchTree<T>::preorder_traverse_r(BinaryTreeNode<T> * r_ptr, void visit(T &))
{
	if (r_ptr == nullptr)
	{
		return;
	}
	else if (r_ptr->left_ptr == nullptr && r_ptr->right_ptr == nullptr)
	{
		visit(r_ptr->datum);
		return;
	}
	else
	{
		visit(r_ptr->datum);
		preorder_traverse_r(r_ptr->left_ptr, visit);
		preorder_traverse_r(r_ptr->right_ptr, visit);
		return;
	}
}

template <typename T>
void BinarySearchTree<T>::preorder_traverse(void visit(T &))
{
	preorder_traverse_r(root_ptr, visit);
	return;
}

template <typename T>
void BinarySearchTree<T>::inorder_traverse_r(BinaryTreeNode<T> * r_ptr, void visit(T &))
{
	if (r_ptr == nullptr)
	{
		return;
	}
	else if (r_ptr->left_ptr == nullptr && r_ptr->right_ptr == nullptr)
	{
		visit(r_ptr->datum);
		return;
	}
	else
	{
		inorder_traverse_r(r_ptr->left_ptr, visit);
		visit(r_ptr->datum);
		inorder_traverse_r(r_ptr->right_ptr, visit);
		return;
	}
}

template <typename T>
void BinarySearchTree<T>::inorder_traverse(void visit(T &))
{
	inorder_traverse_r(root_ptr, visit);
	return;
}

template <typename T>
void BinarySearchTree<T>::postorder_traverse_r(BinaryTreeNode<T> * r_ptr, void visit(T &))
{
	if (r_ptr == nullptr)
	{
		return;
	}
	else if (r_ptr->left_ptr == nullptr && r_ptr->right_ptr == nullptr)
	{
		visit(r_ptr->datum);
		return;
	}
	else
	{
		postorder_traverse_r(r_ptr->left_ptr, visit);
		postorder_traverse_r(r_ptr->right_ptr, visit);
		visit(r_ptr->datum);
		return;
	}
}

template <typename T>
void BinarySearchTree<T>::postorder_traverse(void visit(T &))
{
	postorder_traverse_r(root_ptr, visit);
	return;
}

template <typename T>
void BinarySearchTree<T>::breath_first_traverse_r(BinaryTreeNode<T> * r_ptr, void visit(T &))
{
	if (r_ptr->left_ptr == nullptr && r_ptr->right_ptr == nullptr)
	{
		return;
	}
	else if (r_ptr->left_ptr == nullptr)
	{
		visit(r_ptr->right_ptr->datum);
		breath_first_traverse_r(r_ptr->right_ptr, visit);
	}
	else if (r_ptr->right_ptr == nullptr)
	{
		visit(r_ptr->left_ptr->datum);
		breath_first_traverse_r(r_ptr->left_ptr, visit);
	}
	else
	{
		visit(r_ptr->left_ptr->datum);
		visit(r_ptr->right_ptr->datum);
		breath_first_traverse_r(r_ptr->left_ptr, visit);
		breath_first_traverse_r(r_ptr->right_ptr, visit);
	}
}

template <typename T>
void BinarySearchTree<T>::breath_first_traverse(void visit(T &))
{
	if (root_ptr == nullptr)
	{
		return;
	}
	else
	{
		visit(root_ptr->datum);
		breath_first_traverse_r(root_ptr, visit);
		return;
	}
}

template <typename T>
void BinarySearchTree<T>::show_trunks(Trunk * prev)
{
	if (prev == nullptr)
	{
		return;
	}
	else // prev != nullptr
	{
		show_trunks(prev->prev);
		std::cout << prev->str;
	}
}

template <typename T>
void BinarySearchTree<T>::print_tree_r(BinaryTreeNode<T> * r_ptr, Trunk * prev, bool is_left)
{
	if (r_ptr == nullptr)
	{
		return;
	}
	else
	{
		std::string prev_str = "       ";
		Trunk * trunk = new Trunk(prev, prev_str);

		print_tree_r(r_ptr->left_ptr, trunk, true);

		if (!prev)
		{
			trunk->str = "------";
		}
		else if (is_left)
		{
			trunk->str = ".------";
			prev_str = "      |";
		}
		else
		{
			trunk->str = "`------";
			prev->str = prev_str;
		}

		show_trunks(trunk); // pay attention to the show_trunks function
		std::cout << r_ptr->datum << std::endl;

		if (prev != nullptr)
		{
			prev->str = prev_str;
		}
		trunk->str = "      |";

		print_tree_r(r_ptr->right_ptr, trunk, false);
	}
}

template <typename T>
void BinarySearchTree<T>::print_tree()
{
	print_tree_r(root_ptr, nullptr, false);
	return;
}

#endif