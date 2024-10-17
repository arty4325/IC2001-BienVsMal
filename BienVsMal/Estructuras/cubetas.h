#ifndef CUBETAS_H
#define CUBETAS_H

#include "listaOrdenada.h"
#include <QDebug>

template <typename T>
class Cubetas {
    int cantCubetas = 0;
    int cantItemsPorCubeta = 100; // Máximo ítems por cubeta
    ListaOrdenada<ListaOrdenada<T>*>* cubetas;

public:
    // Constructor
    Cubetas(int cantItems) {
        if (cantItems <= 100) {
            cantCubetas = cantItems;
        } else {
            cantCubetas = cantItems / 100;
            if (cantItems % 100 != 0) {
                cantCubetas++;
            }
        }

        cubetas = new ListaOrdenada<ListaOrdenada<T>*>();
        for (int i = 0; i < cantCubetas; ++i) {
            cubetas->insert(new ListaOrdenada<T>());
        }
    }

    int getCantCubetas() {
        return cantCubetas;
    }

    void insertarEnCubeta(int indiceCubeta, const T& item) {
        if (indiceCubeta >= 0 && indiceCubeta < cantCubetas) {
            ListaOrdenada<T>* cubetaEspecifica = cubetas->ver(indiceCubeta);

            if (cubetaEspecifica->size() >= cantItemsPorCubeta) {
                T ultimoElemento = cubetaEspecifica->ultimoNodo->data;
                cubetaEspecifica->ultimoNodo->data;
                cubetaEspecifica->insert(item);
                moverAProximaCubeta(indiceCubeta + 1, ultimoElemento);
            } else {
                cubetaEspecifica->insert(item);
            }
        } else {
            qDebug() << "Índice de cubeta fuera de rango.";
        }
    }

    void moverAProximaCubeta(int indiceCubeta, const T& item) {
        if (indiceCubeta < cantCubetas) {
            ListaOrdenada<T>* siguienteCubeta = cubetas->ver(indiceCubeta);

            if (siguienteCubeta->size() >= cantItemsPorCubeta) {
                T ultimoElemento = siguienteCubeta->ultimoNodo->data;
                siguienteCubeta->borrar(siguienteCubeta->cantItems - 1);
                siguienteCubeta->insert(item);
                moverAProximaCubeta(indiceCubeta + 1, ultimoElemento);
            } else {
                siguienteCubeta->insert(item);
            }
        } else {
            qDebug() << "Todas las cubetas están llenas.";
        }
    }

    ListaOrdenada<T>* ver(int indiceCubeta) {
        if (indiceCubeta >= 0 && indiceCubeta < cantCubetas) {
            return cubetas->ver(indiceCubeta); // Devuelve la cubeta específica
        } else {
            qDebug() << "Índice de cubeta fuera de rango.";
            return nullptr; // Devuelve nullptr si el índice está fuera de rango
        }
    }


    ListaOrdenada<T> obtenerMinMaxDeCubeta(int indiceCubeta) {
        if (indiceCubeta >= 0 && indiceCubeta < cantCubetas) {
            ListaOrdenada<T>* cubetaEspecifica = cubetas->ver(indiceCubeta);

            if (cubetaEspecifica->getSize() > 0) {
                T minimo = cubetaEspecifica->primerNodo();
                T maximo = cubetaEspecifica->ultimoNodo();


                ListaOrdenada<T> minMaxLista;
                minMaxLista.insertar(minimo);
                minMaxLista.insertar(maximo);

                return minMaxLista;
            } else {
                qDebug() << "Cubeta vacía.";
                return ListaOrdenada<T>();
            }
        } else {
            qDebug() << "Índice de cubeta fuera de rango.";
            return ListaOrdenada<T>();
        }
    }


    ~Cubetas() {
        for (int i = 0; i < cantCubetas; ++i) {
            delete cubetas->ver(i);
        }
        delete cubetas;
    }
};

#endif // CUBETAS_H
