#include "PetrolStation.h"


PetrolStation::PetrolStation(string stationName, string fuelType, int fuelVolume, Base *headObject) :
        Base(headObject, stationName) {
    this->fuelType = fuelType;
    this->fuelVolume = fuelVolume;
}

string PetrolStation::getType() {
    return fuelType;
}

int PetrolStation::getVolume() {
    return fuelVolume;
}

int PetrolStation::getQueueCountStation() {
    return queueCars.size();
}

int PetrolStation::getServicedCountStation() {
    return servicedCars.size();
}

void PetrolStation::addCarToQueue(Car *car) {
    queueCars.push_back(car);
}

void PetrolStation::reserveFuel(int carVolume) {
    fuelVolume -= carVolume;
}

string PetrolStation::refuelFirstCar(string info) {
    if (!queueCars.empty() || currentCar != nullptr) {
        if (!currentCar) {
            currentCar = queueCars[0];
            queueCars.erase(queueCars.begin());
        }

        currentCar->refuelFromStation();

        if (currentCar->getVolume() == 0) {
            servicedCars.push_back(currentCar->getObjectName());
            currentCar->removeFromSubObjects();
            delete currentCar;
            currentCar = nullptr;
        }
    }
    return "ok";
}

void PetrolStation::stationStatusSignal(string &info) {
    info = "Petrol filling station status " + getObjectName() + to_string(queueCars.size()) + " " + to_string(
            servicedCars.size());
}

//
string PetrolStation::stationStatusHandler(string info) {
    info = "Petrol filling station status " + getObjectName() + to_string(queueCars.size()) + " " + to_string(
            servicedCars.size()) + "\n";

    //22
    emitSignal(SIGNAL_D(PetrolStation::stationStatusSignal), info);
    //emitSignal("DisplayStationStatus", info);
    //22

    for (auto carStr: servicedCars)
        emitSignal(SIGNAL_D(PetrolStation::stationStatusSignal), (carStr + "\n"));
    //emitSignal("DisplayStationStatus", (carStr + "\n"));
    return "ok";
}

void PetrolStation::showStationStatus() {
    string info = "Petrol filling station status " + getObjectName() + " " + to_string(queueCars.size()) + " " +
                  to_string(servicedCars.size()) + "\n";

    // 34
    //emitSignal("DisplayStationStatus", info);
    emitSignal(SIGNAL_D(PetrolStation::printMessageSignal), info);
    // 34

    for (auto carStr: servicedCars)
        emitSignal(SIGNAL_D(PetrolStation::printMessageSignal), (carStr + "\n"));
}

void PetrolStation::printServicedCarsSignal(string &info) {
}

void PetrolStation::printMessageSignal(string &info) {
}
