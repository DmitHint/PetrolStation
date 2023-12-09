#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Base;

typedef void (Base::* TYPE_SIGNAL)(string &str); // Указатель на метод сигнала объекта
typedef string (Base::* TYPE_HANDLER)(string str); // Указатель на метод обработчика объекта


#define SIGNAL_D(signal_f) (( TYPE_SIGNAL ) ( & signal_f ))    //параметризированное макроопределение
//для получения указателя на метод сигнала объекта

#define HANDLER_D(handler_f) (( TYPE_HANDLER ) ( & handler_f ))    //параметризированное макроопределение
//для получения указателя на метод сигнала обработчика


struct connection_SH // Структура задания одной связи
{
    //string signalName;
    TYPE_SIGNAL signal; // Указатель на метод сигнала
    Base *targetObject; // Указатель на целевой объект
    TYPE_HANDLER handler; // Указатель на метод обработчика
};

class Base {
private:
    Base *headObject;
    string objectName;
    int objectState = 1;
    vector<Base *> subObjects; // вектор указателей на объекты класса Base
    vector<connection_SH *> connections;

public:
    Base(Base *headObject, // параметризированный конструктор, при создании объекта
         string objectName = "Base"); // присвоение ему заданного имени и вставка в дерево иерархии

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
