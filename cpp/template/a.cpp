#include <iostream>
#include <cstring>
using namespace std;
typedef char* SearchF(char*, int);
char* myStrChr(const char* str, int c)
{
    return strchr((char*)str, c);
}
class A
{
public:
    void lprint(char *str, int c) { _print(str, c, strchr); }
    void rprint(char *str, int c) { _print(str, c, strrchr); }
private:
    void _print(char *str, int c, SearchF func) {
        // do_something_1
        char *ptr = func(str, c);
        if(ptr != NULL) {
            cout << ptr << endl;
        }
        // do_something_2 
    }
};

int main()
{
    A a;
    char s[16] = "hello";
    a.lprint(s, 'l');
    a.rprint(s, 'l');
}
