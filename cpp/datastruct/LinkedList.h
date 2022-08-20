// https://github.com/BigWheel92/Singly-Linked-List/blob/master/LinkedList.h
// https://github.com/youzp/DoubleLinkedList/blob/master/double_linked_list.h
// https://github.com/anthonyzhub/NodeList-With-Iterator/blob/master/NodeList.cpp
#ifndef LINKED_LIST_H

#include <cstddef>
#include <assert.h>

template<typename T>
class LinkedList
{
private:
	struct Node;
public:
	class Iterator;
    using NodePtr = Node*;

    LinkedList();
    virtual ~LinkedList();
    virtual size_t size() { return m_size; }
    virtual bool add(T);
    virtual T remove(size_t index);
    virtual void display();
	Iterator begin() const;
    Iterator end() const;
	Iterator find(const T &) const;

    class Iterator
	{
	public:
        explicit Iterator(Node* node);
		Node* node() const;
        T& value() const;
        bool valid() const;
        Iterator& operator++(); // ++iter
        Iterator operator++(int); // iter++
        bool operator==(const Iterator&) const;
        bool operator!=(const Iterator&) const;
        T& operator*() const { return m_pNode->data; }
	private:
		Node* m_pNode;
    };
private:
	struct Node
	{
	    T data;
	    Node* next;
	};

    NodePtr m_head, m_tail;
    size_t m_size;

};

template<typename T>
LinkedList<T>::LinkedList() : m_size(0),m_head(nullptr),m_tail(nullptr)
{
}

template<typename T>
LinkedList<T>::~LinkedList() 
{
    //TODO
}

template<typename T>
bool LinkedList<T>::add(T data) 
{
    NodePtr newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    if(m_head) {
        m_tail->next = newNode;
        m_tail = newNode;
    } else {
        m_head = newNode;
        m_tail = newNode;
    }
    m_size++;
    return true;
}

template<typename T>
void LinkedList<T>::display()
{
    NodePtr p = m_head;
    while(p) {
        std::cout << p->data << std::endl;
        p = p->next;
    }

}

template<typename T>
T LinkedList<T>::remove(size_t index) 
{
    T a;
    return a;
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() const
{
	return Iterator(m_head);
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end() const
{
	return Iterator(nullptr);
}
////////////////////////////////////////////////////////
template<typename T>
LinkedList<T>::Iterator::Iterator(Node* node):m_pNode(node)
{
}

template<typename T>
bool LinkedList<T>::Iterator::valid() const
{
	return m_pNode != nullptr;
}

template<typename T>
T& LinkedList<T>::Iterator::value() const
{
	return m_pNode->data;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Iterator::node() const
{
    return m_pNode;
}

template<typename T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++()
{
    assert(valid());
    m_pNode = m_pNode->next;
    return *this;
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(int)
{
    assert(valid());
    Iterator newIter(*this);
    m_pNode = m_pNode->next;
    return newIter;
}

template<typename T>
inline bool LinkedList<T>::Iterator::operator==(const Iterator& rhs) const
{
    return (rhs.m_pNode == this->m_pNode);
}

template<typename T>
inline bool LinkedList<T>::Iterator::operator!=(const Iterator& rhs) const
{
    return (rhs.m_pNode != this->m_pNode);
}


#endif
