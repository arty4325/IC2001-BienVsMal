#ifndef ANGEL_H
#define ANGEL_H
#include <QString>
#include "../Human/persona.h"
#include "Estructuras/Reencarnacion.h"
#include <QCoreApplication>
#include "Lector/lectorarchivos.h"
#include <QString>
#include "arbolBinario.h"

struct Angel{
    ArbolBinario* arbolBinario;
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
          QStringList _listaApellidos, QStringList _listaPais, QStringList _listaCreencia, QStringList _listaProfesion, ArbolBinario* _arbolBinario){
        nombre = "San " + _nombre;
        version = _version;
        generacion = _generacion;
        hijoIzquierdo = hijoCentro = hijoDerecho = nullptr;
        listaNombres = _listaNombres;
        listaApellidos = _listaApellidos;
        listaPais = _listaPais;
        listaCreencia = _listaCreencia;
        listaProfesion = _listaProfesion;
        arbolBinario = _arbolBinario;
        humanoSalvado = buscarHumanoASalvar();
    }

    Angel(QString _nombre, int _version, int _generacion, Persona* _humanoSalvado, ArbolBinario* _arbolBinario){ //para el caso de los primeros 2 niveles.
        nombre = _nombre;
        arbolBinario = _arbolBinario;
        version = _version;
        generacion = _generacion;
        humanoSalvado = _humanoSalvado;
        hijoIzquierdo = hijoCentro = hijoDerecho = nullptr;
    }

    QString infoAngel(){
        if(generacion < 3){
            return nombre;
        }
        if (humanoSalvado == nullptr){
            return (nombre + " (" + QString::number(version) + ") G" + QString::number(generacion)  + " No salvo a nadie");
        }
        return (nombre + " (" + QString::number(version) + ") G" + QString::number(generacion) + " ID: " + QString::number(humanoSalvado->ID) + " R" + QString::number(humanoSalvado->reencarnaciones->size()));
    } //Para imrpimir el arbol
private:
    Persona* buscarHumanoASalvar(){
        QString paraBitacora;
        QString personaRandom = "";
        QString personasMuertas = lector->read(6, -1);
        QStringList listaPersonasMuertas = personasMuertas.split("\n", Qt::SkipEmptyParts);
        QString filePath = "";
        filePath = baseDir + "/Archivostxt/bitacoraMuerte.txt";
        int idHumano = 0;
        // Verificar que la lista no esté vacía
        if (!listaPersonasMuertas.isEmpty()) {
            int randomIndex = QRandomGenerator::global()->bounded(listaPersonasMuertas.size());  // Generar un índice aleatorio
            QString personaRandom = listaPersonasMuertas.at(randomIndex);  // Seleccionar la persona al azar

            // Separar el string por tabuladores y obtener el primer elemento
            QStringList partes = personaRandom.split("\t");
            QString primerElemento = partes.value(0);  // Obtener el primer elemento (o una cadena vacía si no hay elementos)

            // Convertir el primer elemento a int y asignarlo a idHumano
            idHumano = primerElemento.toInt();

            // qDebug() << "Persona seleccionada al azar:" << personaRandom;
            lector->deleteLineFromFile(filePath, personaRandom);
            // qDebug() << "Primer elemento (ID):" << idHumano;
        } else {
            // qDebug() << "La lista de personas está vacía.";
        }

        // Ahora quiero borrar esa linea del txt
        if(idHumano != 0){
            Persona* persona = arbolBinario->buscarNodoEnListaConID(idHumano)->data;

            Reencarnacion* reencarnacion = new Reencarnacion(persona,this);
            paraBitacora = persona->timestampNacimiento + "\tHumano " + QString::number(persona->ID) + "\t" + persona->nombre + "\t" + persona->apellido + "\t" + persona->pais + "\t" + persona->profesion + "\t" + persona->creencia;
            persona->reencarnaciones->insert(reencarnacion);
            reencarnar(persona);


            paraBitacora += "\tSalvado por " + nombre + " (" + QString::number(version) + ")\tG" + QString::number(generacion);
            paraBitacora += "\tReencarnado como " + persona->nombre + "\t" + persona->apellido + "\t" + persona->pais + "\t" + persona->profesion + "\t" + persona->creencia;
            lector->appendTextToFile(path,paraBitacora);
            return persona;
        } else {
            paraBitacora += nombre + " (" + QString::number(version) + ")\tG" + QString::number(generacion) + "No salvó a nadie";
            lector->appendTextToFile(path,paraBitacora);
            return nullptr;
        }
    }

    void reencarnar(Persona* persona){
        persona->nombre = listaNombres[QRandomGenerator::global()->bounded(0, listaNombres.size())];
        persona->apellido = listaApellidos[QRandomGenerator::global()->bounded(0, listaApellidos.size())];
        persona->pais = listaPais[QRandomGenerator::global()->bounded(0, listaPais.size())];
        persona->profesion = listaProfesion[QRandomGenerator::global()->bounded(0, listaProfesion.size())];
        persona->creencia = listaCreencia[QRandomGenerator::global()->bounded(0, listaCreencia.size())];

        persona->pecadosTotales = 0;
        for (int i=0;i<7;i++){
            persona->pecados[i]/=2;
            persona->pecadosTotales += persona->pecados[i];
        }
        persona->amigos->vaciar();
        persona->timestampNacimiento = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        persona->vivo = true;
    }
};

#endif // ANGEL_H
