#ifndef ANGEL_H
#define ANGEL_H
#include <QString>
#include "../Human/persona.h"

struct Angel{
    QString nombre;
    int version;
    int generacion; //nivel del arbol
    Persona* humanoSalvado;

    Angel* hijoIzquierdo;
    Angel* hijoCentro;
    Angel* hijoDerecho;

    Angel(QString _nombre, int _version, int _generacion){
        nombre = _nombre;
        version = _version;
        generacion = _generacion;
        humanoSalvado = buscarHumanoASalvar();
        hijoIzquierdo = hijoCentro = hijoDerecho = nullptr;
    }

    Angel(QString _nombre, int _version, int _generacion, Persona* _humanoSalvado){ //para el caso de los primeros 2 niveles.
        nombre = _nombre;
        version = _version;
        generacion = _generacion;
        humanoSalvado = _humanoSalvado;
        hijoIzquierdo = hijoCentro = hijoDerecho = nullptr;
    }

private:
    Persona* buscarHumanoASalvar(){
        //TODO
        return nullptr;
    }
};

#endif // ANGEL_H
