#include <iostream>
#include <memory>
#include <exception>

class A
{
private:
    int b;
    int c;
    float r;

public:
    void Print()
    {
        std::cout << "b = " << b << "\n" << "c = " << c << "\n" << "r = " << r << std::endl;
    }
};

template<typename T1, typename T2, int offset>
class PrivateAccess
{
private:
    T2* ptr;

public:
    PrivateAccess(T1& source)
    {
        if (offset > sizeof(T1))
        {
            throw std::exception();
        }

        uint8_t* p = (uint8_t*)&source;
        p += offset;
        ptr = (T2*)p;
    }

    void Set(T2&& value)
    {
        *ptr = value;
    }

    T2&& Get()
    {
        return *ptr;
    }
};

using A_a_accs = PrivateAccess<A, int, 0>;
using A_c_accs = PrivateAccess<A, int, 4>;

int main()
{
    A* a = new A();

    A_a_accs gh(*a);
    gh.Set(4);
    A_c_accs gb(*a);
    gb.Set(6);

    std::cout << gh.Get() << std::endl;

    a->Print();

    std::cout << "Hello World!\n";
}
