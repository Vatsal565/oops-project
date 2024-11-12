#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Passenger
{
private:
    string name;
    int age;
    string gender;
    bool specialNeeds;
    string username;
    string password;

public:
    Passenger(const string &name, int age, const string &gender, const string &username, const string &password, bool specialNeeds = false) : name(name), age(age), gender(gender), username(username), password(password), specialNeeds(specialNeeds) {}

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

    // Authentication
    bool authenticate(const string &username, const string &password) {
        return this->username == username && this->password == password;
    }

    void saveToCSV() {
        ofstream file("passenger_data.csv", ios::app);
        if (file.is_open())
        {
            if(!userIsAlreadyThere(username, password)) {
                file << username << "," << password << "," << name << "," << age << "," << gender << "," << (specialNeeds ? "Yes" : "No") << endl;
            } else {
                cout << "Username Already Exists." << endl;
            }
            file.close();
        }
        else {
            cerr << "Unable to open CSV file for writing." << endl;
        }
    }

    bool userIsAlreadyThere(const string &username, const string &password) {
        ifstream file("passenger_data.csv");
        string line;

        bool found = false;

        if(file.is_open()) {
            while (getline(file, line))
            {
                stringstream ss(line);
                string user, pass, name, gender, specialNeedsStr;

                int age;
                bool specialNeeds;

                getline(ss, user, ',');
                getline(ss, pass, ',');
                getline(ss, name, ',');
                ss >> age;
                ss.ignore();
                getline(ss, gender, ',');
                getline(ss, specialNeedsStr, '\n');

                if (user == username && pass == password)
                {
                    found = true;
                    break;
                }
            }   
            file.close();
        }
        else {
            cerr << "Unable to open CSV file for reading." << endl;
        }
        return found;
    }

    static Passenger* loadFromCSV(const string &username, const string &password) {
        ifstream file("passenger_data.csv");
        string line;

        bool found = false;

        if(file.is_open()) {
            while (getline(file, line))
            {
                stringstream ss(line);
                string user, pass, name, gender, specialNeedsStr;

                int age;
                bool specialNeeds;

                getline(ss, user, ',');
                getline(ss, pass, ',');
                getline(ss, name, ',');
                ss >> age;
                ss.ignore();
                getline(ss, gender, ',');
                getline(ss, specialNeedsStr, '\n');

                if (user == username && pass == password)
                {
                    file.close();
                    return new Passenger(name, age, gender, user, pass, specialNeeds);
                }
            }   
            file.close();
        }
        else {
            cerr << "Unable to open CSV file for reading." << endl;
        }

        return nullptr;
    }
};
