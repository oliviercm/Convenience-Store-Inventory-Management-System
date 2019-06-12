#include <iostream>
using namespace std;
#include "Hash.h"
int main(int argc, const char * argv[])
{
    //string yx = "Hello";
    //HashTable<string> ok;
    //ok.add(yx);
    // cout << ok;
    HashTable<int> two;
    for(int i = 0; i < two.getSize(); i++)
    {
        two.add(i);
    }
    //cout << two;
    int x = 101;
    two.add(x);
    //cout << endl;
    cout << two.calcLoadFactor() << endl;
    cout << two;

	system("pause");
    return 0;
}
