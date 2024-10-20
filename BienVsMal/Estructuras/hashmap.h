#ifndef HASHMAP_H
#define HASHMAP_H
#include "Estructuras/nodoHash.h"

struct Hashmap{
    static const int SIZE = 250;
    NodoHash* hashmap[SIZE];

    Hashmap(){
        for (int i=0;i<SIZE;i++){
            hashmap[i] = nullptr;
        } //inicializa todo en null
    }

    ~Hashmap() {
        //destructor
        for (int i = 0; i < SIZE; i++) {
            NodoHash* tmp = hashmap[i];
            while (tmp != nullptr) {
                NodoHash* next = tmp->next;
                delete tmp;
                tmp = next;
            }
        }
        //como el hashmap solo se va a usar por un momento entonces luego de usarlo lo borra el destructor poco a poco.
    }

    int funcionHash(QString key){
        int hash = 0;
        for(QChar caracter : key){
            hash += caracter.unicode(); //coge el valor en entero del caracter
        }
        return hash % SIZE; //devuelve siempre un valor entre 0-249 que va a ser el hash para el hashmap.
    }

    void insertar(Persona* persona){
        QString key = persona->apellido + persona->pais + persona->creencia; //pone las 3 en un solo string, que va a ser el key.
        int index = funcionHash(key);
        NodoHash* tmp = hashmap[index];
        if(tmp == nullptr){
            hashmap[index] = new NodoHash(key,persona); //si es el primero en ese index.
        } else {
            while(tmp -> next != nullptr){
                tmp = tmp ->next; //Si no es el primero, entonces va al siguiente espacio en null
            }
            tmp -> next = new NodoHash(key, persona);
        }
    }








};

#endif // HASHMAP_H
