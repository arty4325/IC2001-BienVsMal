#ifndef NodoOrdenado_H
#define NodoOrdenado_H


template <typename T>
class NodoOrdenado {
public:
    T data;
    NodoOrdenado* next; // Siguiente (Por ser una lista ordenada)
    NodoOrdenado* previous; // Anterior

    NodoOrdenado(){
        data = 0;
        next = nullptr;
    }

    NodoOrdenado(T _data){
        data = _data;
        next = nullptr;
    }
};


#endif // NodoOrdenado_H
