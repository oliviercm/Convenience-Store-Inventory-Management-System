#pragma once
#ifndef AVLTREE
#define AVLTREE

#include <iostream>

#include "BinaryTreeNode.h"
#include "BinarySearchTree.h"
#include "Stack.h"

template <typename T>
class AVLTree : protected BinarySearchTree<T>
{
protected:
	int get_balanced_factor(BinaryTreeNode<T> *);
	BinaryTreeNode<T>* get_rp_add(const T &);
	void rotate_right(BinaryTreeNode<T> *, BinaryTreeNode<T> *);
	void rotate_left(BinaryTreeNode<T> *, BinaryTreeNode<T> *);
	void rotate(BinaryTreeNode<T> *, BinaryTreeNode<T> *, const T &);
	void rotate_rem(BinaryTreeNode<T> *, BinaryTreeNode<T> *);
	BinaryTreeNode<T>  * get_dele_addr(BinaryTreeNode<T> *, const T &);
	void to_leftmost_leaf_parent(Stack<BinaryTreeNode<T> *> &, const T &);
	void to_dele_node_parent(Stack<BinaryTreeNode<T> *> &, const T &);
public:
	bool isEmpty_avl();
	int get_height_avl();
	int get_nodes_num_avl();
	BinaryTreeNode<T> get_root_data_avl();
	void clear_avl();
	bool search_avl(const T &);
	void preorder_traverse_avl(void visit(T &));
	void inorder_traverse_avl(void visit(T &));
	void postorder_traverse_avl(void visit(T &));
	void breath_first_traverse_avl(void visit(T &));
	void add_avl(const T &);
	bool remove_avl(const T &);
	void print_tree_avl();
	void myVisit(List<Item>&);

	void check_balanced_r(BinaryTreeNode<T> *);
	void check_balanced();

};

template <typename T>
void AVLTree<T>::check_balanced_r(BinaryTreeNode<T> * r_ptr)
{
	if (r_ptr == nullptr)
	{
		return;
	}
	else if (r_ptr->left_ptr == nullptr && r_ptr->right_ptr == nullptr)
	{
		if (get_balanced_factor(r_ptr) != -1 && get_balanced_factor(r_ptr) != 0 && get_balanced_factor(r_ptr) != 1)
		{
			std::cout << "this is not a good point " << get_balanced_factor(r_ptr) << std::endl;
		}
		else
		{
			std::cout << get_balanced_factor(r_ptr) << std::endl;
		}
		return;
	}
	else
	{
		check_balanced_r(r_ptr->left_ptr);
		if (get_balanced_factor(r_ptr) != -1 && get_balanced_factor(r_ptr) != 0 && get_balanced_factor(r_ptr) != 1)
		{
			std::cout << "this is not a good point " << get_balanced_factor(r_ptr) << std::endl;
		}
		else
		{
			std::cout << get_balanced_factor(r_ptr) << std::endl;
		}
		check_balanced_r(r_ptr->right_ptr);
		return;
	}
}

template <typename T>
void AVLTree<T>::check_balanced()
{
	check_balanced_r(BinarySearchTree<T>::root_ptr);
	return;
}

template <typename T>
bool AVLTree<T>::isEmpty_avl()
{
	return BinarySearchTree<T>::isEmpty();
}

template <typename T>
int AVLTree<T>::get_height_avl()
{
	return  BinarySearchTree<T>::get_height();
}

template <typename T>
int AVLTree<T>::get_nodes_num_avl()
{
	return  BinarySearchTree<T>::get_nodes_num();
}

template <typename T>
BinaryTreeNode<T> AVLTree<T>::get_root_data_avl()
{
	return BinarySearchTree<T>::get_root_data();
}

template <typename T>
void AVLTree<T>::clear_avl()
{
	BinarySearchTree<T>::clear();
}

template <typename T>
bool AVLTree<T>::search_avl(const T & i_item)
{
	return BinarySearchTree<T>::search(i_item);
}

template <typename T>
void AVLTree<T>::preorder_traverse_avl(void visit(T &))
{
	BinarySearchTree<T>::preorder_traverse(visit);
}

template <typename T>
void AVLTree<T>::inorder_traverse_avl(void visit(T &))
{
	BinarySearchTree<T>::inorder_traverse(visit);
}

template <typename T>
void AVLTree<T>::postorder_traverse_avl(void visit(T &))
{
	BinarySearchTree<T>::postorder_traverse(visit);
}

template <typename T>
void AVLTree<T>::breath_first_traverse_avl(void visit(T &))
{
	BinarySearchTree<T>::breath_first_traverse(visit);
}

template <typename T>
int AVLTree<T>::get_balanced_factor(BinaryTreeNode<T> * node_ptr)
{
	return BinarySearchTree<T>::get_height_r(node_ptr->left_ptr) - BinarySearchTree<T>::get_height_r(node_ptr->right_ptr);
}

template <typename T>
BinaryTreeNode<T> * AVLTree<T>::get_rp_add(const T & i_item)
{
	Stack<BinaryTreeNode<T> *> stack_tt;
	BinaryTreeNode<T> * t_ptr = BinarySearchTree<T>::root_ptr, *tt_ptr = t_ptr;
	int balanced_factor;
	while (t_ptr->datum != i_item)
	{
		if (t_ptr->datum > i_item)
		{
			balanced_factor = get_balanced_factor(t_ptr);
			if (balanced_factor != -1 && balanced_factor != 0 && balanced_factor != 1)
			{
				stack_tt.push(tt_ptr);
			}
			tt_ptr = t_ptr;
			t_ptr = t_ptr->left_ptr;
		}
		else
		{
			balanced_factor = get_balanced_factor(t_ptr);
			if (balanced_factor != -1 && balanced_factor != 0 && balanced_factor != 1)
			{
				stack_tt.push(tt_ptr);
			}
			tt_ptr = t_ptr;
			t_ptr = t_ptr->right_ptr;
		}
	}
	if (stack_tt.isEmpty())
	{
		return nullptr;
	}
	else
	{
		return stack_tt.peek();
	}
}

template <typename T>
void AVLTree<T>::rotate_right(BinaryTreeNode<T> * rp_ptr, BinaryTreeNode<T> * r_ptr)
{
	if (rp_ptr == r_ptr)
	{
		BinarySearchTree<T>::root_ptr = r_ptr->left_ptr;
		r_ptr->left_ptr = r_ptr->left_ptr->right_ptr;
		BinarySearchTree<T>::root_ptr->right_ptr = r_ptr;
	}
	else
	{
		if (rp_ptr->left_ptr != nullptr && rp_ptr->left_ptr == r_ptr)
		{
			rp_ptr->left_ptr = r_ptr->left_ptr;
			r_ptr->left_ptr = r_ptr->left_ptr->right_ptr;
			rp_ptr->left_ptr->right_ptr = r_ptr;
		}
		else
		{
			rp_ptr->right_ptr = r_ptr->left_ptr;
			r_ptr->left_ptr = r_ptr->left_ptr->right_ptr;
			rp_ptr->right_ptr->right_ptr = r_ptr;
		}
	}
}

template <typename T>
void AVLTree<T>::rotate_left(BinaryTreeNode<T> * rp_ptr, BinaryTreeNode<T> * r_ptr)
{
	if (rp_ptr == r_ptr)
	{
		BinarySearchTree<T>::root_ptr = r_ptr->right_ptr;
		r_ptr->right_ptr = r_ptr->right_ptr->left_ptr;
		BinarySearchTree<T>::root_ptr->left_ptr = r_ptr;
	}
	else
	{
		if (rp_ptr->right_ptr != nullptr && rp_ptr->right_ptr == r_ptr)
		{
			rp_ptr->right_ptr = r_ptr->right_ptr;
			r_ptr->right_ptr = r_ptr->right_ptr->left_ptr;
			rp_ptr->right_ptr->left_ptr = r_ptr;
		}
		else
		{
			rp_ptr->left_ptr = r_ptr->right_ptr;
			r_ptr->right_ptr = r_ptr->right_ptr->left_ptr;
			rp_ptr->left_ptr->left_ptr = r_ptr;
		}
	}
}

template <typename T>
void AVLTree<T>::rotate(BinaryTreeNode<T> * rp_ptr, BinaryTreeNode<T> * r_ptr, const T & i_item)
{
	if (r_ptr->datum > i_item)
	{
		if (r_ptr->left_ptr->datum > i_item)
		{
			/*
			left-left
			*/
			rotate_right(rp_ptr, r_ptr);
		}
		else
		{
			/*
			left-right
			*/
			rotate_left(r_ptr, r_ptr->left_ptr);
			rotate_right(rp_ptr, r_ptr);
		}
	}
	else
	{
		if (r_ptr->right_ptr->datum > i_item)
		{
			/*
			right-left
			*/
			rotate_right(r_ptr, r_ptr->right_ptr);
			rotate_left(rp_ptr, r_ptr);
		}
		else
		{
			/*
			right-right
			*/
			rotate_left(rp_ptr, r_ptr);
		}
	}
}

template <typename T>
void AVLTree<T>::add_avl(const T & i_item)
{
	BinarySearchTree<T>::add(i_item);
	BinaryTreeNode<T> * unbalanced_root_parent = get_rp_add(i_item), *unbalanced_root = nullptr;
	int balanced_factor;
	if (unbalanced_root_parent == nullptr)
	{
	}
	else if (unbalanced_root_parent->datum > i_item)
	{
		balanced_factor = get_balanced_factor(unbalanced_root_parent->left_ptr);
		if (balanced_factor != -1 && balanced_factor != 0 && balanced_factor != 1)
		{
			unbalanced_root = unbalanced_root_parent->left_ptr;
		}
		else
		{
			unbalanced_root = unbalanced_root_parent;
		}
	}
	else
	{
		balanced_factor = get_balanced_factor(unbalanced_root_parent->right_ptr);
		if (balanced_factor != -1 && balanced_factor != 0 && balanced_factor != 1)
		{
			unbalanced_root = unbalanced_root_parent->right_ptr;
		}
		else
		{
			unbalanced_root = unbalanced_root_parent;
		}
	}
	if (unbalanced_root_parent == nullptr)
	{
	}
	else
	{
		rotate(unbalanced_root_parent, unbalanced_root, i_item);
	}
	/*
	check_balanced();
	std::cout << std::endl << std::endl << "*************************************************************************************************************" << std::endl << std::endl;
	*/
}

template <typename T>
void AVLTree<T>::rotate_rem(BinaryTreeNode<T> * rp_ptr, BinaryTreeNode<T> * r_ptr)
{
	if (BinarySearchTree<T>::get_height_r(r_ptr->left_ptr) > BinarySearchTree<T>::get_height_r(r_ptr->right_ptr))
	{
		if (BinarySearchTree<T>::get_height_r(r_ptr->left_ptr->left_ptr) >= BinarySearchTree<T>::get_height_r(r_ptr->left_ptr->right_ptr))
		{
			/*
			left-left
			*/
			rotate_right(rp_ptr, r_ptr);
		}
		else
		{
			/*
			left_right
			*/
			rotate_left(r_ptr, r_ptr->left_ptr);
			rotate_right(rp_ptr, r_ptr);
		}
	}
	else 
	{
		if (BinarySearchTree<T>::get_height_r(r_ptr->right_ptr->left_ptr) > BinarySearchTree<T>::get_height_r(r_ptr->right_ptr->right_ptr))
		{
			/*
			right-left
			*/
			rotate_right(r_ptr, r_ptr->right_ptr);
			rotate_left(rp_ptr, r_ptr);
		}
		else
		{
			/*
			right-right
			*/
			rotate_left(rp_ptr, r_ptr);
		}
	}
}

template <typename T>
BinaryTreeNode<T>  * AVLTree<T>::get_dele_addr(BinaryTreeNode<T> * r_ptr, const T & i_item)
{
	if (r_ptr == nullptr)
	{
		return  nullptr;
	}
	else // r_ptr != nullptr
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
					r_ptr = r_ptr->left_ptr;
				}
			}
			else
			{
				if (r_ptr->right_ptr == nullptr)
				{
					return  nullptr;
				}
				else
				{
					r_ptr = r_ptr->right_ptr;
				}
			}
		}
	}
	return r_ptr;
}

template <typename T>
void AVLTree<T>::to_leftmost_leaf_parent(Stack<BinaryTreeNode<T> *> & path_stack, const T & i_item)
{
	BinaryTreeNode<T> * temp = BinarySearchTree<T>::root_ptr;
	while (temp->datum != i_item)
	{
		path_stack.push(temp);
		if (temp->datum > i_item)
		{
			temp = temp->left_ptr;
		}
		else
		{
			temp = temp->right_ptr;
		}
	}
	path_stack.push(temp);
	temp = temp->right_ptr;
	while (temp->left_ptr != nullptr)
	{
		path_stack.push(temp);
		temp = temp->left_ptr;
	}
	return;
}

template <typename T>
void AVLTree<T>::to_dele_node_parent(Stack<BinaryTreeNode<T> *> & path_stack, const T & i_item)
{
	BinaryTreeNode<T> * temp_ptr = BinarySearchTree<T>::root_ptr;
	while (temp_ptr->datum != i_item)
	{
		path_stack.push(temp_ptr);
		if (temp_ptr->datum > i_item)
		{
			temp_ptr = temp_ptr->left_ptr;
		}
		else
		{
			temp_ptr = temp_ptr->right_ptr;
		}
	}
	return;
}

template <typename T>
bool AVLTree<T>::remove_avl(const T & i_item)
{
	bool result;
	// find the address of the deleting node
	BinaryTreeNode<T> * dele_addr = get_dele_addr(BinarySearchTree<T>::root_ptr, i_item);

	BinaryTreeNode<T> * unbalanced_root = nullptr, *unbalanced_root_parent = nullptr;
	Stack<BinaryTreeNode<T> *> path_stack;
	int balanced_factor;
	if (dele_addr != nullptr)
	{
		// find the path from the root to actionPos (the root of the deleted node)
		if (dele_addr->left_ptr != nullptr && dele_addr->right_ptr != nullptr)
		{
			to_leftmost_leaf_parent(path_stack, i_item);
		}
		else
		{
			to_dele_node_parent(path_stack, i_item);
		}

		// delete the deleting node
		result = BinarySearchTree<T>::remove(i_item);

		// rebalance the AVL tree from actionPos to root
		while (!path_stack.isEmpty())
		{
			if (path_stack.getCount() == 1)
			{
				balanced_factor = get_balanced_factor(path_stack.peek());
				if (balanced_factor != -1 && balanced_factor != 0 && balanced_factor != 1)
				{
					unbalanced_root = path_stack.peek();
					unbalanced_root_parent = path_stack.peek();
					rotate_rem(unbalanced_root_parent, unbalanced_root);
					path_stack.pop();
				}
				else
				{
					path_stack.pop();
				}
			}
			else
			{
				balanced_factor = get_balanced_factor(path_stack.peek());
				if (balanced_factor != -1 && balanced_factor != 0 && balanced_factor != 1)
				{
					unbalanced_root = path_stack.peek();
					path_stack.pop();
					unbalanced_root_parent = path_stack.peek();
					rotate_rem(unbalanced_root_parent, unbalanced_root);
				}
				else
				{
					path_stack.pop();
				}
			}
		}
	}
	/*
	check_balanced();
	std::cout << std::endl << std::endl << "*************************************************************************************************************" << std::endl << std::endl;
	*/
	check_balanced();
	std::cout << std::endl;
	return result;
}

template <typename T>
void AVLTree<T>::print_tree_avl()
{
	BinarySearchTree<T>::print_tree();
}

template<typename T>
void AVLTree<T>::myVisit(List<Item>& itemList)
{
	
}

#endif
