#include "Passenger.cpp"
#include <iostream>
using namespace std;

Passenger* login() {
    string username, password;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    return Passenger::loadFromCSV(username, password);
}

int main() {
    Passenger *p = nullptr;
    int choice;

    cout << "1. Register User" << endl << "2. Login User" << endl;
    cout << "Enter Your Choice : ";
    cin >> choice;

    if (choice == 1)
    {
        Passenger newPassenger("Vatsal", 19, "Male", "vatsal123", "vatsal123");
        newPassenger.saveToCSV();
        cout << "Registration done Successfully!" << endl;
    }
    else if (choice == 2)
    {
        p = login();

        if (p != nullptr) {
            cout << "Login successful!" << endl;
            p->displayInfo();
        } 
        else {
            cout << "Login failed. Please check your username and password.\n";
        }
    }
    else {
        cout << "Invalid choice. Exiting.\n";
    }
    
    
    /* Testing Passenger.cpp
    // Passenger p1("Vatsal", 19, "Male", "vatsal123", "vatsal123");
    // Passenger p2("Miten", 19, "Male", "miten123", "miten123", true);

    // p1.saveToCSV();
    // p2.saveToCSV();

    // string username, password;

    // cout << "Enter Your Username : ";
    // cin >> username;
    // cout << "Enter Your Password : ";
    // cin >> password;

    // Passenger::loadFromCSV(username, password);
    */

    if (p) delete p;
    return 0;
}