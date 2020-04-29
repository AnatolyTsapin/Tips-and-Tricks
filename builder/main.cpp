#include <string>
#include <iostream>
#include <stdexcept>

#include "builder.h"

using namespace std;

ostream& operator<<(ostream& s, const Card& c)
{
    s << "Name:      " << c.name << endl;
    s << "Surname:   " << c.surname << endl;
    s << "Job Title: " << c.jobTitle << endl;
    s << "Email:     " << c.email << endl;
    for(const auto& phone : c.phone)
        s << "Phone:     " << phone << endl;
    return s;
}

int main(int argc, char* argv[])
try
{
    cout << "Start test" << endl;

    auto card = CardBuilder().name("John").surname("Smith").email("john@my.mail").build();
    cout << card << endl;

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
