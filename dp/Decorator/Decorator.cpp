/*
 * C++ Design Patterns: Decorator
 * Author: Jakub Vojvoda [github.com/JakubVojvoda]
 * 2016
 *
 * Source code is licensed under MIT License
 * (for more details see LICENSE)
 *
 */

#include <iostream>

/*
 * Component
 * defines an interface for objects that can have responsibilities
 * added to them dynamically
 */
class Component
{
public:
    virtual ~Component() {}

    virtual std::string operation() = 0;
    // ...
};

/*
 * Concrete Component
 * defines an object to which additional responsibilities
 * can be attached
 */
class ConcreteComponent : public Component
{
public:
    ~ConcreteComponent() {}

    std::string operation()
    {
    return "ConcreteComponent";
    }
    // ...
};

/*
 * Decorator
 * maintains a reference to a Component object and defines an interface
 * that conforms to Component's interface
 */
class Decorator : public Component
{
public:
    ~Decorator() {}

    Decorator( Component *c ) : component( c ) {}

    // The Decorator delegates all work to the wrappered component
    virtual std::string operation()
    {
    return component->operation();
    }
    // ...

private:
    Component *component;
};

/*
 * Concrete Decorators
 * add responsibilities to the component (can extend the state
 * of the component)
 */
class ConcreteDecoratorA : public Decorator
{
public:
    ConcreteDecoratorA( Component *c ) : Decorator( c ) {}

    std::string operation()
    {
        return std::string() + "ConcreateDecoratorA" + "(" + Decorator::operation() + ")";
    }
    // ...
};

class ConcreteDecoratorB : public Decorator
{
public:
    ConcreteDecoratorB( Component *c ) : Decorator( c ) {}

    std::string operation()
    {
        return std::string() + "ConcreateDecoratorB" + "(" + Decorator::operation() + ")";
    }
    // ...
};


void ClientCode(Component* component) {
    std::cout << "RESULT: " << component->operation() << std::endl;
}

int main()
{
    ConcreteComponent  *cc = new ConcreteComponent();
    ConcreteDecoratorB *db = new ConcreteDecoratorB( cc );
    ConcreteDecoratorA *da = new ConcreteDecoratorA( db );

    ClientCode(cc);
    ClientCode(db);
    ClientCode(da);

    delete da;
    delete db;
    delete cc;

    return 0;
}
