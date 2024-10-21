#ifndef GENERARPANDEMIA_H
#define GENERARPANDEMIA_H
#include "persona.h"
#include "Estructuras/arbolBinario.h"
#include "Estructuras/listaOrdenada.h"

void GenerarPandemia(ListaOrdenada<Persona*>* listaHumanos, double porcentaje){
    // Quiero obtener la cantidad de humanos que quiero eliminar
    int cantidadEliminar = (listaHumanos->size())*porcentaje;
    int cantidadEliminados = 0;
    qDebug() << cantidadEliminar << " estoy ejecutando pandemia";
    while(cantidadEliminados <= cantidadEliminar){
        int idRand = QRandomGenerator::global()->bounded(0, listaHumanos->size());
        Persona* personaCandidata;
        personaCandidata = listaHumanos->ver(idRand);
        if(personaCandidata->vivo == true){
            qDebug() << cantidadEliminados;
            cantidadEliminados += 1;
            personaCandidata -> vivo = false;
        }


    }
}


#endif // GENERARPANDEMIA_H
