#ifndef PETROL_STATION_H
#define PETROL_STATION_H


#include "Base.h"
#include "Car.h"

class PetrolStation : public Base {
private:
    string fuelType;
    int fuelVolume;

    Car *currentCar = nullptr;
    vector<Car *> queueCars;
    vector<string> servicedCars;
public:
    PetrolStation(string stationName, string fuelType, int fuelVolume, Base *headObject);

    string getType();

    int getVolume();

    int getQueueCountStation();

    int getServicedCountStation();

    void addCarToQueue(Car *car);

    void stationStatusSignal(string &info);

    void printMessageSignal(string &info);

    void printServicedCarsSignal(string &str);

    string stationStatusHandler(string info);

    string refuelFirstCar(string info);

    void reserveFuel(int carVolume);

    void showStationStatus();
};

#endif
