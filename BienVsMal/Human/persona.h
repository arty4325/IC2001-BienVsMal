#ifndef PERSONA_H
#define PERSONA_H

#include <QString>
#include "../Estructuras/listaOrdenada.h"

struct Persona{
    int ID;
    QString nombre;
    QString apellido;
    QString pais;
    QString creencia;
    QString profesion;
    QString timestampNacimiento;
    int pecados[7]; //Lujuria, Gula, Avaricia, Pereza, Ira, Envidia, Soberbia.
    ListaOrdenada<Persona*>* amigos;
    bool vivo;

    Persona(int ID, QString nombre, QString apellido, QString pais, QString creencia, QString profesion, QString timestampNacimiento){
        this->ID = ID;
        this->nombre = nombre;
        this->apellido = apellido;
        this->creencia = creencia;
        this->profesion = profesion;
        this->timestampNacimiento = timestampNacimiento;
        for(int i=0;i<7;i++){
            this->pecados[i] = 0;
        }
        this->amigos = new ListaOrdenada<Persona*>;
    }
};






#endif // PERSONA_H
