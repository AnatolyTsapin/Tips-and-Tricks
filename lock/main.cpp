#include <string>
#include <iostream>
#include <stdexcept>

#include "lock.h"

using namespace std;

class Test
{
public:
    Test(bool& locked, const string& name, int id = 0) :
        locked(locked),
        name(name + (id ? to_string(id) : string()))
    {}

    void lock() const
    {
        locked = true;
        cout << name << ": lock()" << endl;
    }
    void unlock() const
    {
        locked = false;
        cout << name << ": unlock()" << endl;
    }

    int add(int a, int b) const
    {
        if(!locked)
            throw runtime_error(name + ": Lock is not acquired");
        cout << name << ": add(" << a << ", " << b << ")" << endl;
        return a + b;
    }

    bool& locked;
    string name;
};

int main(int argc, char* argv[])
try
{
    bool l1 = false, l2 = false;
    Lock<Test> test1(l1, "Test", 1);
    Lock<const Test> test2(l2, "Test", 2);

    cout << "Start test" << endl;

    int x = test1->add(1, 3) + test2->add(2, 5);
    if(l1 || l2)
        throw runtime_error("One of objects is not released");

    cout << x << endl;

    auto n = test1->name;
    cout << n << endl;

    if(l1 || l2)
        throw runtime_error("One of objects is not released");

    return 0;
}
catch(const exception& e)
{
    cerr << e.what() << endl;
    return 1;
}
catch(...)
{
    cerr << "Unknown exception is caught" << endl;
    return 2;
}
