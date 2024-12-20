#ifndef LISTAORDENADA_H
#define LISTAORDENADA_H
#include "NodoOrdenado.h"
#include <QList>
#include <QDebug>
#include <QObject>
#include <QRandomGenerator>


template <typename T>
class ListaOrdenada {
public:
    int cantItems = 0;
    NodoOrdenado<T>* primerNodo = nullptr;
    NodoOrdenado<T>* ultimoNodo = nullptr;

    // Método para insertar un nuevo nodo en la lista
    void insert(T _data){
        NodoOrdenado<T>* nodo = new NodoOrdenado<T>();
        nodo->data = _data;
        if(cantItems == 0){
            primerNodo = ultimoNodo = nodo;
        } else {
            // Agregar el nuevo nodo después del último nodo
            NodoOrdenado<T>* tempNodo = ultimoNodo;
            ultimoNodo = nodo;
            ultimoNodo->previous = tempNodo;
            tempNodo->next = ultimoNodo;
        }
        cantItems += 1;
    }

    void vaciar(){
        while(borrarAlInicio()){}
        cantItems = 0;
    }

    // Método para insertar un nuevo nodo en la lista de forma ordenada
    void insertOrdenado(T _data) {
        NodoOrdenado<T>* nuevoNodo = new NodoOrdenado<T>();
        nuevoNodo->data = _data;

        // Caso 1: La lista está vacía
        if (cantItems == 0) {
            primerNodo = ultimoNodo = nuevoNodo;
        } else {
            NodoOrdenado<T>* nodoActual = primerNodo;

            // Buscar la posición de inserción
            while (nodoActual != nullptr && nodoActual->data->ID < _data->ID) { // Suponiendo que la clase T tiene un atributo ID (Pensado para personas)
                nodoActual = nodoActual->next;
            }

            // Caso 2: Insertar al inicio
            if (nodoActual == primerNodo) {
                nuevoNodo->next = primerNodo;
                primerNodo->previous = nuevoNodo;
                primerNodo = nuevoNodo; // Actualizar el primer nodo
            }
            // Caso 3: Insertar al final
            else if (nodoActual == nullptr) {
                ultimoNodo->next = nuevoNodo;
                nuevoNodo->previous = ultimoNodo;
                ultimoNodo = nuevoNodo; // Actualizar el último nodo
            }
            // Caso 4: Insertar en el medio
            else {
                nuevoNodo->previous = nodoActual->previous;
                nuevoNodo->next = nodoActual;

                if (nodoActual->previous != nullptr) {
                    nodoActual->previous->next = nuevoNodo; // Actualizar el siguiente del nodo anterior
                }
                nodoActual->previous = nuevoNodo; // Actualizar el anterior del nodo actual
            }
        }

        cantItems += 1; // Incrementar el contador de items
    }

    T borrar(int indice) {
        // Verificar si el índice está dentro del rango
        if (indice < 0 || indice >= cantItems) {
            return T();  // Devuelve un objeto por defecto si el índice es inválido
        }

        // Caso especial: si la lista tiene un solo elemento
        if (cantItems == 1) {
            NodoOrdenado<T>* nodoAEliminar = primerNodo;  // El único nodo

            // Actualizar primerNodo y ultimoNodo a nullptr ya que estamos eliminando el único nodo
            primerNodo = nullptr;
            ultimoNodo = nullptr;

            T dataEliminada = nodoAEliminar->data;
            delete nodoAEliminar;  // Liberar memoria
            cantItems = 0;  // La lista ahora está vacía

            return dataEliminada;  // Retorna el dato eliminado
        }

        // Caso especial: eliminar el primer nodo (índice 0)
        if (indice == 0) {
            NodoOrdenado<T>* nodoAEliminar = primerNodo;
            T dataEliminada = nodoAEliminar->data;

            primerNodo = nodoAEliminar->next;  // Actualizar el primer nodo

            if (primerNodo != nullptr) {
                primerNodo->previous = nullptr;  // Si hay un nuevo primer nodo, no tiene anterior
            }

            delete nodoAEliminar;  // Liberar la memoria del nodo eliminado
            cantItems -= 1;
            return dataEliminada;  // Retornar el dato eliminado
        }

        // Caso general: eliminar un nodo que no es el primero
        NodoOrdenado<T>* nodoActual = primerNodo;

        // Avanza hasta el nodo a eliminar
        for (int i = 0; i < indice; i++) {
            nodoActual = nodoActual->next;
        }

        // Eliminar el nodo actual (que no es el primero)
        if (nodoActual->previous != nullptr) {
            nodoActual->previous->next = nodoActual->next;
        }

        if (nodoActual->next != nullptr) {
            nodoActual->next->previous = nodoActual->previous;
        } else {
            // Si es el último nodo, actualizar el último puntero
            ultimoNodo = nodoActual->previous;
        }

        T dataEliminada = nodoActual->data;
        delete nodoActual;  // Liberar la memoria del nodo
        cantItems -= 1;

        return dataEliminada;  // Retornar el dato eliminado
    }


    // Método para ver el valor de un nodo en un índice específico
    T ver(int indice) const {
        if(indice < 0 || indice >= cantItems){
            return T();  // Devuelve un objeto por defecto si el índice es inválido
        }

        NodoOrdenado<T>* nodoActual = primerNodo;
        for(int i = 0; i < indice; i++){
            nodoActual = nodoActual->next;
        }

        return nodoActual->data;  // Retorna el dato del nodo en el índice
    }

    NodoOrdenado<T>* verNodo(int indice){ //Lo mismo que el anterior pero devuelve el nodo, no su data.
        if(indice < 0 || indice >= cantItems){
            return new NodoOrdenado<T>();  // Devuelve un objeto por defecto si el índice es inválido
        }

        NodoOrdenado<T>* nodoActual = primerNodo;
        for(int i = 0; i < indice; i++){
            nodoActual = nodoActual->next;
        }

        return nodoActual;  // Retorna el nodo en el índice
    }

    // Método que devuelve el tamaño de la lista
    int size() const {
        return cantItems;
    }

    void set(int indice, T nuevoData) {
        if (indice < 0 || indice >= cantItems) {
            return;
        }
        NodoOrdenado<T>* nodoActual = primerNodo;
        for(int i = 0; i < indice; i++){
            nodoActual = nodoActual -> next;
        }
        nodoActual -> data = nuevoData;
    }

private:
    bool borrarAlInicio() {
        if (primerNodo != NULL) { // caso solo 1 nodo
            if (primerNodo == ultimoNodo) {
                primerNodo = ultimoNodo = NULL;
            } else { // caso mas de un Nodo
                NodoOrdenado<T>* borrado = primerNodo;
                primerNodo = primerNodo->next;
                borrado->next = NULL;
                primerNodo->previous = NULL;
            }
            return true;
        }
        return false;
    }
};

#endif // LISTAORDENADA_H
