#include <bits/stdc++.h>
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

// Transport Constructor
Transport::Transport(const string &id, const string &src, const string &dest)
    : transportID(id), source(src), destination(dest) {}

// Display Transport Info
void Transport::displayInfo() const {
    cout << "Transport ID: " << transportID << endl;
    cout << "Source: " << source << endl;
    cout << "Destination: " << destination << endl;
}

class Train : public Transport {
private:
    string trainName;
    int totalSeats;
    vector<string> seatAllocation; // Tracks passenger names
    vector<string> seatTypes;      // Types: Lower, Upper, Middle, etc.

public:
    Train(const string &id, const string &src, const string &dest, const string &name, int seats);
    ~Train();

    // Seat management
    vector<string> &getSeats();
    vector<string> &getSeatTypes();

    int getTotalSeats() const;
    int allocateSeat(const string &passengerName);  // Returns seat number on success, -1 on failure
    bool deallocateSeat(int seatNumber);            // Cancels a seat
    int getAvailableSeats() const;                  // Gets available seat count
    string getTrainName() const {
        return this->trainName;
    }

    // Display
    void displayInfo() const override;
};

vector<string> &Train::getSeats() {
    return seatAllocation;
}

vector<string> &Train::getSeatTypes() {
    return seatTypes;
}

int Train::getTotalSeats() const {
    return totalSeats;
}

// Train Constructor
Train::Train(const string &id, const string &src, const string &dest, const string &name, int seats)
    : Transport(id, src, dest), trainName(name), totalSeats(seats), seatAllocation(seats, ""), seatTypes(seats) {
    // Assign seat types
    for (int i = 0; i < seats; ++i) {
        if (i % 6 == 0 || i % 6 == 3) {
            seatTypes[i] = "Lower";
        } else if (i % 6 == 1 || i % 6 == 4) {
            seatTypes[i] = "Middle";
        } else {
            seatTypes[i] = "Upper";
        }
    }
}

// Train Destructor
Train::~Train() {
    cout << "Train " << trainName << " is being deconstructed." << endl;
}

// Allocate a Seat
int Train::allocateSeat(const string &passengerName) {
    for (int i = 0; i < totalSeats; ++i) {
        if (seatAllocation[i].empty()) {
            seatAllocation[i] = passengerName;
            return i + 1; // Seat number is 1-based
        }
    }
    return -1; // No available seats
}

// Deallocate a Seat
bool Train::deallocateSeat(int seatNumber) {
    if (seatNumber > 0 && seatNumber <= totalSeats && !seatAllocation[seatNumber - 1].empty()) {
        seatAllocation[seatNumber - 1].clear();
        return true;
    }
    return false;
}

// Get Available Seats
int Train::getAvailableSeats() const {
    int count = 0;
    for (const auto &seat : seatAllocation) {
        if (seat.empty()) {
            ++count;
        }
    }
    return count;
}

// Display Train Info
void Train::displayInfo() const {
    Transport::displayInfo(); // Call base class function
    cout << "Train Name: " << trainName << endl;
    cout << "Total Seats: " << totalSeats << endl;
    cout << "Available Seats: " << getAvailableSeats() << endl;
}
