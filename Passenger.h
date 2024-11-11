#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
using namespace std;

class Passenger {
private:
    string name;
    int age;
    string gender;
    bool specialNeeds;

public:
    Passenger(const string &n, int age, const string &gender, bool specialNeeds = false);

    string getName() const;
    int getAge() const;
    string getGender() const;
    bool hasSpecialNeeds() const;

    void displayInfo() const;
};

#endif // PASSENGER_H