#include <iostream>
using namespace std;

struct HEADER
{
    unsigned int version : 4;
    unsigned int protocol : 4;
    unsigned int length : 12;
    unsigned flags : 4;
    unsigned int : 6;
    bool valid : 1;
    bool global : 1;

    unsigned int source : 32;
    unsigned int destination : 32;

};

int main()
{
    HEADER h;
    h.valid = true;

    cout << "HEADER size:" << sizeof(HEADER) << "bytes" << endl;

    return 0;
}
