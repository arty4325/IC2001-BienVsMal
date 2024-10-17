#ifndef NODOAB_H
#define NODOAB_H
#include "NodoOrdenado.h"
struct NodoAB{
    int ID;
    NodoOrdenado<int>* nodoPuntero;
    NodoAB* hijoIzquierdo;
    NodoAB* hijoDerecho;

    NodoAB(NodoOrdenado<int>* _nodoPuntero){
        ID = _nodoPuntero->data;
        nodoPuntero = _nodoPuntero;
        hijoIzquierdo = hijoDerecho = nullptr;
    }
};

#endif // NODOAB_H
