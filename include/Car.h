#ifndef CAR_H
#define CAR_H

#include <string>

#include "Base.h"

using namespace std;

class Car : public Base {
private:
    string fuelType;
    int fuelVolume;
public:
    Car(string carNum, string fuelType, int fuelVolume, Base *headObject);

    void refuelFromStation();

    void commandSignal(string &info);

    string getType();

    int getVolume();
};

#endif
