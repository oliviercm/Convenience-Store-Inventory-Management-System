#include <iostream>
using namespace std;
#include "Hash.h"


int main(int argc, const char * argv[])
{
    HashTable<int, int> two;
    int size = two.getSize();
    for (int i = 0; i < size; i++)
    {
        two.add(i+1, i);
    }
    cout << two;
    int x = 101;
    two.add(x + 1, x);
    cout << two;
    cout << endl;
    cout << "The load factor of the table is: " << two.calcLoadFactor() << "%" << endl;
    cout << two;
    cout << endl;
    int a = 303;
    int b = 302;
    two.add(a, b);
    cout << "There's a collision at index 100!" << endl;
    cout << two << endl;
    List<int>* holder;
    holder = two.getItems(303);
    cout << "The number of nodes not directly on an index in the table are: " << two.getOffTable() << endl;
    cout << endl << "Entering key 303..nodes associated with this hash key are: " << endl;
    cout << *holder << endl;
    two.remove(x+1, x);
    cout << two;
    cout << endl;
    int y = 5;
    int z = 4;
    cout << "The number of operations to find key: 5, value: 4 is: " << two.getOperations(y, z) << endl;
    two.empty();
    cout << two;
    cout << endl;
    
    holder = two.getItems(0);
    cout << "Hash Table is empty? " << boolalpha << two.isEmpty() << endl;
    system("pause");
    return 0;
}



