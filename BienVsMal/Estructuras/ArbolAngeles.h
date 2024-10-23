#ifndef ARBOLANGELES_H
#define ARBOLANGELES_H
#include "Angel.h"
#include <QString>

struct ArbolAngeles{
    Angel* raiz;
    QString nombres[10] = {"Miguel", "Nuriel", "Aniel", "Rafael", "Gabriel","Shamsiel", "Raguel", "Uriel", "Azrael", "Sariel"};
    int versionesNombres[10];

    ArbolAngeles(){
        raiz = new Angel("Dios",1, 1,nullptr);
        raiz->hijoIzquierdo = new Angel("Serafines",1, 2,nullptr);
        raiz->hijoCentro = new Angel("Querubines",1, 2,nullptr);
        raiz->hijoDerecho = new Angel("Tronos",1, 2,nullptr);
    }

    void salvacion(){ //crea un nuevo árbol de ángeles salvadores
        for(int i=0;i<10;i++){
            versionesNombres[i] = 0;
        }
        salvacion(raiz,2);
    }

private:
    void salvacion(Angel* nodo, int generacion){
        if(nodo == nullptr){ //Condicion de parada
            return;
        }

        if(nodo->hijoIzquierdo == nullptr && nodo->hijoCentro == nullptr && nodo->hijoDerecho == nullptr){ // Si ya llega a hoja / el último nivel
            int nombreIzquierdo = QRandomGenerator::global()->bounded(0, 10); //genera numero entre 0 y 9
            nodo->hijoIzquierdo = new Angel(nombres[nombreIzquierdo],versionesNombres[nombreIzquierdo]++,generacion);

            int nombreCentro = QRandomGenerator::global()->bounded(0, 10);
            nodo->hijoCentro = new Angel(nombres[nombreCentro], versionesNombres[nombreCentro]++, generacion);

            int nombreDerecho = QRandomGenerator::global()->bounded(0, 10);
            nodo->hijoDerecho = new Angel(nombres[nombreDerecho], versionesNombres[nombreDerecho]++, generacion);
        }

        salvacion(nodo->hijoIzquierdo,generacion+1);
        salvacion(nodo->hijoCentro,generacion+1);
        salvacion(nodo->hijoDerecho,generacion+1);
    }







};

#endif // ARBOLANGELES_H
