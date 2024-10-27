#ifndef ANGEL_H
#define ANGEL_H
#include <QString>
#include "../Human/persona.h"
#include "Estructuras/Reencarnacion.h"
#include <QCoreApplication>
#include "Lector/lectorarchivos.h"

struct Angel{

    QString nombre;
    int version;
    int generacion; //nivel del arbol
    Persona* humanoSalvado;

    Angel* hijoIzquierdo;
    Angel* hijoCentro;
    Angel* hijoDerecho;

    QStringList listaNombres;
    QStringList listaApellidos;
    QStringList listaPais;
    QStringList listaCreencia;
    QStringList listaProfesion;
    QString baseDir = QCoreApplication::applicationDirPath();
    QString path = baseDir + "/Archivostxt/salvacion.txt";
    lectorArchivos* lector = new lectorArchivos();

    Angel(QString _nombre, int _version, int _generacion, QStringList _listaNombres,
          QStringList _listaApellidos, QStringList _listaPais, QStringList _listaCreencia, QStringList _listaProfesion){
        nombre = _nombre;
        version = _version;
        generacion = _generacion;
        hijoIzquierdo = hijoCentro = hijoDerecho = nullptr;
        listaNombres = _listaNombres;
        listaApellidos = _listaApellidos;
        listaPais = _listaPais;
        listaCreencia = _listaCreencia;
        listaProfesion = _listaProfesion;
        humanoSalvado = buscarHumanoASalvar();
    }

    Angel(QString _nombre, int _version, int _generacion, Persona* _humanoSalvado){ //para el caso de los primeros 2 niveles.
        nombre = "San " + _nombre;
        version = _version;
        generacion = _generacion;
        humanoSalvado = _humanoSalvado;
        hijoIzquierdo = hijoCentro = hijoDerecho = nullptr;
    }

    QString infoAngel(){
        return (nombre + " (" + QString::number(version) + ")\tG" + QString::number(generacion) + "\tID: " + QString::number(humanoSalvado->ID) + "\tR" + QString::number(humanoSalvado->reencarnaciones->size()));
    } //Para imrpimir el arbol
private:
    Persona* buscarHumanoASalvar(){
        QString paraBitacora;
        Persona* persona = new Persona();//TODO: buscar persona
        Reencarnacion* reencarnacion = new Reencarnacion(persona,this);
        paraBitacora = persona->timestampNacimiento + "\tHumano " + QString::number(persona->ID) + "\t" + persona->nombre + "\t" + persona->apellido + "\t" + persona->pais + "\t" + persona->profesion + "\t" + persona->creencia;
        persona->reencarnaciones->insert(reencarnacion);
        reencarnar(persona);


        paraBitacora += "\tSalvado por " + nombre + " (" + QString::number(version) + ")\tG" + QString::number(generacion);
        paraBitacora += "\tReencarnado como " + persona->nombre + "\t" + persona->apellido + "\t" + persona->pais + "\t" + persona->profesion + "\t" + persona->creencia;
        lector->appendTextToFile(path,paraBitacora);
        return persona;
    }

    void reencarnar(Persona* persona){
        persona->nombre = listaNombres[QRandomGenerator::global()->bounded(0, 10000)];
        persona->apellido = listaApellidos[QRandomGenerator::global()->bounded(0, 10000)];
        persona->pais = listaPais[QRandomGenerator::global()->bounded(0, 100)];
        persona->profesion = listaProfesion[QRandomGenerator::global()->bounded(0, 100)];
        persona->creencia = listaCreencia[QRandomGenerator::global()->bounded(0, 20)];

        persona->pecadosTotales = 0;
        for (int i=0;i<7;i++){
            persona->pecados[i]/=2;
            persona->pecadosTotales += persona->pecados[i];
        }
        persona->timestampNacimiento = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        persona->vivo = true;
    }
};

#endif // ANGEL_H
