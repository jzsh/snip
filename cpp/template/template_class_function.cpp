#include <iostream>
#include <string>
#include <cstring>

using namespace std;

typedef  char *STRCHR_T(const char *, int);

class A
{
public:
    A() {}
    ~A() {}

    template<char* (*T)(const char*, int)>
    const char* Pos(const char* str, int s) {
        char* p = T(str, s);
        if(p)
            cout << "pos=" << p << endl;
        return p;
    }

    template<typename T>
    const char* Pos1(const char* str, int s, T func) {
        char* p = func(str, s);
        if(p)
            cout << "pos=" << p << endl;
        return p;
    }
};


char * myStrChr(const char *s, int c)
{
    return strchr((char*)s, c);
}

int main()
{
    A a;
    int c = 'l';
    constexpr auto ttt1 = myStrChr; 
    const char* ptr = a.Pos<myStrChr>("hello", c);
    const char* ptr1 = a.Pos1("hello", c, myStrChr);

    //cout << ptr << endl;

}