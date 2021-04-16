#include "subject.h"

Subject_V::Subject_V()
{
}

Subject_V::~Subject_V()
{
}

void Subject_V::attach(Observer_V* pObeserver)
{
    m_observersVec.push_back(pObeserver);
}

void Subject_V::detach(Observer_V* pObeserver)
{
    for(std::vector<Observer_V*>::iterator itr = m_observersVec.begin();
        itr != m_observersVec.end(); itr++)
    {
        if(*itr == pObeserver)
        {
            m_observersVec.erase(itr);
            return;
        }
    }
}

void Subject_V::notify()
{
    for(std::vector<Observer_V*>::iterator itr = m_observersVec.begin();
        itr != m_observersVec.end();
        itr++)
    {
        (*itr)->update();
    }
}
