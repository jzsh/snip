#include <iostream>
#include "Product.h"

using namespace std;

Product::Product()
{

}
Product::~Product()
{

}

ConcreteProduct::ConcreteProduct()
{
    cout << "ConcreteProduct construct" << endl;
}

ConcreteProduct::~ConcreteProduct()
{
    cout << "ConcreteProduct deconstruct" << endl;
}

