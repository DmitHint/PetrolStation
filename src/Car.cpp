#include "Car.h"

Car::Car(string carNum, string fuelType, int fuelVolume, Base* headObject): Base(headObject, carNum)
{
	this->fuelType = fuelType;
	this->fuelVolume = fuelVolume;
}

string Car::getType()
{
	return fuelType;
}

int Car::getVolume()
{
	return fuelVolume;
}

void Car::refuelFromStation()
{
	fuelVolume-=10;
}
void Car::commandSignal(string& info)
{}

