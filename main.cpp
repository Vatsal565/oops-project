#include "Passenger.cpp"
#include <iostream>

int main() {
    Passenger p1("Vatsal", 19, "Male");
    Passenger p2("Miten", 19, "Male", true);

    cout << "Passenger 1 Info : " << endl;
    p1.displayInfo();
}