#include <iostream>

using namespace std;

class C {
public:
    C() { cout << "C class construct" << endl; }
};

class Base {
public:
    Base() { cout << "Base class construct" << endl; }
private:
    int m_a;
};

class Derive : public Base {
public:
    Derive() { cout << "Derive class construct" << endl; }
public:
    C c;
};

int main()
{
    // Base class construct
    // C class construct
    // Derive class construct
    Derive d;
}
