#ifndef CONTROL_PANEL_H
#define CONTROL_PANEL_H

#include <vector>
#include <string>

#include "Base.h"

#include "PetrolStation.h"
#include "Car.h"

using namespace std;

class ControlPanel : public Base {
private:
    Car *carInQueue;
    vector<PetrolStation *> stations;
    int servicedCount;

public:
    ControlPanel(Base *headObject);

    void commandSignal(string &command);

    Car *getCarFromParameters(string carInfo);

    string findStationForCar(string carInfo);

    //
    void stationStatusSignal(string &info);

    void printMessageSignal(string &info);

    void refuelCarsSignal(string &info);

    void systemStatusSignal(string &info);

    //


    PetrolStation *findStationByName(string searchName);

    int getQueueCount();

    int getServicedCount();

    string commandHandler(string command);

    string setStationInfo(string info);

    //
    //void setStationsDisplayConnection(string signalName, TYPE_SIGNAL signalStation, Base* displayObject,
    //                                  TYPE_HANDLER printMessage);

    //
    void setStationsDisplayConnection(TYPE_SIGNAL signalStation, Base *displayObject, TYPE_HANDLER printMessage);
};

#endif
