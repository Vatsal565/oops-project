#include <fstream>
#include <sstream>
#include <iostream>
#include "SeatAllocation.cpp"
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

// Load Train Data from File
void BookingSystem::loadTrainData(const string &filename) {
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        getline(file, line); // Skip header
        while (getline(file, line)) {
            stringstream ss(line);
            string trainID, source, destination, trainName;
            int totalSeats;

            getline(ss, trainID, ',');
            getline(ss, source, ',');
            getline(ss, destination, ',');
            getline(ss, trainName, ',');
            ss >> totalSeats;

            trains.emplace_back(trainID, source, destination, trainName, totalSeats);
        }
        file.close();
    }
}

// Save Train Data to File
void BookingSystem::saveTrainData(const string &filename) const {
    ofstream file(filename);

    if (file.is_open()) {
        file << "TrainID,Source,Destination,TrainName,TotalSeats\n";
        for (const auto &train : trains) {
            file << train.transportID << ","
                 << train.source << ","
                 << train.destination << ","
                 << train.getTrainName() << ","
                 << train.getAvailableSeats() << "\n";
        }
        file.close();
    }
}

// Add a Train
void BookingSystem::addTrain(const Train &train) {
    trains.push_back(train);
}

bool BookingSystem::bookTicket(const string &trainID, const string &username, int age, const string &gender) {
    for (auto &train : trains) {
        if (trainID == train.transportID) {
            // Use SeatAllocation to allocate a seat
            int seat = SeatAllocation::allocateSeat(train, username, age, gender);
            if (seat != -1) {
                // Save the booking record to file
                ofstream file("user_bookings.csv", ios::app); // Open in append mode
                if (file.is_open()) {
                    file << username << "," << trainID << "," << seat << "," 
                         << train.source << "," << train.destination << "\n";
                    file.close();
                } else {
                    cerr << "Error: Unable to open user_bookings.csv for writing." << endl;
                    return false;
                }

                cout << "Ticket booked successfully for " << username << ": Train " 
                     << trainID << ", Seat " << seat << endl;
                return true;
            } else {
                cout << "No available seats on train " << trainID << endl;
                return false;
            }
        }
    }
    cout << "Train with ID " << trainID << " not found." << endl;
    return false;
}



// Cancel a Ticket for a User
bool BookingSystem::cancelTicket(const string &trainID, const string &username, int seatNumber) {
    for (auto &train : trains) {
        if (trainID == train.transportID) {
            if (train.deallocateSeat(seatNumber)) {
                // Update user_bookings.csv
                ifstream file("user_bookings.csv");
                ofstream tempFile("temp.csv");
                string line;

                if (file.is_open() && tempFile.is_open()) {
                    while (getline(file, line)) {
                        stringstream ss(line);
                        string user, train, source, destination;
                        int seat;

                        getline(ss, user, ',');
                        getline(ss, train, ',');
                        ss >> seat;
                        ss.ignore();
                        getline(ss, source, ',');
                        getline(ss, destination, '\n');

                        if (!(user == username && train == trainID && seat == seatNumber)) {
                            tempFile << user << "," << train << "," << seat << "," << source << "," << destination << "\n";
                        }
                    }
                    file.close();
                    tempFile.close();

                    remove("user_bookings.csv");
                    rename("temp.csv", "user_bookings.csv");
                }
                cout << "Ticket cancelled successfully for " << username << ": Train " << trainID << ", Seat " << seatNumber << endl;
                return true;
            }
        }
    }
    cout << "Cancellation failed: Train not found or invalid seat number." << endl;
    return false;
}

// View User Bookings
void BookingSystem::viewUserBookings(const string &username) const {
    ifstream file("user_bookings.csv");
    string line;

    cout << "Bookings for user " << username << ":" << endl;
    bool found = false;

    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string user, trainID, source, destination;
            int seat;

            getline(ss, user, ',');
            getline(ss, trainID, ',');
            ss >> seat;
            ss.ignore();
            getline(ss, source, ',');
            getline(ss, destination, '\n');

            if (user == username) {
                cout << "Train ID: " << trainID << ", Seat: " << seat
                     << ", Source: " << source << ", Destination: " << destination << endl;
                found = true;
            }
        }
        file.close();
    }

    if (!found) {
        cout << "No bookings found for " << username << "." << endl;
    }
}
