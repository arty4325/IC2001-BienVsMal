#ifndef NODOAB_H
#define NODOAB_H
#include "NodoOrdenado.h"
#include "Human/persona.h"
struct NodoAB{
    int ID;
    NodoOrdenado<Persona*>* nodoPuntero;
    NodoAB* hijoIzquierdo;
    NodoAB* hijoDerecho;

    NodoAB(NodoOrdenado<Persona*>* _nodoPuntero){
        ID = _nodoPuntero->data->ID;
        nodoPuntero = _nodoPuntero;
        hijoIzquierdo = hijoDerecho = nullptr;
    }
};

#endif // NODOAB_H
