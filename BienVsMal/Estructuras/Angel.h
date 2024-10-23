#ifndef ANGEL_H
#define ANGEL_H
#include <QString>
#include "../Human/persona.h"
#include "Estructuras/Reencarnacion.h"



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
        Persona* persona = new Persona();//Para simular todo el proceso de conseguir el humano desde bitacora de muerte TODO:
        Reencarnacion* reencarnacion = new Reencarnacion(persona,this);
        persona->reencarnaciones->insert(reencarnacion);
        //Ponerle nombre random y todo eso para la reencarnación. TODO:
        persona->pecadosTotales = 0;
        for (int i=0;i<7;i++){
            persona->pecados[i]/=2;
            persona->pecadosTotales += persona->pecados[i];
        }
        //TODO: preguntarle a arturo si hace falta rehacer el heap cuando se salva a alguien o como sirve el heap y eso?
        return nullptr;
    }
};

#endif // ANGEL_H
