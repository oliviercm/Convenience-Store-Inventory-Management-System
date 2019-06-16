#include <iostream>
#include <fstream>
#include <string>
#include "BinaryTreeNode.h"
#include "BinarySearchTree.h"
#include "AVLTree.h"
using namespace std;

void visit(int &);
void read_in_data(AVLTree<int> &);
void delete_data(AVLTree<int> &);

int main()
{
	AVLTree<int> avlt;
	cout << avlt.get_height_avl() << endl;
	cout << avlt.get_nodes_num_avl() << endl << endl;

	read_in_data(avlt);

	delete_data(avlt);

	system("pause");
	return 0;
}

void read_in_data(AVLTree<int> & avlt)
{
	ifstream inputFile;
	int datum;
	inputFile.open("C:\\Users\\panyue\\source\\repos\\CIS22C\\Group_Project_BST_Backup2\\input.txt");
	while (inputFile >> datum)
	{
		avlt.add_avl(datum);
		/*
		avlt.print_tree_avl();
		cout << endl << "************************************************************************************" << endl;
		*/
	}
	inputFile.close();
}

void delete_data(AVLTree<int> & avlt)
{
	ifstream inputFile;
	int datum;
	inputFile.open("C:\\Users\\panyue\\source\\repos\\CIS22C\\Group_Project_BST_Backup2\\input_dele.txt");
	cout << inputFile.is_open() << endl;
	while (inputFile >> datum)
	{
		avlt.remove_avl(datum);
		/*
		avlt.print_tree_avl();
		cout << endl << "************************************************************************************" << endl;
		*/
		avlt.print_tree_avl();
		cout << endl << "************************************************************************************" << endl;
	}
	inputFile.close();
}

void visit(int & x)
{
	cout << x << " ";
}

/*
#include <iostream>
#include <fstream>
#include <string>
#include "BinaryTreeNode.h"
#include "BinarySearchTree.h"
#include "AVLTree.h"
using namespace std;

void visit(int &);
void read_in_data(BinarySearchTree<int> &);
void delete_data(BinarySearchTree<int> &);

int main()
{
	BinarySearchTree<int> bst;

	read_in_data(bst);

	delete_data(bst);

	system("pause");
	return 0;
}

void read_in_data(BinarySearchTree<int> & bst)
{
	ifstream inputFile;
	int datum;
	inputFile.open("C:\\Users\\panyue\\source\\repos\\CIS22C\\Group_Project_BST_Backup3\\input.txt");
	while (inputFile >> datum)
	{
		bst.add(datum);
		bst.print_tree();
		cout << endl << endl << "************************************************************************************************************" << endl << endl;
	}
	inputFile.close();
}

void delete_data(BinarySearchTree<int> & bst)
{
	ifstream inputFile;
	int datum;
	inputFile.open("C:\\Users\\panyue\\source\\repos\\CIS22C\\Group_Project_BST_Backup3\\input_dele.txt");
	while (inputFile >> datum)
	{
		bst.remove(datum);
		bst.print_tree();
		cout << endl << endl << "************************************************************************************************************" << endl << endl;
	}
	inputFile.close();
}

void visit(int & x)
{
	cout << x << " ";
}
*/