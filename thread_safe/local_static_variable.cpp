#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>

template<typename ValueT>
class EnvReader
{
public:
    EnvReader(const char* envName) {
        printf("construct...%p\n", this);
        std::call_once(flag, &EnvReader::parseEnv, this, envName);
    }
    void parseEnv(const char* envName);
    ValueT& operator*() {
        return m_value;
    }
private:
    ValueT m_value;
    std::once_flag flag;
};

template<>
void EnvReader<bool>::parseEnv(const char* envName)
{
    printf("getenv...%p\n", this);
    m_value = getenv(envName) != NULL;
}
template<>
void EnvReader<int>::parseEnv(const char* envName)
{
    printf("getenv...%p\n", this);
    const char* envStr = getenv(envName);
    if(envStr) m_value = atoi(envStr);
    else m_value = 0;
}

void GetEnv()
{
	static EnvReader<bool> obj("VERDI_HOME");
    printf("bool=%d\n", *obj);
	static EnvReader<int> obj1("NUM");
    printf("int=%d\n", *obj1);
// 	static EnvReader<char> obj2("CHAR");
}

int main()
{
    std::thread t1(GetEnv);
    std::thread t2(GetEnv);
    std::thread t3(GetEnv);
    std::thread t4(GetEnv);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}
