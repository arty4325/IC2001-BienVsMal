#ifndef REENCARNACION_H
#define REENCARNACION_H

#include <QString>
#include "Human/persona.h"
#include <QDateTime>
struct Angel; //Está incluido el archivo de Angel en el main, entonces solo con avisar que hay un struct ángel quita el error que habia. Sino habia como recursividad circular y no se que.
struct Persona;

struct Reencarnacion{
    int ID;
    QString nombre;
    QString apellido;
    QString pais;
    QString creencia;
    QString profesion;
    Angel* angelSalvador;
    int numeroDeReencarnacion;
    QString timestampNacimiento;

    Reencarnacion(Persona* persona, Angel* angel){
        ID = persona->ID;
        nombre = persona->nombre;
        apellido = persona->apellido;
        pais = persona->pais;
        creencia = persona->creencia;
        profesion = persona->profesion;
        angelSalvador = angel;
        numeroDeReencarnacion = persona->reencarnaciones->size() + 1;
        timestampNacimiento = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    }

    QString infoReencarnacion(){
        return QString::number(ID) + " | " + nombre + " " + apellido + " | " + pais + " | " + creencia + " | " + profesion + " | Número de vida: " + QString::number(numeroDeReencarnacion);
    }
};

#endif // REENCARNACION_H
