#ifndef NODOHASH_H
#define NODOHASH_H
#include "Human/persona.h"
#include <QString>

struct NodoHash{
    QString key;
    Persona* data;
    NodoHash* next;

    NodoHash(QString _key,Persona* _data){
        key = _key;
        data = _data;
        next = nullptr;
    }
};

#endif // NODOHASH_H
