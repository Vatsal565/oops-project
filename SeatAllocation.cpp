#include <iostream>
#include "Train.cpp"
using namespace std;

class SeatAllocation {
public:
    static int allocateSeat(Train &train, const string &passengerName, int age, const string &gender, bool isDisabled = false);
    static vector<int> allocateGroupSeats(Train &train, const vector<pair<string, pair<int, string>>> &groupDetails);
    static void reallocateSeatsOnCancellation(Train &train, int seatNumber);
};

// Allocate a Seat for a Single Passenger
int SeatAllocation::allocateSeat(Train &train, const string &passengerName, int age, const string &gender, bool isDisabled) {
    int totalSeats = train.getTotalSeats();
    vector<string> &seats = train.getSeats();
    vector<string> &seatTypes = train.getSeatTypes(); // E.g., Lower, Middle, Upper, etc.

    // Priority 1: Disabled passengers -> Preferred seat (lower berth if available)
    if (isDisabled) {
        for (int i = 0; i < totalSeats; ++i) {
            if (seatTypes[i] == "Lower" && seats[i].empty()) {
                seats[i] = passengerName;
                return i + 1;
            }
        }
    }

    // Priority 2: Senior citizens -> Lower berth
    if (age >= 60) {
        for (int i = 0; i < totalSeats; ++i) {
            if (seatTypes[i] == "Lower" && seats[i].empty()) {
                seats[i] = passengerName;
                return i + 1;
            }
        }
    }

    // Priority 3: Younger passengers -> Upper berth
    if (age < 30) {
        for (int i = 0; i < totalSeats; ++i) {
            if (seatTypes[i] == "Upper" && seats[i].empty()) {
                seats[i] = passengerName;
                return i + 1;
            }
        }
    }

    // Priority 4: General allocation -> First available seat
    for (int i = 0; i < totalSeats; ++i) {
        if (seats[i].empty()) {
            seats[i] = passengerName;
            return i + 1;
        }
    }

    // If no seat is available, return -1
    return -1;
}

// Allocate Seats for a Group
vector<int> SeatAllocation::allocateGroupSeats(Train &train, const vector<pair<string, pair<int, string>>> &groupDetails) {
    vector<int> allocatedSeats;
    vector<string> &seats = train.getSeats();
    int totalSeats = train.getTotalSeats();

    // Try to allocate seats sequentially
    for (int i = 0; i < totalSeats && allocatedSeats.size() < groupDetails.size(); ++i) {
        if (seats[i].empty()) {
            seats[i] = groupDetails[allocatedSeats.size()].first; // Assign passenger name
            allocatedSeats.push_back(i + 1);
        }
    }

    // If not enough seats, clear allocations and return empty vector
    if (allocatedSeats.size() < groupDetails.size()) {
        for (int seat : allocatedSeats) {
            seats[seat - 1].clear();
        }
        return {};
    }

    return allocatedSeats;
}

// Reallocate Seats on Cancellation
void SeatAllocation::reallocateSeatsOnCancellation(Train &train, int seatNumber) {
    vector<string> &seats = train.getSeats();

    // Mark seat as available
    if (seatNumber > 0 && seatNumber <= train.getTotalSeats()) {
        seats[seatNumber - 1].clear();
        cout << "Seat " << seatNumber << " is now available." << endl;
    }

    // Additional logic for dynamic reallocation can be added here
}
