#ifndef ARBOLANGELES_H
#define ARBOLANGELES_H
#include "Angel.h"
#include <QString>
#include "Lector/lectorarchivos.h"

struct ArbolAngeles{
    Angel* raiz;
    QString nombres[10] = {"Miguel", "Nuriel", "Aniel", "Rafael", "Gabriel","Shamsiel", "Raguel", "Uriel", "Azrael", "Sariel"};
    int versionesNombres[10];
    int altura;
    QString baseDir = QCoreApplication::applicationDirPath();
    QString path = baseDir + "/Archivostxt/arbolAngeles.txt";

    lectorArchivos* lector = new lectorArchivos();

    QString nombresString = lector->read(1, 10000);
    QString apellidosString = lector->read(2, 10000);
    QString paisString = lector->read(3, 100);
    QString creenciaString = lector->read(4, 20);
    QString profesionString = lector->read(5, 100);

    // Convertir las cadenas a listas de palabras separadas por salto de línea
    QStringList listaNombres = nombresString.split('\n');
    QStringList listaApellidos = apellidosString.split('\n');
    QStringList listaPaises = paisString.split('\n');
    QStringList listaCreencias = creenciaString.split('\n');
    QStringList listaProfesiones = profesionString.split('\n');


    ArbolAngeles(){
        raiz = new Angel("Dios",1, 1,nullptr);
        raiz->hijoIzquierdo = new Angel("Serafines",1, 2,nullptr);
        raiz->hijoCentro = new Angel("Querubines",1, 2,nullptr);
        raiz->hijoDerecho = new Angel("Tronos",1, 2,nullptr);
        altura = 2;
    }

    void salvacion(){ //crea un nuevo árbol de ángeles salvadores
        for(int i=0;i<10;i++){
            versionesNombres[i] = 0;
        }
        salvacion(raiz,2);
        //Mandarlo al correo TODO:
        //ponerlo vacio
        altura++;
    }

    void ponerEnBitacora(){
        //TODO: poner en blanco
        for(int nivel = 1; nivel <= altura ; nivel++){
            lector->appendTextToFile(path,stringNivel(raiz,nivel));
        }
    }


private:
    void salvacion(Angel* nodo, int generacion){
        if(nodo == nullptr){ //Condicion de parada
            return;
        }

        if(nodo->hijoIzquierdo == nullptr && nodo->hijoCentro == nullptr && nodo->hijoDerecho == nullptr){ // Si ya llega a hoja / el último nivel
            int nombreIzquierdo = QRandomGenerator::global()->bounded(0, 10); //genera numero entre 0 y 9
            nodo->hijoIzquierdo = new Angel(nombres[nombreIzquierdo],versionesNombres[nombreIzquierdo]++,generacion, listaNombres, listaApellidos, listaPaises, listaCreencias, listaProfesiones);

            int nombreCentro = QRandomGenerator::global()->bounded(0, 10);
            nodo->hijoCentro = new Angel(nombres[nombreCentro], versionesNombres[nombreCentro]++, generacion, listaNombres, listaApellidos, listaPaises, listaCreencias, listaProfesiones);

            int nombreDerecho = QRandomGenerator::global()->bounded(0, 10);
            nodo->hijoDerecho = new Angel(nombres[nombreDerecho], versionesNombres[nombreDerecho]++, generacion, listaNombres, listaApellidos, listaPaises, listaCreencias, listaProfesiones);
        }

        salvacion(nodo->hijoIzquierdo,generacion+1);
        salvacion(nodo->hijoCentro,generacion+1);
        salvacion(nodo->hijoDerecho,generacion+1);
    }

    QString stringNivel(Angel* nodo, int nivel){
        if (nodo == nullptr){
            return "";
        }
        if(nivel == 1){
            return nodo->infoAngel() + "\t\t";
        }else if (nivel > 1){
            return stringNivel(nodo->hijoIzquierdo,nivel-1) + stringNivel(nodo->hijoCentro,nivel-1) + stringNivel(nodo->hijoDerecho,nivel-1);
        }
        return "";
    }
};

#endif // ARBOLANGELES_H
