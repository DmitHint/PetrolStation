#include "ControlPanel.h"

#include "OperatorClass.h"

ControlPanel::ControlPanel(Base *headObject) : Base(headObject, "ControlPanel") {
};


string ControlPanel::commandHandler(string commandStr) {
    string command = commandStr;
    string commandSubstr = command.substr(0, 16);
    string displayCommand;
    if (carInQueue) {
        string findStationResponse = carInQueue->emitSignal(SIGNAL_D(Car::commandSignal));
        if (findStationResponse.substr(0, 17) == "Denial of service") {
            emitSignal(SIGNAL_D(ControlPanel::printMessageSignal), findStationResponse + "\n");
        }
    }
    if (command == "SHOWTREE") {
        getObjectHead()->printTreeWithState(1);
    } else if (command == "Turn off the system") {
        emitSignal(SIGNAL_D(ControlPanel::printMessageSignal), command);
    } else if (commandSubstr == "Fill up the tank") {
        command.erase(0, 16 + 1);
        Car *car = getCarFromParameters(command);
        carInQueue = car;
        carInQueue->setConnection(SIGNAL_D(Car::commandSignal), this,
                                  HANDLER_D(ControlPanel::findStationForCar));
    } else if (commandSubstr == "Display the petr") {
        displayCommand = "Display the petrol filling station status";
        command.erase(0, displayCommand.size() + 1);
        PetrolStation *station = findStationByName(command);
        station->showStationStatus();
    } else if (command.substr(0, 16) == "Display the syst") {
        for (auto station: stations)
            emitSignal(SIGNAL_D(ControlPanel::printMessageSignal), "Petrol station " + station->getObjectName() + " " +
                                                                   to_string(station->getVolume()) + " " +
                                                                   to_string(station->getQueueCountStation()) + "\n");

        emitSignal(SIGNAL_D(ControlPanel::printMessageSignal),
                   "Operator " + to_string(getServicedCount()) + " " + to_string(getQueueCount()) + "\n");
    }

    // Заправить автомобили
    emitSignal(SIGNAL_D(ControlPanel::refuelCarsSignal));

    return commandStr;
};


int ControlPanel::getQueueCount() {
    int cnt = 0;
    for (auto station: stations)
        cnt += station->getQueueCountStation();

    return cnt;
}

int ControlPanel::getServicedCount() {
    int cnt = 0;

    for (auto station: stations)
        cnt += station->getServicedCountStation();

    return cnt;
}

PetrolStation *ControlPanel::findStationByName(string searchName) {
    // цикл для поиска объекта среди подчиненных
    for (auto station: stations)
        if (searchName == station->getObjectName())
            return station;
    return nullptr;
}

void ControlPanel::setStationsDisplayConnection(TYPE_SIGNAL signalStation, Base *displayObject,
                                                TYPE_HANDLER printMessage) {
    for (auto station: stations) {
        station->setConnection(signalStation, displayObject, printMessage);
    }
}

string ControlPanel::setStationInfo(string info) {
    if (info == "End of information about petrol filling stations")
        return "End of information about petrol filling stations";

    string stationName;
    string fuelType;
    int fuelVolume;

    size_t pos = info.find(" ");
    string tempInfo = info;
    stationName = tempInfo.erase(pos, tempInfo.size());
    info.erase(0, pos + 1);

    pos = info.find(" ");
    tempInfo = info;
    fuelType = tempInfo.erase(pos, tempInfo.size());
    info.erase(0, pos + 1);

    fuelVolume = stoi(info);

    PetrolStation *newStation = new PetrolStation(stationName, fuelType, fuelVolume, this);

    setConnection(SIGNAL_D(ControlPanel::stationStatusSignal), newStation,
                  HANDLER_D(PetrolStation::stationStatusHandler));
    setConnection(SIGNAL_D(ControlPanel::refuelCarsSignal), newStation,
                  HANDLER_D(PetrolStation::refuelFirstCar));

    stations.push_back(newStation);

    return "ok";
}

vector<string> getCarParametersFromInfo(string carInfo) {
    vector<string> parameters;

    size_t pos = carInfo.find(" ");
    string tempInfo = carInfo;
    parameters.push_back(tempInfo.erase(pos, tempInfo.size()));
    carInfo.erase(0, pos + 1);

    pos = carInfo.find(" ");
    tempInfo = carInfo;
    parameters.push_back(tempInfo.erase(pos, tempInfo.size()));
    carInfo.erase(0, pos + 1);
    parameters.push_back(carInfo);

    return parameters;
}

Car *ControlPanel::getCarFromParameters(string carInfo) {
    vector<string> parameters = getCarParametersFromInfo(carInfo);

    Car *newCar = new Car(parameters[0], parameters[1], stoi(parameters[2]), this);

    return newCar;
}

string ControlPanel::findStationForCar(string carInfo) {
    Car *car = carInQueue;
    carInQueue = nullptr;
    car->deleteConnection(SIGNAL_D(Car::commandSignal), this, HANDLER_D(ControlPanel::findStationForCar));
    for (auto station: stations) {
        if (station->getVolume() >= car->getVolume() && station->getType() == car->getType()) {
            car->setObjectHead(station);
            station->addCarToQueue(car);
            station->reserveFuel(car->getVolume());
            return "ok";
        }
    }
    string name = car->getObjectName();
    car->removeFromSubObjects();
    delete car;
    return ("Denial of service " + name);
}

void ControlPanel::stationStatusSignal(string &info) {
}

void ControlPanel::printMessageSignal(string &info) {
}

void ControlPanel::refuelCarsSignal(string &info) {
}

void ControlPanel::commandSignal(string &commandStr) {
}

void ControlPanel::systemStatusSignal(string &info) {
}
