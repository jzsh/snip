#include <iostream>
#include <string>
#include <thread>
#include <ctime>
#include <unistd.h>

using namespace std;

// h
class Singleton
{
public:
    // return reference
    static Singleton* getInstance();
    std::string& value() { return _value; }

private:
    static Singleton* _instance;
    std::string _value;
private:
    Singleton(){ _value = std::to_string(rand()); }
    ~Singleton(){};
    Singleton(const Singleton&) = delete;
    const Singleton& operator=(const Singleton&) = delete;
};

// cpp

Singleton* Singleton::_instance = nullptr;

Singleton* Singleton::getInstance()
{
    if(_instance == nullptr) {
        _instance = new Singleton();
    }
    return _instance;
}

void ThreadFoo(){
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::getInstance();
    std::cout << singleton->value() << "\n";
}

void ThreadBar(){
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::getInstance();
    std::cout << singleton->value() << "\n";
}

int main()
{
    std::cout <<"If you see the same value, then singleton was reused (yay!\n" <<
                "If you see different values, then 2 singletons were created (booo!!)\n\n" <<
                "RESULT:\n";

    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    std::cout << "Done" << std::endl;
    t1.join();
    t2.join();
    std::cout << "Join Done" << std::endl;

    return 0;
}

