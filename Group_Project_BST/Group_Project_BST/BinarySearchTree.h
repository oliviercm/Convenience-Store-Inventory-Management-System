#pragma once
#ifndef BINARYSEARCHTREE
#define BINARYSEARCHTREE

#include "BinaryTreeNode.h"

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
	BinaryTreeNode<T> * remove_add_r(BinaryTreeNode<T> *, BinaryTreeNode<T> *, const T &);
	BinaryTreeNode<T> * leftmost_leaf(BinaryTreeNode<T> *);
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
	else // r_ptr->datum <= i_ptr->datum
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
BinaryTreeNode<T> * BinarySearchTree<T>::remove_add_r(BinaryTreeNode<T> * rp_ptr, BinaryTreeNode<T> * r_ptr, const T & i_item)
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
BinaryTreeNode<T> * BinarySearchTree<T>::leftmost_leaf(BinaryTreeNode<T> * r_ptr)
{
 	if (r_ptr->left_ptr == nullptr)
	{
		return r_ptr;
	}
	else // r_ptr->left != nullptr
	{
		leftmost_leaf(r_ptr->left_ptr);
	}
}

template <typename T>
bool BinarySearchTree<T>::remove(const T & i_item)
{
	// get address of parent node of the deleting node
	BinaryTreeNode<T> * dele_add_parent = remove_add_r(root_ptr, root_ptr, i_item), * dele_add = nullptr,  * lml = nullptr;
	// get address of the deleting node
	if (dele_add_parent == nullptr)
	{
		return false;
	}
	else if (dele_add_parent == root_ptr && dele_add_parent->datum == i_item)
	{
		dele_add = dele_add_parent;
	}
	else
	{
		if (dele_add_parent->datum > i_item)
		{
			dele_add = dele_add_parent->left_ptr;
		}
		else // dele_add_paretn->dataum <= i_item
		{
			dele_add = dele_add_parent->right_ptr;
		}
	}
	// eliminate deleting node
	if (dele_add == root_ptr)
	{
		if (dele_add->left_ptr == nullptr && dele_add->right_ptr == nullptr)
		{
			root_ptr = nullptr;
		}
		else if (dele_add->left_ptr != nullptr && dele_add->right_ptr != nullptr)
		{
			lml = leftmost_leaf(dele_add->right_ptr);
			lml->left_ptr = dele_add->left_ptr;
			root_ptr = dele_add->right_ptr;
		}
		else if (dele_add->right_ptr != nullptr)
		{
			root_ptr = dele_add->right_ptr;
		}
		else // dele_add->left_ptr != nullptr
		{
			root_ptr = dele_add->left_ptr;
		}
	}
	else // dele_add != root_ptr
	{
		if (dele_add->left_ptr == nullptr && dele_add->right_ptr == nullptr)
		{
			if (dele_add_parent->left_ptr == dele_add)
			{
				dele_add_parent->left_ptr = nullptr;
			}
			else // dele_add_parent->right_ptr == dele_add
			{
				dele_add_parent->right_ptr = nullptr;
			}
		}
		else if (dele_add->left_ptr != nullptr && dele_add->right_ptr != nullptr)
		{
			lml = leftmost_leaf(dele_add->right_ptr);
			lml->left_ptr = dele_add->left_ptr;
			if (dele_add_parent->right_ptr != nullptr && dele_add_parent->right_ptr == dele_add)
			{
				dele_add_parent->right_ptr = dele_add->right_ptr;
			}
			else // dele_add_parent->left_ptr != nullptr && dele_add_parent->left_ptr == dele_add
			{
				dele_add_parent->left_ptr = dele_add->right_ptr;
			}
		}
		else if (dele_add->right_ptr != nullptr)
		{
			if (dele_add_parent->left_ptr == dele_add)
			{
				dele_add_parent->left_ptr = dele_add->right_ptr;;
			}
			else // dele_add_parent->right_ptr == dele_add
			{
				dele_add_parent->right_ptr = dele_add->right_ptr;
			}
		}
		else // dele_add->left_ptr != nullptr
		{
			if (dele_add_parent->left_ptr == dele_add)
			{
				dele_add_parent->left_ptr = dele_add->left_ptr;
			}
			else // dele_add_parent->right_ptr == dele_add
			{
				dele_add_parent->right_ptr = dele_add->left_ptr;
			}
		}
	}
	dele_add_parent = nullptr;
	dele_add = nullptr;
	lml = nullptr;
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

#endif