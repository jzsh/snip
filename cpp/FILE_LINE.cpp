#include <cstdio>

void print_func(const char* file=__FILE__, int line=__LINE__)
{
    printf("file:%s, line:%d\n", file, line);
}

void print_func2(const char* file=__FILE__, int line=__LINE__);

int main()
{
    print_func(__FILE__, __LINE__);
    print_func();
    print_func2();
}

void print_func2(const char* file, int line)
{
    printf("method2: file:%s, line:%d\n", file, line);
}
