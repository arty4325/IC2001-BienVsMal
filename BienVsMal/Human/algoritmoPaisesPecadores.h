#ifndef ALGORITMOPAISESPECADORES_H
#define ALGORITMOPAISESPECADORES_H
#include "persona.h"
#include "Estructuras/PaisPecados.h"
#include "Lector/lectorarchivos.h"
#include <QTextBrowser>

bool compararPorPecados(PaisPecados* a, PaisPecados* b) {
    return a->pecados < b->pecados;
}

void algoritmoPaisesPecadores(ListaOrdenada<Persona*>* _humanosCadaPais[100] , QTextBrowser* txbConsultas){
    PaisPecados* pecadosPorPais[100];
    lectorArchivos* lector = new lectorArchivos();
    QString paisString = lector->read(3, 100);
    QStringList listaPaises = paisString.split('\n');

    for (int i=0;i<100;i++){

        pecadosPorPais[i] = new PaisPecados(listaPaises[i]);

        ListaOrdenada<Persona*>* listaPersonasPais = _humanosCadaPais[i];
        NodoOrdenado<Persona*>* tmp = listaPersonasPais ->primerNodo;
        while(tmp!= nullptr){
            pecadosPorPais[i]->pecados += tmp->data->pecadosTotales;
            tmp = tmp->next;
        }
    }

    std::sort(pecadosPorPais,pecadosPorPais + 100,compararPorPecados);
    for(int i=99;i>=0;i--){
        txbConsultas->append(pecadosPorPais[i]->pais + ": " + QString::number(pecadosPorPais[i]->pecados));
    }
}



#endif // ALGORITMOPAISESPECADORES_H
