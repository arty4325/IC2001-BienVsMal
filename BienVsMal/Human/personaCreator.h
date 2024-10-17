#ifndef PERSONACREATOR_H
#define PERSONACREATOR_H

#include "persona.h"
#include "../Estructuras/cubetas.h"
#include "../Lector/lectorarchivos.h"
#include <QList>
#include <QDebug>
#include <QObject>
#include <QRandomGenerator>

class PersonaCreator {
public:
    int cantHumanos = 0;
    ListaOrdenada<Persona*>* listaHumanos = nullptr;
    Cubetas<Persona*>* cubetas;

    PersonaCreator(int _cantHumanos, ListaOrdenada<Persona*>* _listaHumanos) {
        listaHumanos = _listaHumanos;
        cantHumanos = _cantHumanos;
        cubetas = new Cubetas<Persona*>(listaHumanos->cantItems + cantHumanos);
    }


    void generarPersonas(int cantNombres, int cantApellidos, int cantPais, int cantCreencia, int cantProfesion) {
        int humanosGenerados = 0;
        lectorArchivos* lector = new lectorArchivos();

        QString nombresString = lector->read(1, cantNombres);
        QString apellidosString = lector->read(2, cantApellidos);
        QString paisString = lector->read(3, cantPais);
        QString creenciaString = lector->read(4, cantCreencia);
        QString profesionString = lector->read(5, cantProfesion);

        // Convertir las cadenas a listas de palabras separadas por salto de línea
        QStringList listaNombres = nombresString.split('\n');
        QStringList listaApellidos = apellidosString.split('\n');
        QStringList listaPaises = paisString.split('\n');
        QStringList listaCreencias = creenciaString.split('\n');
        QStringList listaProfesiones = profesionString.split('\n');

        while (humanosGenerados < cantHumanos) {
            int ranID = QRandomGenerator::global()->bounded(0, 999999);
            if (!existeID(ranID)) {
                // Generar índices aleatorios para cada atributo
                int ranNombre = QRandomGenerator::global()->bounded(0, cantNombres);
                int ranApellido = QRandomGenerator::global()->bounded(0, cantApellidos);
                int ranPais = QRandomGenerator::global()->bounded(0, cantPais);
                int ranCreencia = QRandomGenerator::global()->bounded(0, cantCreencia);
                int ranProfesion = QRandomGenerator::global()->bounded(0, cantProfesion);

                // Obtener valores correspondientes de cada lista
                QString nombre = listaNombres[ranNombre];
                QString apellido = listaApellidos[ranApellido];
                QString pais = listaPaises[ranPais];
                QString creencia = listaCreencias[ranCreencia];
                QString profesion = listaProfesiones[ranProfesion];

                // Crear la nueva persona con los atributos generados
                Persona* nuevaPersona = new Persona(ranID, nombre, apellido, pais, creencia, profesion, "");
                listaHumanos->insertOrdenado(nuevaPersona);

                // Insertar en la cubeta
                int cubetaIndex = ranID % cubetas->getCantCubetas();
                cubetas->insertarEnCubeta(cubetaIndex, nuevaPersona);

                humanosGenerados++;
            }
        }
    }


private:
    bool existeID(int id) {
        int cubetaIndex = id % cubetas->getCantCubetas(); // Calcular el índice de la cubeta

        ListaOrdenada<Persona*>* cubetaEspecifica = cubetas->ver(cubetaIndex);
        for (int i = 0; i < cubetaEspecifica->cantItems; i++) {
            Persona* p = cubetaEspecifica->ver(i);
            if (p->ID == id) {
                return true; // ID ya existe en la cubeta
            }
        }
        return false; // ID no existe
    }
};

#endif // PERSONACREATOR_H
