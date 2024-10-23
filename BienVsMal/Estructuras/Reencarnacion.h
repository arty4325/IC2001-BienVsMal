#ifndef REENCARNACION_H
#define REENCARNACION_H

#include <QString>

struct Angel; //Está incluido el archivo de Angel en el main, entonces solo con avisar que hay un struct ángel quita el error que habia. Sino habia como recursividad circular y no se que.

struct Reencarnacion{
    int ID;
    QString nombre;
    QString apellido;
    QString pais;
    QString creencia;
    QString profesion;
    Angel* angelSalvador;
    int numeroDeReencarnacion;
};

#endif // REENCARNACION_H
