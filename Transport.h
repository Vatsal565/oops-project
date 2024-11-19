#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <string>
using namespace std;

class Transport {
public:
    string transportID;
    string source;
    string destination;

public:
    Transport(const string &id, const string &src, const string &dest);
    virtual void displayInfo() const; // Polymorphic function
    virtual ~Transport() {}
};

#endif // TRANSPORT_H
