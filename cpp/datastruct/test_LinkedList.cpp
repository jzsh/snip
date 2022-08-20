#include <iostream>
#include "LinkedList.h"

using namespace std;

int main()
{
    LinkedList<int> list;
    list.add(1);
    list.add(3);
    list.add(5);
    list.display();

    auto iter = list.begin();
    while(iter != list.end()) {
        int a = iter.value();
        cout << a << endl;
        ++iter;
    }

    iter = list.begin();
    cout  << *(iter++) << endl;
}
