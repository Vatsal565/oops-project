#include "Transport.h"
#include <iostream>
using namespace std;

// Transport Constructor
Transport::Transport(const string &id, const string &src, const string &dest)
    : transportID(id), source(src), destination(dest) {}

// Display Transport Info
void Transport::displayInfo() const {
    cout << "Transport ID: " << transportID << endl;
    cout << "Source: " << source << endl;
    cout << "Destination: " << destination << endl;
}
