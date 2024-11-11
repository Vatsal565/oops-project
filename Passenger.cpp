#include <iostream>
using namespace std;

class Passenger
{
private:
    string name;
    int age;
    string gender;
    bool specialNeeds;

public:
    Passenger(const string &name, int age, const string &gender, bool specialNeeds = false) : name(name), age(age), gender(gender), specialNeeds(specialNeeds) {}

    string getName()
    {
        return name;
    };
    int getAge()
    {
        return age;
    };
    string getGender()
    {
        return gender;
    };
    bool hasSpecialNeeds()
    {
        return specialNeeds;
    };

    void displayInfo()
    {
        cout << "Passenger Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender << endl;
        cout << "Special Needs: " << (specialNeeds ? "Yes" : "No") << endl;
    };
};
