#include <iostream>

using namespace std;

// h
class Singleton
{
public:
    // return reference
    static Singleton& getInstance();

private:
    Singleton(){};
    ~Singleton(){};
    Singleton(const Singleton&) = delete;
    const Singleton& operator=(const Singleton&) = delete;
};

// cpp

Singleton& Singleton::getInstance()
{
    static Singleton instance;
    return instance;
}

int main()
{
    Singleton &s1 = Singleton::getInstance();
    Singleton &s2 = Singleton::getInstance();

    return 0;
}
