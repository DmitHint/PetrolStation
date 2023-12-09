#include "System.h"


System::System(Base *headObject) : Base(headObject, "System") {
};

void System::buildTree() {
    // Создание дерева объектов
    Base *rootObject = this;

    // Создание объекта считывания строк
    Base *operatorObject = new OperatorClass(rootObject);

    // Создание объекта пульта управления
    ControlPanel *controlPanel = new ControlPanel(rootObject);

    // Создание объекта для вывода на экран
    Base *displayObject = new DisplayClass(rootObject);

    // Создание необходимых связей
    operatorObject->setConnection(
            SIGNAL_D(OperatorClass::inputStationsSignal), controlPanel, HANDLER_D(ControlPanel::setStationInfo));
    operatorObject->setConnection(
            SIGNAL_D(OperatorClass::inputCommandSignal), controlPanel, getHandler("commandHandler"));


    controlPanel->setConnection(SIGNAL_D(ControlPanel::printMessageSignal), displayObject, getHandler("printMessage"));


    // Ввод информации о бензоколонках
    string inputOperatorResponse = operatorObject->emitSignal(SIGNAL_D(OperatorClass::inputStationsSignal));
    while (inputOperatorResponse != "End of information about petrol filling stations")
        inputOperatorResponse = operatorObject->emitSignal(SIGNAL_D(OperatorClass::inputStationsSignal));

    controlPanel->setStationsDisplayConnection(SIGNAL_D(PetrolStation::printMessageSignal), displayObject,
                                               getHandler("printMessage"));
}

int System::execApp() {
    Base *RootObject = this;
    Base *operatorObject = findObjectByName(RootObject, "Operator");

    cout << "Ready to work\n";

    string inputOperatorResponse = operatorObject->emitSignal(SIGNAL_D(OperatorClass::inputCommandSignal));
    while (inputOperatorResponse != "SHOWTREE" && inputOperatorResponse != "Turn off the system")
        inputOperatorResponse = operatorObject->emitSignal(SIGNAL_D(OperatorClass::inputCommandSignal));

    return 0;
}

TYPE_HANDLER System::getHandler(string methodName) {
    if (methodName == "inputHandler")
        return HANDLER_D(OperatorClass::inputHandler);
    if (methodName == "commandHandler")
        return HANDLER_D(ControlPanel::commandHandler);
    if (methodName == "setStationInfo")
        return HANDLER_D(ControlPanel::commandHandler);
    if (methodName == "commandHandler")
        return HANDLER_D(ControlPanel::commandHandler);
    if (methodName == "printMessage")
        return HANDLER_D(DisplayClass::printMessage);

    return nullptr;
}
