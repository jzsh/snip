#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <iostream>
#include "observer.h"

class Subject_V
{
public:
        Subject_V();
        virtual ~Subject_V();
        void attach(Observer_V* pObserver);
        void detach(Observer_V* pObserver);
        void notify();
        virtual void doSomething() = 0;
private:
        std::vector<Observer_V*> m_observersVec;
};

class ConcreteSubject_C : public Subject_V
{
public:
    virtual void doSomething() { std::cout << "happend" << std::endl; notify(); }
};

#endif
