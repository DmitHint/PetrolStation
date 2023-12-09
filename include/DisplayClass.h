#ifndef DISPLAYCLASS_H
#define DISPLAYCLASS_H

#include "Base.h"

class DisplayClass : public Base {
public:
    DisplayClass(Base *headObject);

    string printMessage(string message);
};

#endif
