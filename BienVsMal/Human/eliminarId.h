#ifndef ELIMINARID_H
#define ELIMINARID_H
#include "Estructuras/arbolBinario.h"


void EliminarId(ArbolBinario* arbolBinario, int persona){
    NodoOrdenado<Persona*>* candidato = arbolBinario->buscarNodoEnListaConID(persona);
    if(candidato == nullptr){
        qDebug() << "El candidato no existe";
    } else {
        qDebug() << "El candidato existe";
        candidato->data->vivo = false;
    }
}

#endif // ELIMINARID_H
