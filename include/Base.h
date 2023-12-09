#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Base;

typedef void (Base::* TYPE_SIGNAL)(string &str); // ��������� �� ����� ������� �������
typedef string (Base::* TYPE_HANDLER)(string str); // ��������� �� ����� ����������� �������


#define SIGNAL_D(signal_f) (( TYPE_SIGNAL ) ( & signal_f ))    //������������������� ����������������
//��� ��������� ��������� �� ����� ������� �������

#define HANDLER_D(handler_f) (( TYPE_HANDLER ) ( & handler_f ))    //������������������� ����������������
//��� ��������� ��������� �� ����� ������� �����������


struct connection_SH // ��������� ������� ����� �����
{
    //string signalName;
    TYPE_SIGNAL signal; // ��������� �� ����� �������
    Base *targetObject; // ��������� �� ������� ������
    TYPE_HANDLER handler; // ��������� �� ����� �����������
};

class Base {
private:
    Base *headObject;
    string objectName;
    int objectState = 1;
    vector<Base *> subObjects; // ������ ���������� �� ������� ������ Base
    vector<connection_SH *> connections;

public:
    Base(Base *headObject, // ������������������� �����������, ��� �������� �������
         string objectName = "Base"); // ���������� ��� ��������� ����� � ������� � ������ ��������

    bool setObjectHead(Base *newHead);

    void removeFromSubObjects();

    void removeNode();

    string getObjectName();

    Base *getObjectHead();

    void setObjectName(string objectName);

    void printTreeWithState(int step);

    Base *findObjectByName(Base *headObject, string searchName);

    void deleteConnection(TYPE_SIGNAL signal, Base *targetObject, TYPE_HANDLER handler);

    string emitSignal(TYPE_SIGNAL signal, string info = "null");

    void setConnection(TYPE_SIGNAL signal, Base *targetObject, TYPE_HANDLER handler);
};

#endif
