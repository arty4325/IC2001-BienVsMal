#ifndef ELIMINARID_H
#define ELIMINARID_H
#include "Estructuras/arbolBinario.h"
#include "Lector/lectorarchivos.h"
#include <QCoreApplication>
#include <QSpinBox>
#include <QDateTime>

void EliminarId(ArbolBinario* arbolBinario, int persona){
    NodoOrdenado<Persona*>* candidato = arbolBinario->buscarNodoEnListaConID(persona);
    if(candidato == nullptr){
        qDebug() << "El candidato no existe";
    } else {
        qDebug() << "El candidato existe";
        candidato->data->vivo = false;
        QString textoBitacora = "";
        QDateTime fechaHoraActual = QDateTime::currentDateTime();
        QString fechaHoraTexto = fechaHoraActual.toString("yyyy-MM-dd HH:mm:ss");
        QString personaIdString = QString::number(candidato->data->ID);
        QString personaPecadosTotales = QString::number(candidato->data ->pecadosTotales);
        QString amigos = "";
        for(int i = 0; i < candidato->data->amigos->size(); i++){
            QString idAmigo = QString::number(candidato->data->amigos->ver(i)->ID);
            amigos += idAmigo + " " + candidato->data->amigos->ver(i)->nombre;
        }
        QString cantReencarnaciones = QString::number(candidato->data->reencarnaciones->cantItems);
        textoBitacora += fechaHoraTexto + " Heap Muerte " + " " + personaIdString + " "
                         + candidato->data->nombre + " " + candidato->data->apellido + " " + candidato->data->pais + " "
                         + candidato->data->creencia + " " + candidato->data->profesion + " " + candidato->data->timestampNacimiento
                         + " Pecados Totales " + personaPecadosTotales
                         + " Amigos " + amigos
                         + " Reencarnaciones " + cantReencarnaciones;

        QString baseDir = QCoreApplication::applicationDirPath();
        QString filePath = baseDir + "/Archivostxt/bitacoraMuerte.txt";
        lectorArchivos* lector = new lectorArchivos();
        lector->appendTextToFile(filePath, textoBitacora);
    }
}

#endif // ELIMINARID_H
