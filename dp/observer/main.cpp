#include "subject.h"
#include "observer.h"

int main()
{
    Subject_V* sub = new ConcreteSubject_C;

    sub->attach(new AObserver_C());
    sub->attach(new BObserver_C());

    sub->doSomething();
}
