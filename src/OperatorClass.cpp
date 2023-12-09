#include "OperatorClass.h"

OperatorClass::OperatorClass(Base *headObject) : Base(headObject, "Operator") {
}

void OperatorClass::inputStationsSignal(string &info) {
    getline(cin, info);
}

void OperatorClass::inputCommandSignal(string &info) {
    getline(cin, info);
}

string OperatorClass::inputHandler(string info) {
    return info;
}
