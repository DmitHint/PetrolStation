#ifndef SYSTEM_H
#define SYSTEM_H

#include "Base.h"

#include "ControlPanel.h"
#include "PetrolStation.h"
#include "DisplayClass.h"
#include "OperatorClass.h"


#include <string>

using namespace std;

class System : public Base {
private:
public:
    System(Base *headObject);

    void buildTree();

    int execApp();

    TYPE_HANDLER getHandler(string methodName);
};

#endif
