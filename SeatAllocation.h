#ifndef SEATALLOCATION_H
#define SEATALLOCATION_H

#include "Train.h"
#include <string>
using namespace std;

class SeatAllocation {
public:
    static int allocatePrioritySeat(Train &train, const string &passengerName, int age, const string &gender);
};

#endif // SEATALLOCATION_H
