#ifndef ELIMINARID_H
#define ELIMINARID_H
#include "Estructuras/arbolBinario.h"
#include "Lector/lectorarchivos.h"
#include <QCoreApplication>
#include <QSpinBox>
#include <QDateTime>
#include <QTcpSocket>

void EliminarId(ArbolBinario* arbolBinario, int persona, QString _correo){
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
        textoBitacora += personaIdString + "    "
                         + candidato->data -> nombre + "    " +
                         candidato->data -> apellido + "    " +
                         candidato->data -> pais + "    " +
                         candidato->data -> creencia + "    " +
                         candidato->data -> profesion + "    " +
                         candidato->data -> timestampNacimiento + "    " +
                         personaPecadosTotales;
        lectorArchivos* lector = new lectorArchivos();
        QString baseDir = QCoreApplication::applicationDirPath();
        QString fileBitacora = baseDir + "/Archivostxt/bitacoraMuerte.txt";
        lector->clearFile(baseDir + "/Archivostxt/muerteActual.txt");
        QString filePath = baseDir + "/Archivostxt/muerteActual.txt";
        lector->appendTextToFile(filePath, textoBitacora);
        lector->appendTextToFile(fileBitacora, textoBitacora);

        QTcpSocket socket;
        socket.connectToHost("127.0.0.1", 12345); // Conectar al servidor

        if (socket.waitForConnected()) {
            qDebug() << "Conectado al servidor!";

            // Enviar un mensaje al servidor
            QString correo;
            QString filePath;
            correo = _correo;
            QString baseDir = QCoreApplication::applicationDirPath();
            filePath = baseDir + "/Archivostxt/muerteActual.txt";
            socket.write((correo + " " + filePath).toUtf8());
            socket.flush();

            // No esperamos respuesta, así que simplemente cerramos la conexión
            socket.disconnectFromHost();
            qDebug() << "Mensaje enviado y conexión cerrada.";
        } else {
            qDebug() << "Error al conectar al servidor!";
        }
    }
}

#endif // ELIMINARID_H
