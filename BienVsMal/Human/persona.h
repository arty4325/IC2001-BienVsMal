#ifndef PERSONA_H
#define PERSONA_H

#include <QString>
#include "Estructuras/listaOrdenada.h"
#include "Estructuras/Amigo.h"

struct Reencarnacion;

struct Persona{
    int ID;
    QString nombre;
    QString apellido;
    QString pais;
    QString creencia;
    QString profesion;
    QString timestampNacimiento;
    int pecados[7]; //Lujuria, Gula, Avaricia, Pereza, Ira, Envidia, Soberbia.
    int pecadosTotales;
    ListaOrdenada<Amigo*>* amigos;
    ListaOrdenada<Reencarnacion*>* reencarnaciones;
    bool vivo;

    Persona(int ID, QString nombre, QString apellido, QString pais, QString creencia, QString profesion, QString timestampNacimiento){
        this->ID = ID;
        this->nombre = nombre;
        this->apellido = apellido;
        this->pais = pais;
        this->creencia = creencia;
        this->profesion = profesion;
        this->timestampNacimiento = timestampNacimiento;
        for(int i=0;i<7;i++){
            this->pecados[i] = 0;
        }
        pecadosTotales = 0;
        this->amigos = new ListaOrdenada<Amigo*>;
        this->reencarnaciones = new ListaOrdenada<Reencarnacion*>;
        this->vivo = true;
    }

    Persona(){

    }
};






#endif // PERSONA_H
