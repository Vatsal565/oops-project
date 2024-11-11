#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // For random ticket number generation
#include <ctime>   // For seeding random number generator
#include <map>     // For tracking booked tickets

using namespace std;

// Train Class for managing train information
class Train
{
public:
    int trainNumber;
    string trainName;
    string source;
    string destination;
    int totalSeats;
    int availableSeats;

    Train(int num, string name, string src, string dest, int seats)
        : trainNumber(num), trainName(name), source(src), destination(dest), totalSeats(seats), availableSeats(seats) {}

    void displayTrainInfo() const
    {
        cout << "Train Number: " << trainNumber << ", Name: " << trainName << endl;
        cout << "Source: " << source << ", Destination: " << destination << endl;
        cout << "Total Seats: " << totalSeats << ", Available Seats: " << availableSeats << endl;
    }
};

// BookingSystem Class for managing bookings and cancellations
class BookingSystem
{
    map<int, int> bookings; // Map of ticket numbers to train numbers for simplicity

public:
    BookingSystem() { srand(static_cast<unsigned int>(time(0))); }

    int bookTicket(Train &train)
    {
        if (train.availableSeats > 0)
        {
            int ticketNumber = generateTicketNumber();
            bookings[ticketNumber] = train.trainNumber;
            train.availableSeats--;
            cout << "Booking Successful! Your Ticket Number is: " << ticketNumber << endl;
            return ticketNumber;
        }
        else
        {
            cout << "Sorry, no available seats on this train." << endl;
            return -1;
        }
    }

    void cancelTicket(Train &train, int ticketNumber)
    {
        auto it = bookings.find(ticketNumber);
        if (it != bookings.end() && it->second == train.trainNumber)
        {
            bookings.erase(it);
            train.availableSeats++;
            cout << "Cancellation Successful. Ticket Number " << ticketNumber << " has been canceled." << endl;
        }
        else
        {
            cout << "Invalid ticket number or ticket does not belong to this train." << endl;
        }
    }

    void displayBookingStatus(const Train &train) const
    {
        cout << "Train Number: " << train.trainNumber << " - Available Seats: " << train.availableSeats << endl;
    }

private:
    int generateTicketNumber()
    {
        return rand() % 9000 + 1000; // Generates a random 4-digit number between 1000 and 9999
    }
};

// Main Function to demonstrate the system
int main()
{
    // Creating a few train instances
    Train train1(101, "Express A", "City X", "City Y", 100);
    Train train2(102, "Express B", "City Z", "City W", 50);

    // Creating booking system instance
    BookingSystem bookingSystem;

    // Display train information
    cout << "Available Trains:\n";
    train1.displayTrainInfo();
    train2.displayTrainInfo();

    // Book some tickets
    cout << "\nBooking tickets...\n";
    int ticket1 = bookingSystem.bookTicket(train1);
    int ticket2 = bookingSystem.bookTicket(train2);

    // Display booking status
    cout << "\nBooking Status after booking:\n";
    bookingSystem.displayBookingStatus(train1);
    bookingSystem.displayBookingStatus(train2);

    // Cancel a ticket
    cout << "\nCancelling a ticket...\n";
    bookingSystem.cancelTicket(train1, ticket1);

    // Display booking status after cancellation
    cout << "\nBooking Status after cancellation:\n";
    bookingSystem.displayBookingStatus(train1);
    bookingSystem.displayBookingStatus(train2);

    return 0;
}
