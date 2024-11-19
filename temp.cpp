#include "BookingSystem.cpp"
#include "Passenger.cpp"
#include <iostream>
using namespace std;

int main() {
    BookingSystem system;
    system.loadTrainData("train_data.csv");

    string username, password;
    Passenger* loggedInUser = nullptr;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Authenticate user
    loggedInUser = Passenger::loadFromCSV(username, password);

    if (!loggedInUser) {
        cout << "Invalid credentials. Exiting." << endl;
        return 1;
    }

    cout << "Welcome, " << loggedInUser->getName() << "!" << endl;

    int choice;
    do {
        cout << "\n--- User Menu ---\n";
        cout << "1. Book Ticket\n";
        cout << "2. Cancel Ticket\n";
        cout << "3. View My Bookings\n";
        cout << "4. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string trainID, gender;
            int age;
            cout << "Enter Train ID: ";
            cin >> trainID;
            cout << "Enter your age: ";
            cin >> age;
            cout << "Enter your gender: ";
            cin >> gender;
            system.bookTicket(trainID, username, age, gender);
        } else if (choice == 2) {
            string trainID;
            int seatNumber;
            cout << "Enter Train ID: ";
            cin >> trainID;
            cout << "Enter Seat Number: ";
            cin >> seatNumber;
            system.cancelTicket(trainID, username, seatNumber);
        } else if (choice == 3) {
            system.viewUserBookings(username);
        }
    } while (choice != 4);

    cout << "Goodbye, " << loggedInUser->getName() << "!" << endl;

    delete loggedInUser;
    return 0;
}
