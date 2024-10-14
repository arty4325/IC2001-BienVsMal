#ifndef NODOORDENADO_H
#define NODOORDENADO_H


template <typename T>
class nodoOrdenado {
public:
    T data;
    nodoOrdenado* next; // Siguiente (Por ser una lista ordenada)
    nodoOrdenado* previous; // Anterior

    nodoOrdenado(){
        data = 0;
        next = nullptr;
    }

    nodoOrdenado(T _data){
        data = _data;
        next = nullptr;
    }
};


#endif // NODOORDENADO_H
