#include "DisplayClass.h"

//==================================
DisplayClass::DisplayClass(Base *headObject) : Base(headObject, "DisplayObject") {}

string DisplayClass::printMessage(string message) {
    cout << message;
    return message;
}
