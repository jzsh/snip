
#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class Stack {
private:
	std::vector<T> elems;
public:
	void push(T const&);
	void pop();
	T top() const;
	bool empty() const {
		return elems.empty();
	}
};

template <class T>
void Stack<T>::push (T const& elem)
{
    // 追加传入元素的副本
    elems.push_back(elem);
}

template <class T>
void Stack<T>::pop ()
{
    if (elems.empty()) {
		throw std::out_of_range("Stack<>::pop(): empty stack");
    }
    // 删除最后一个元素
    elems.pop_back();
}

template <typename T>
T Stack<T>::top() const
{
	if(elems.empty()) {
		throw std::out_of_range("Stack<::top(: empty stack)>");
	}
	return elems.back();
}

int main()
{
    try {
        Stack<int>         intStack;  // int 类型的栈
        Stack<std::string> stringStack;    // string 类型的栈

        // 操作 int 类型的栈
        intStack.push(7);
		std::cout << intStack.top() << std::endl;

        // 操作 string 类型的栈
        stringStack.push("hello");
		std::cout << stringStack.top() << std::endl;
        stringStack.pop();
        stringStack.pop();
    }
    catch (std::exception const& ex) {
		std::cerr << "Exception: " << ex.what() << std::endl;
        return -1;
    }
}
