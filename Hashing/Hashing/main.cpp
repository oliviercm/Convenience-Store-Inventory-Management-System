#include <iostream>
using namespace std;
#include "Hash.h"


int main(int argc, const char * argv[])
{
	HashTable<int> two;
	int size = two.getSize();
	for (int i = 0; i < size; i++)
	{
		two.add(i+1, i);
	}
	cout << two;
	int x = 101;
	two.add(x+1, x);
	cout << endl;
	cout << "The load factor of the table is: " << two.calcLoadFactor() << "%" << endl;
	cout << two;
	cout << endl;
	cout << "The number of nodes not directly on an index in the table are: " << two.getOffTable() << endl;
	two.remove(x+1, x);
	cout << two;
	cout << endl;
	int y = 5;
	int z = 4;
	cout << "The number of operations to find key: 5, value: 4 is: " << two.getOperations(y, z) << endl;
	two.empty();
	cout << two;
	cout << endl; 
	cout << "Hash Table is empty? " << boolalpha << two.isEmpty() << endl;
	system("pause");
	return 0;
}

