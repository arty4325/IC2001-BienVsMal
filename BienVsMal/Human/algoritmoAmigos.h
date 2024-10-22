#ifndef ALGORITMOAMIGOS_H
#define ALGORITMOAMIGOS_H
#include "Human/persona.h"
#include "Estructuras/listaOrdenada.h"
#include "Estructuras/hashmap.h"
#include "../Estructuras/Amigo.h"

void algoritmoAmigos(ListaOrdenada<Persona*>* listaHumanos){
    Hashmap* hashmap = new Hashmap();
    for (int i=0;i<listaHumanos->size();i++){ //mete a todos en el hashmap
        hashmap->insertar(listaHumanos->ver(i));
    }
    for (int i=0;i<listaHumanos->size();i++){
        Persona* persona = listaHumanos->ver(i);
        QString key = persona->apellido + persona->pais + persona->creencia; //pone las 3 en un solo string, que va a ser el key.
        int index = hashmap->funcionHash(key);
        NodoHash* tmp = hashmap->hashmap[index];
        while(persona->amigos->size() < 10 && tmp!=nullptr){ //Mientras la persona no tenga 10 amigos y aún hayan posibles personas que pueden ser amigos
            if(tmp->key == key){
                if(tmp->data == persona){
                    tmp = tmp ->next;
                    continue; // si es la misma persona, entonces no la agrega a amigos.
                }
                persona->amigos->insert(new Amigo(tmp->data->ID,tmp->data->nombre, tmp->data->apellido, tmp->data->pais, tmp->data->creencia, tmp->data->profesion));
            }
            tmp = tmp ->next;
        }
    }

    delete hashmap;
}

#endif // ALGORITMOAMIGOS_H
