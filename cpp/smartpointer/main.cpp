#include <iostream>
#include <memory>
using namespace std;
 
class Rectangle {
public:
    Rectangle() : length(0), breadth(0) { cout << "construct" << endl; }
// private:
    int length;
    int breadth;
	Rectangle& operator=(const Rectangle& r) { cout << "assign construct" << endl; length = r.length; breadth = r.breadth; return *this; }
	Rectangle(const Rectangle& r) { cout << "copy construct" << endl; length = r.length; breadth = r.breadth; }
};

class Node {
public:
    Rectangle& getRectange() {
        return m_rect;
    }
    Rectangle getRectangeClone() {
        Rectangle rect;
        return rect;
    }
private:
    Rectangle m_rect;
};
 
void fun()
{
    Node node;
    cout << "-----------------------" << endl; 
    Rectangle rect = node.getRectange();
    cout << "-----------------------" << endl; 
    Rectangle& rect1 = node.getRectange();
    cout << "-----------------------" << endl; 
    Rectangle rect2 = node.getRectangeClone();
    //cout << "-----------------------" << endl; 
    //Rectangle& rect3 = node.getRectangeClone(); can not bind non-const lvalue rect3 to rvalue
}
 
int main()
{
    fun();
}
