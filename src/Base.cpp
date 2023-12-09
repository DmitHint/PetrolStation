#include "Base.h"

//===============================
Base::Base(Base *headObject, string objectName) {
    this->headObject = headObject;
    this->objectName = objectName;

    if (headObject != nullptr)
        headObject->subObjects.push_back(this); //добавить в вектор подчиненных
}

string Base::getObjectName() {
    return objectName;
}

Base *Base::getObjectHead() {
    return headObject;
}

void Base::setObjectName(string objectName) {
    this->objectName = objectName;
}

Base *Base::findObjectByName(Base *headObject, string searchName) {
    // имя объекта совпадает с заданным именем
    if (searchName == objectName)
        return this;

    // цикл для поиска объекта среди подчиненных
    for (int i = 0; i < subObjects.size(); i++) {
        // имя i-го объекта совпадает с заданным
        if (searchName == subObjects[i]->objectName)
            return subObjects[i];
    }
    return nullptr;
}

void Base::printTreeWithState(int step) {
    string indent;
    for (int i = 0; i < step; i++)
        indent += "    ";

    if (headObject == nullptr) // корневой объект
        cout << objectName << ((objectState != 0) ? " is ready" : " is not ready");

    // вывод на подчиненных объектов и их состояний
    for (int i = 0; i < subObjects.size(); i++) {
        cout << "\n" << indent << subObjects[i]->objectName <<
             ((subObjects[i]->objectState != 0) ? " is ready" : " is not ready");
        // вывод на подчиненных объектов и их состояний i-го объекта
        subObjects[i]->printTreeWithState(step + 1);
    }
}

bool Base::setObjectHead(Base *newHead) {
    if (newHead == nullptr) // нет объекта в качестве головного
        return false;

    // удалить текущий объект из вектора подчиненных у головного объекта
    for (int i = 0; i < headObject->subObjects.size(); i++) {
        if (headObject->subObjects[i]->objectName == objectName) {
            headObject->subObjects.erase(headObject->subObjects.begin() + i);
            break;
        }
    }
    headObject = newHead;
    // добавить текущий объект в вектор подчиненных объектов нового головного
    headObject->subObjects.push_back(this);
    return true;
}


//==================================
void Base::removeFromSubObjects() {
    // цикл для поиска и удаления объекта в векторе подчиненных
    for (auto it = headObject->subObjects.begin(); it != headObject->subObjects.end(); ++it) {
        if ((*it)->objectName == objectName) {
            headObject->subObjects.erase(it);
            break;
        }
    }
    // метод для удаления подчиненных объектов у удаляемого
    removeNode();
}

//==================================
void Base::removeNode() {
    // цикл для удаления всех подчиненных объектов
    for (int i = 0; i < subObjects.size(); i++) {
        subObjects[i]->removeNode();
        delete subObjects[i];
    }
}

string Base::emitSignal(TYPE_SIGNAL signal, string info) {
    string responseInfo = "null";
    TYPE_HANDLER p_handler;
    Base *targetObject;
    //-----------------------------------------------------
    (this->*signal)(info); // вызов метода сигнала
    for (int i = 0; i < connections.size(); i++) // цикл по всем обработчикам
    {
        if (connections[i]->signal == signal) // определение допустимого обработчика
        {
            p_handler = connections[i]->handler;
            targetObject = connections[i]->targetObject;

            responseInfo = (targetObject->*p_handler)(info); // вызов метода обработчика
        }
    }
    return responseInfo;
}

void Base::setConnection(TYPE_SIGNAL signal, Base *targetObject, TYPE_HANDLER handler) {
    // Цикл для исключения повторного установления связи
    for (int i = 0; i < connections.size(); i++) {
        if (connections[i]->signal == signal &&
            connections[i]->targetObject == targetObject &&
            connections[i]->handler == handler) {
            return;
        }
    }
    connection_SH *newConnection = new connection_SH;
    // создание объекта структуры для хранения информации о новой связи
    newConnection->signal = signal;
    newConnection->targetObject = targetObject;
    newConnection->handler = handler;
    connections.push_back(newConnection); // добавление новой связи
}

void Base::deleteConnection(TYPE_SIGNAL signal, Base *targetObject, TYPE_HANDLER handler) {
    // Цикл для поиска связи для удаления
    for (int i = 0; i < connections.size(); i++) {
        if (connections[i]->signal == signal &&
            connections[i]->targetObject == targetObject &&
            connections[i]->handler == handler) {
            delete connections[i];
            if (i == connections.size())
                connections.pop_back();
            else
                connections.erase(connections.begin() + i, connections.begin() + i + 1);

            break;
        }
    }
}
