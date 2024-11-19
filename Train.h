#ifndef TRAIN_H
#define TRAIN_H

#include "Transport.h"
#include <vector>
#include <string>
using namespace std;

class Train : public Transport {
private:
    string trainName;
    int totalSeats;
    vector<string> seatAllocation; // Tracks allocated passenger names or empty seats

public:
    Train(const string &id, const string &src, const string &dest, const string &name, int seats);
    ~Train();

    // Seat management
    int allocateSeat(const string &passengerName);  // Returns seat number on success, -1 on failure
    bool deallocateSeat(int seatNumber);            // Cancels a seat
    int getAvailableSeats() const;                  // Gets available seat count

    // Display
    void displayInfo() const override;
};

#endif // TRAIN_H
