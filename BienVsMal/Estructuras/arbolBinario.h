#ifndef ARBOLBINARIO_H
#define ARBOLBINARIO_H
#include "nodoAB.h"
#include "listaOrdenada.h"
#include "nodoOrdenado.h"
#include "Human/persona.h"
#include <cmath>

struct ArbolBinario{
    NodoAB* raiz;
    int niveles;
    ListaOrdenada<Persona*>* listaHumanos;
    int humanos;

    ArbolBinario(ListaOrdenada<Persona*>* _listaHumanos){
        listaHumanos = _listaHumanos;

        humanos = listaHumanos->size();
        niveles = ceil(log2(humanos/100)); //8 si hay 10000 personas
        raiz = new NodoAB(listaHumanos->verNodo(humanos/2)); //Le pone a la raíz el puntero y el ID de ese nodo en la lista.
        inicializarArbol(raiz, humanos/2, 2);
        inorden(raiz);
    }

    NodoOrdenado<Persona*>* buscarNodoEnListaConID(int ID){ //función solo para la llamada
        if(ID >= 1000000 || ID < 0){
            qDebug() << "Se buscó un nodo en lista con ID inválido";
            return nullptr;
        }
        NodoOrdenado<Persona*>* vaARetornar =  buscarNodoEnListaConIDAux(ID, raiz);
        if(vaARetornar == nullptr){
            qDebug() << "Persona Buscada no existe";
            return nullptr;
        }
        qDebug() << vaARetornar->data->ID;
        return vaARetornar;
    }


    private:
    void inicializarArbol(NodoAB* nodo, int cant, int nivel){
        if(nivel>niveles){ //Si ya construyó la cantidad necesaria de niveles
            return;
        }
        int indexIzquierda = cant - humanos/(int)(pow(2,nivel));
        int indexDerecha = cant + humanos/(int)(pow(2,nivel));
        nodo->hijoIzquierdo = new NodoAB(listaHumanos->verNodo(indexIzquierda));
        nodo->hijoDerecho = new NodoAB(listaHumanos->verNodo(indexDerecha));
        inicializarArbol(nodo->hijoIzquierdo,indexIzquierda,nivel+1);
        inicializarArbol(nodo->hijoDerecho,indexDerecha,nivel+1);
    }

    NodoOrdenado<Persona*>* buscarNodoEnListaConIDAux(int ID, NodoAB* nodo){ //La función que si es recursiva
        if(ID == nodo->ID){ //si alguno de los nodos tiene exactamente el ID que busca, entonces retornar el puntero al nodo en lista.
            return nodo->nodoPuntero;
        }
        if(nodo->hijoDerecho == nullptr && nodo->hijoIzquierdo == nullptr){ //si es una hoja, es decir, si llegó al final.
            int nodosARecorrer = ceil(listaHumanos->size()/(pow(2,niveles) -1)); //cantidad / cantNodosEnArbol.
            if(ID > nodo->ID){
                return buscarNodoEnListaDerecha(ID,nodo,nodosARecorrer);
            } else {
                return buscarNodoEnListaIzquierda(ID,nodo,nodosARecorrer);
            }
        }
        //Si no es una hoja, ni tiene el ID que necesita, entonces sigue izquierda/derecha.
        if(ID < nodo->ID){ //si es menor al del nodo, entonces que vaya al hijoIzquierdo y haga lo mismo.
            return buscarNodoEnListaConIDAux(ID, nodo->hijoIzquierdo);
        } else {
            return buscarNodoEnListaConIDAux(ID, nodo->hijoDerecho);
        }
    }

    NodoOrdenado<Persona*>* buscarNodoEnListaDerecha(int ID, NodoAB* nodo, int nodosARecorrer){
        NodoOrdenado<Persona*>* tmp = nodo->nodoPuntero;
        for(int i=0;i<nodosARecorrer;i++){
            if(ID == tmp->data->ID){
                return tmp;
            } else{
                tmp = tmp->next;
            }
        }
        return nullptr; //Si no encuentra
    }

    NodoOrdenado<Persona*>* buscarNodoEnListaIzquierda(int ID, NodoAB* nodo, int nodosARecorrer){
        NodoOrdenado<Persona*>* tmp = nodo->nodoPuntero;
        for(int i=0;i<nodosARecorrer;i++){
            if(ID == tmp->data->ID){
                return tmp;
            } else{
                tmp = tmp->previous;
            }
        }
        return nullptr; //Si no encuentra
    }

    void inorden(NodoAB* nodo) {
        if (nodo == nullptr) {
            return;
        }

        // Primero recorremos el hijo izquierdo
        inorden(nodo->hijoIzquierdo);

        // Luego procesamos el nodo actual (imprimimos el valor del nodo)
        qDebug() << nodo->ID;

        // Finalmente recorremos el hijo derecho
        inorden(nodo->hijoDerecho);
    }
};



#endif // ARBOLBINARIO_H
