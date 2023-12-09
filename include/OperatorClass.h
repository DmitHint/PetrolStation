#ifndef OPERATORCLASS_H
#define OPERATORCLASS_H

#include "Base.h"

#include <iostream>
#include <vector>
#include <string>


using namespace std;

class OperatorClass : public Base {
public:
    OperatorClass(Base *headObject);

    void inputStationsSignal(string &info);

    void inputCommandSignal(string &info);

    string inputHandler(string info);
};

#endif
