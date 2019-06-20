/********************************************************************************
************************************ BST ****************************************
*********************************************************************************
* Author: Olivier Chan - 70%
* Author: Luis Guerrero - 30%
*
* This class is a BST (binary search tree) ADT.
*****************
***** USAGE *****
*****************
* Functions:
*	insert()
*	remove()
*	findByKey()
*	maxDepth()
*********************************************************************************/

#pragma once

#include "BST_Node.h"

#include "Efficiency.h"

template <typename K, typename V>
class BST
{
protected:
	int count;
	BST_Node<K, V>* head;

	BST_Node<K, V>* insert(K, V&, BST_Node<K, V>*);
	BST_Node<K, V>* remove(const K&, const V&, BST_Node<K, V>*);
	BST_Node<K, V>* findByKey(const K&, BST_Node<K, V>*);
	BST_Node<K, V>* findInorderSuccessor(BST_Node<K, V>*); //Pass the right child of the node to find the successor of.
	void deleteAll(BST_Node<K, V>*);
	int maxDepth(int, const BST_Node<K, V>*);
public:
	BST();
	virtual ~BST();

	/**
	* getHead
	*
	* @brief Returns head.
	*
	* @return head
	*/
	BST_Node<K, V>* getHead() const;
	/**
	* insert
	*
	* @brief Recursively inserts the data into a new node in the sorted tree.
	*
	* @param The data to insert, as a reference.
	*/
	void insert(K, V&);
	/**
	* delete
	*
	* @brief Recursively deletes the node with matching key from the tree.
	*
	* @param The key of the node to delete.
	*/
	void remove(const K&, const V&);
	/**
	* find
	*
	* @brief Recursively finds the node with the matching key from the tree.
	*
	* @param K The key to search for.
	*
	* @param bool Whether to search for matching key or matching data. True searches for matching key.
	*
	* @return The found BST_Node.
	*/
	V& findByKey(const K&);
	/**
	* deleteAll
	*
	* @brief Deletes all managed nodes using a queue.
	*/
	virtual void deleteAll();
	/**
	* maxDepth
	*
	* @brief Returns the max depth of the BST.
	*/
	int maxDepth();
};

template <typename K, typename V>
BST<K, V>::BST() : count(0), head(nullptr)
{
	
}

template <typename K, typename V>
BST<K, V>::~BST()
{
	deleteAll();
}

template <typename K, typename V>
BST_Node<K, V>* BST<K, V>::getHead() const
{
	return head;
}
template <typename K, typename V>
void BST<K, V>::insert(K k, V& v)
{
	insert(k, v, head);
}

template <typename K, typename V>
BST_Node<K, V>* BST<K, V>::insert(K k, V& v, BST_Node<K, V>* root)
{
	//The BST is completely empty
	if (head == nullptr)
	{
		head = new BST_Node<K, V>(k, v);
		Efficiency::globalBinaryTreeOperations++;
		return head;
	}
	
	//If the root is non-existent, create a new node and return it - the new node will be saved in the previous call
	if (root == nullptr)
	{
		Efficiency::globalBinaryTreeOperations++;
		return new BST_Node<K, V>(k, v);
	}

	//If the new data is less than root, recur for left root
	if (k < root->key)
	{
		root->left = insert(k, v, root->left);
		Efficiency::globalBinaryTreeOperations++;
	}
	//If the new data is greater or equal than root, recur for right root
	else
	{
		root->right = insert(k, v, root->right);
		Efficiency::globalBinaryTreeOperations++;
	}

	//Return the root so previous recursion calls keep their current values for left and right
	return root;
}

template <typename K, typename V>
V& BST<K, V>::findByKey(const K& searchKey)
{
	return findByKey(searchKey, head)->value;
}

template <typename K, typename V>
BST_Node<K, V>* BST<K, V>::findByKey(const K& searchKey, BST_Node<K, V>* root)
{
	if (root == nullptr) //If the tree is empty, or we have reached a leaf node and haven't found the key, return null
	{
		return nullptr;
	}
	else
	{
		if (searchKey == root->key) //The node was found. Duplicate keys will return the first node found.
		{
			Efficiency::globalBinaryTreeOperations++;
			return root;
		}
		else if (searchKey < root->key) //if key is less than root, search from the left.
		{
			Efficiency::globalBinaryTreeOperations++;
			return find(searchKey, root->left, searchKey);
		}
		else if (searchKey > root->key) //if key is greater than root, search from the right.
		{
			Efficiency::globalBinaryTreeOperations++;
			return find(searchKey, root->right, searchKey);
		}
	}

	return nullptr;
}

template <typename K, typename V>
void BST<K, V>::remove(const K& key, const V& value)
{
	remove(key, value, head);
}

template <typename K, typename V>
BST_Node<K, V>* BST<K, V>::remove(const K& key, const V& value, BST_Node<K, V>* root)
{
	if (root == nullptr) //if tree is empty return null.
	{
		return root;
	}
	else if (key < root->key)//if data is less than root, remove the root from the left.
	{
		root->left = remove(key, value, root->left);
		Efficiency::globalBinaryTreeOperations++;
	}
	else if (key > root->key)//if data is greater than root, remove the root from the right.
	{
		root->right = remove(key, value, root->right);
		Efficiency::globalBinaryTreeOperations++;
	}
	else if (value != root->value)//if key matches, make sure value matches as well. Otherwise, the correct node must be to the right.
	{
		root->right = remove(key, value, root->right);
		Efficiency::globalBinaryTreeOperations++;
	}
	else//the key and value match. delete the node
	{
		//if root has no child
		if (root->left == nullptr && root->right == nullptr)
		{
			delete root;
			root = nullptr;
			Efficiency::globalBinaryTreeOperations++;
		}
		else if (root->left == nullptr) //if root has only one right child
		{
			//Copy the values from the right child into root and then delete the right child
			BST_Node<K, V>* temp = root->right;
			root->key = temp->key;
			root->value = temp->value;
			root->left = temp->left;
			root->right = temp->right;
			delete temp;
			temp = nullptr;
			Efficiency::globalBinaryTreeOperations++;
		}
		else if (root->right == nullptr) //if root has only one left child
		{
			//Copy the values from the left child into root and then delete the left child
			BST_Node<K, V>* temp = root->left;
			root->key = temp->key;
			root->value = temp->value;
			root->left = temp->left;
			root->right = temp->right;
			delete temp;
			temp = nullptr;
			Efficiency::globalBinaryTreeOperations++;
		}
		else //if root has a left and right child.
		{
			//Copy the values from the inorder successor to the root and then delete the inorder successor
			BST_Node<K, V>* temp = findInorderSuccessor(root->right);
			root->key = temp->key;
			root->value = temp->value;
			root->right = remove(temp->key, temp->value, root->right);
			Efficiency::globalBinaryTreeOperations++;
		}
	}
	return root;
}

template <typename K, typename V>
BST_Node<K, V>* BST<K, V>::findInorderSuccessor(BST_Node<K, V>* root)
{
	BST_Node<K, V>* current = root;
	while (current->left != nullptr)
	{
		current = current->left;
		Efficiency::globalBinaryTreeOperations++;
	}
	return current;
}

template <typename K, typename V>
void BST<K, V>::deleteAll(BST_Node<K, V>* root)
{
	if (root == nullptr)
	{
		return;
	}

	deleteAll(root->left);
	deleteAll(root->right);
	delete root;
	root = nullptr;
	Efficiency::globalBinaryTreeOperations++;
}

template <typename K, typename V>
void BST<K, V>::deleteAll()
{
	deleteAll(head);
}

template <typename K, typename V>
int BST<K, V>::maxDepth()
{
	return maxDepth(0, head);
}

template <typename K, typename V>
int BST<K, V>::maxDepth(int depth, const BST_Node<K, V>* root)
{
	if (root == nullptr)
	{
		return depth;
	}

	const int maxLeft = maxDepth(depth, root->left);
	const int maxRight = maxDepth(depth, root->right);

	return maxLeft >= maxRight ? maxLeft + 1: maxRight + 1;
}