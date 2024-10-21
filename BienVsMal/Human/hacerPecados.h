#ifndef HACERPECADOS_H
#define HACERPECADOS_H
#include "persona.h"

void HacerPecados(ListaOrdenada<Persona*>* listaHumanos){
    for(int i = 0; i < listaHumanos->size(); i++){
        Persona* persona = listaHumanos->ver(i);
        int cantLujuria = QRandomGenerator::global()->bounded(0, 99) + persona->pecados[0];
        int cantGula = QRandomGenerator::global()->bounded(0, 99) + persona->pecados[1];
        int cantAvaricia = QRandomGenerator::global()->bounded(0, 99)+ persona->pecados[2];
        int cantPereza = QRandomGenerator::global()->bounded(0, 99)+ persona->pecados[3];
        int cantIra = QRandomGenerator::global()->bounded(0, 99)+ persona->pecados[4];
        int cantEnvidia = QRandomGenerator::global()->bounded(0, 99)+ persona->pecados[5];
        int cantSobervia = QRandomGenerator::global()->bounded(0, 99)+ persona->pecados[6];

        persona->pecados[0] = cantLujuria;
        persona->pecados[1] = cantGula;
        persona->pecados[2] = cantAvaricia;
        persona->pecados[3] = cantPereza;
        persona->pecados[4] = cantIra;
        persona->pecados[5] = cantEnvidia;
        persona->pecados[6] = cantSobervia;
        persona->pecadosTotales += cantLujuria + cantSobervia + cantAvaricia + cantPereza + cantIra + cantEnvidia + cantSobervia;
    }
}

#endif // HACERPECADOS_H
