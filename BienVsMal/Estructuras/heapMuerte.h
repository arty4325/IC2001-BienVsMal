#ifndef HEAPMUERTE_H
#define HEAPMUERTE_H
#include <iostream>
#include <algorithm>
#include "listaOrdenada.h"
#include "../Human/persona.h"


template <typename T>
class HeapMuerte {
private:
    ListaOrdenada<Persona*> elementos;
    int indicePecado; // Con esto decido si es por pecados totales o por un pecado que yo decida

    int obtenerValorComparacion(Persona* persona){
        if(indicePecado == -1){
            return persona->pecadosTotales;
        }
        return persona->pecados[indicePecado];
    }

    void heapify(int index, int size){
        int largest = index;
        int left = 2*index+1;
        int right = 2*index+2;

        if(left < size && obtenerValorComparacion(elementos.ver(left)) > obtenerValorComparacion(elementos.ver(largest))){
            largest = left;
        }

        if (right < size && obtenerValorComparacion(elementos.ver(right)) > obtenerValorComparacion(elementos.ver(largest))) {
            largest = right;
        }

        if(largest != index) {
            Persona* temp = elementos.ver(index);
            elementos.set(index, elementos.ver(largest));
            elementos.set(largest, temp);

            heapify(largest, size);
        }
    }
public:
    HeapMuerte(int indicePecado = -1) : indicePecado(indicePecado) {}

    void agregarElemento(Persona* elemento){
        elementos.insert(elemento);
        int index = elementos.size() - 1;

        while(index != 0 && obtenerValorComparacion(elementos.ver((index - 1)/2)) < obtenerValorComparacion(elementos.ver(index))) {
            Persona * temp = elementos.ver(index);
            elementos.set(index, elementos.ver((index - 1 )/ 2));
            elementos.set((index - 1)/2, temp);
        }
    }

    void construirHeap(){
        int size = elementos.size();
        for(int i = size / 2 - 1; i >= 0; i--){
            heapify(i, size);
        }
    }

    ListaOrdenada<Persona*> recorrerNiveles(int niveles){
        ListaOrdenada<Persona*> resultado;

        for(int nivel = 0; nivel < niveles; nivel++){
            int startIndex = (1 << nivel) - 1;

            int numNodosNivel = 1 << nivel;

            for(int i = 0; i < numNodosNivel; i++){
                int index = startIndex + i;

                if(index < elementos.size()) {
                    resultado.insert(elementos.ver(index));
                } else {
                    break;
                }
            }
        }
        return resultado;
    }
};

#endif // HEAPMUERTE_H
