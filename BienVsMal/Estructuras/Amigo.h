#ifndef AMIGO_H
#define AMIGO_H
#include <QString>
struct Amigo{
    int ID;
    QString nombre;
    QString apellido;
    QString pais;
    QString creencia;
    QString profesion;
    Amigo(int ID, QString nombre, QString apellido, QString pais, QString creencia, QString profesion){
        this->ID = ID;
        this->nombre = nombre;
        this->apellido = apellido;
        this->pais = pais;
        this->creencia = creencia;
        this->profesion = profesion;
    }
};
#endif // AMIGO_H
