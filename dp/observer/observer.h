#ifndef OBSERVER_H
#define OBSERVER_H

#include <iostream>

class Observer_V
{
public:
    Observer_V(){}
    virtual ~Observer_V(){}
    virtual void update() = 0;
};

class AObserver_C : public Observer_V
{
public:
    AObserver_C(){}
    ~AObserver_C(){}
    virtual void update(){ std::cout << "A Receive event, handle it" << std::endl; }
};

class BObserver_C : public Observer_V
{
public:
    BObserver_C(){}
    ~BObserver_C(){}
    virtual void update(){ std::cout << "B Receive event, handle it" << std::endl; }
};

#endif
