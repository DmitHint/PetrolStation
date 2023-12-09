#include "Base.h"

//===============================
Base::Base(Base *headObject, string objectName) {
    this->headObject = headObject;
    this->objectName = objectName;

    if (headObject != nullptr)
        headObject->subObjects.push_back(this); //�������� � ������ �����������
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
    // ��� ������� ��������� � �������� ������
    if (searchName == objectName)
        return this;

    // ���� ��� ������ ������� ����� �����������
    for (int i = 0; i < subObjects.size(); i++) {
        // ��� i-�� ������� ��������� � ��������
        if (searchName == subObjects[i]->objectName)
            return subObjects[i];
    }
    return nullptr;
}

void Base::printTreeWithState(int step) {
    string indent;
    for (int i = 0; i < step; i++)
        indent += "    ";

    if (headObject == nullptr) // �������� ������
        cout << objectName << ((objectState != 0) ? " is ready" : " is not ready");

    // ����� �� ����������� �������� � �� ���������
    for (int i = 0; i < subObjects.size(); i++) {
        cout << "\n" << indent << subObjects[i]->objectName <<
             ((subObjects[i]->objectState != 0) ? " is ready" : " is not ready");
        // ����� �� ����������� �������� � �� ��������� i-�� �������
        subObjects[i]->printTreeWithState(step + 1);
    }
}

bool Base::setObjectHead(Base *newHead) {
    if (newHead == nullptr) // ��� ������� � �������� ���������
        return false;

    // ������� ������� ������ �� ������� ����������� � ��������� �������
    for (int i = 0; i < headObject->subObjects.size(); i++) {
        if (headObject->subObjects[i]->objectName == objectName) {
            headObject->subObjects.erase(headObject->subObjects.begin() + i);
            break;
        }
    }
    headObject = newHead;
    // �������� ������� ������ � ������ ����������� �������� ������ ���������
    headObject->subObjects.push_back(this);
    return true;
}


//==================================
void Base::removeFromSubObjects() {
    // ���� ��� ������ � �������� ������� � ������� �����������
    for (auto it = headObject->subObjects.begin(); it != headObject->subObjects.end(); ++it) {
        if ((*it)->objectName == objectName) {
            headObject->subObjects.erase(it);
            break;
        }
    }
    // ����� ��� �������� ����������� �������� � ����������
    removeNode();
}

//==================================
void Base::removeNode() {
    // ���� ��� �������� ���� ����������� ��������
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
    (this->*signal)(info); // ����� ������ �������
    for (int i = 0; i < connections.size(); i++) // ���� �� ���� ������������
    {
        if (connections[i]->signal == signal) // ����������� ����������� �����������
        {
            p_handler = connections[i]->handler;
            targetObject = connections[i]->targetObject;

            responseInfo = (targetObject->*p_handler)(info); // ����� ������ �����������
        }
    }
    return responseInfo;
}

void Base::setConnection(TYPE_SIGNAL signal, Base *targetObject, TYPE_HANDLER handler) {
    // ���� ��� ���������� ���������� ������������ �����
    for (int i = 0; i < connections.size(); i++) {
        if (connections[i]->signal == signal &&
            connections[i]->targetObject == targetObject &&
            connections[i]->handler == handler) {
            return;
        }
    }
    connection_SH *newConnection = new connection_SH;
    // �������� ������� ��������� ��� �������� ���������� � ����� �����
    newConnection->signal = signal;
    newConnection->targetObject = targetObject;
    newConnection->handler = handler;
    connections.push_back(newConnection); // ���������� ����� �����
}

void Base::deleteConnection(TYPE_SIGNAL signal, Base *targetObject, TYPE_HANDLER handler) {
    // ���� ��� ������ ����� ��� ��������
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
