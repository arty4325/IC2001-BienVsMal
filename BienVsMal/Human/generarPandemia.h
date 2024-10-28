#ifndef GENERARPANDEMIA_H
#define GENERARPANDEMIA_H
#include "persona.h"
#include "Estructuras/arbolBinario.h"
#include "Estructuras/listaOrdenada.h"
#include "Lector/lectorarchivos.h"
#include <QCoreApplication>
#include <QSpinBox>
#include <QDateTime>
#include <QTcpSocket>

void GenerarPandemia(ListaOrdenada<Persona*>* listaHumanos, double porcentaje){
    // Quiero obtener la cantidad de humanos que quiero eliminar
    ListaOrdenada<Persona*>* listaHumanosVivos = new ListaOrdenada<Persona*>();
    for(int i = 0; i < listaHumanos->size(); i++){
        if(listaHumanos->ver(i)->vivo){
            listaHumanosVivos->insert(listaHumanos->ver(i));
        }
    }

    int cantidadEliminar = (listaHumanosVivos->size())*porcentaje;
    int cantidadEliminados = 0;
    qDebug() << cantidadEliminar << " estoy ejecutando pandemia";
    lectorArchivos* lector = new lectorArchivos();
    QString baseDir = QCoreApplication::applicationDirPath();
    lector->clearFile(baseDir + "/Archivostxt/muerteActual.txt");
    while(cantidadEliminados <= cantidadEliminar){
        int idRand = QRandomGenerator::global()->bounded(0, listaHumanosVivos->size());
        Persona* personaCandidata;
        personaCandidata = listaHumanosVivos->ver(idRand);
        if(personaCandidata->vivo == true){
            qDebug() << cantidadEliminados;
            cantidadEliminados += 1;
            personaCandidata -> vivo = false;
            QString textoBitacora = "";
            QDateTime fechaHoraActual = QDateTime::currentDateTime();
            QString fechaHoraTexto = fechaHoraActual.toString("yyyy-MM-dd HH:mm:ss");
            QString personaIdString = QString::number(personaCandidata->ID);
            QString personaPecadosTotales = QString::number(personaCandidata ->pecadosTotales);
            QString amigos = "";
            for(int i = 0; i < personaCandidata->amigos->size(); i++){
                QString idAmigo = QString::number(personaCandidata->amigos->ver(i)->ID);
                amigos += idAmigo + " " + personaCandidata->amigos->ver(i)->nombre ;
            }
            QString cantReencarnaciones = QString::number(personaCandidata->reencarnaciones->cantItems);
            textoBitacora += personaIdString + "    "
                             + personaCandidata -> nombre + "    " +
                             personaCandidata -> apellido + "    " +
                             personaCandidata -> pais + "    " +
                             personaCandidata -> creencia + "    " +
                             personaCandidata -> profesion + "    " +
                             personaCandidata -> timestampNacimiento + "    " +
                             personaPecadosTotales;
            QString filePath = baseDir + "/Archivostxt/muerteActual.txt";
            QString fileBitacora = baseDir + "/Archivostxt/bitacoraMuerte.txt";
            lector->appendTextToFile(filePath, textoBitacora);
            lector->appendTextToFile(fileBitacora, textoBitacora);

    }
    }}


#endif // GENERARPANDEMIA_H
