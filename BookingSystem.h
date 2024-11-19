#ifndef BOOKINGSYSTEM_H
#define BOOKINGSYSTEM_H

#include "Train.cpp"
#include <vector>
#include <string>
using namespace std;

class BookingSystem {
private:
    vector<Train> trains;

public:
    void loadTrainData(const string &filename);
    void saveTrainData(const string &filename) const;

    void addTrain(const Train &train);
    bool bookTicket(const string &trainID, const string &username, int age, const string &gender);
    bool cancelTicket(const string &trainID, const string &username, int seatNumber);
    void displayTrainInfo(const string &trainID) const;
    void viewUserBookings(const string &username) const;
};

#endif // BOOKINGSYSTEM_H
