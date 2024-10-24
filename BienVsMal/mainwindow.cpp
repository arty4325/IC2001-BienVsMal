#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Estructuras/listaOrdenada.h"
#include "Human/persona.h"
#include "Human/personaCreator.h"
#include "Estructuras/arbolBinario.h"
#include <QSpinBox>
#include "Human/algoritmoAmigos.h"
#include "Human/hacerPecados.h"
#include "Estructuras/heapMuerte.h"
#include "Human/generarPandemia.h"
#include "Human/eliminarId.h"
#include "Estructuras/Reencarnacion.h"


ListaOrdenada<Persona*>* _listaHumanos = new ListaOrdenada<Persona*>();
ArbolBinario* arbolBinario;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    PersonaCreator* personaCreator = new PersonaCreator(10000, _listaHumanos);
    personaCreator->generarPersonas(100, 10, 10, 10, 10);
    qDebug() << _listaHumanos->size();
    algoritmoAmigos(_listaHumanos);
    /**
    for(int i = 0; i < 10000; i++){
        qDebug() << _listaHumanos->ver(i)->ID << " " << _listaHumanos->ver(i)->nombre << " " << _listaHumanos->ver(i)->apellido << " " << _listaHumanos->ver(i)->pais << " " <<
            _listaHumanos->ver(i)->creencia << " " << _listaHumanos->ver(i)->profesion << " " << _listaHumanos ->ver(i) ->timestampNacimiento;
    }
    **/

}


void MainWindow::on_pushButton_2_clicked()
{
    //Todo lo de esta funcion hay que ponerlo donde sea que se ponga después, no solo el new arbol.
    QTextBrowser* txbInfoHumanidad = ui->txbInfoArbolHumanos;
    txbInfoHumanidad->clear();
    txbInfoHumanidad->append("Información de los humanos en el último nivel: ");
    arbolBinario = new ArbolBinario(_listaHumanos, txbInfoHumanidad);
    txbInfoHumanidad->append("Cantidad de niveles en árbol: " + QString::number(arbolBinario->niveles));
    txbInfoHumanidad->append("Cantidad de nodos en árbol: " + QString::number(pow(2,arbolBinario->niveles)-1));
    txbInfoHumanidad->append("Cantidad de humanos: " + QString::number(_listaHumanos->size()));

}


void MainWindow::on_pushButton_3_clicked()
{
    NodoOrdenado<Persona*>* personaNodo = arbolBinario->buscarNodoEnListaConID(ui->spinBox->value());
    if(personaNodo  == nullptr){
        return;
    }
    Persona* persona = personaNodo->data;
    qDebug() << "\n\n\n\n";
    qDebug() << persona ->ID << " | " << persona->nombre << " " << persona->apellido << " | " << persona->pais << " | " << persona->creencia << " | " << persona->profesion;
    qDebug() << "Nació: " << persona->timestampNacimiento;
    qDebug() << "Tiene " << persona->pecadosTotales << " pecados en total";
    if(!persona->vivo){
        qDebug() << "Está muerto en este momento";
    }
    qDebug() << "Ha reencarnado " << persona->reencarnaciones->size() << " veces";
    for(int i=0;i<persona->reencarnaciones->size();i++){
        persona->reencarnaciones->ver(i)->imprimirReencarnacion();
    }

    qDebug() << "Tiene de amigos a " << persona->amigos->size() << " personas:";
    for(int i = 0; i<persona->amigos->size();i++){
        Amigo* amigo = persona->amigos->ver(i);
        qDebug() << amigo->ID << " | " <<amigo->nombre << " " << amigo->apellido << " | " << amigo->pais << " | " << amigo->creencia << " | " << amigo->profesion;
        qDebug() << "__________";
    }
    qDebug() << "_________________________________________________";

    qDebug() << "Es amigo de:";
        //TODO

}


void MainWindow::on_pushButton_4_clicked()
{
    HacerPecados(_listaHumanos);
    for(int i = 0; i < _listaHumanos->size(); i++){
        qDebug() << _listaHumanos->ver(i)->pecados[0];
        qDebug() << _listaHumanos->ver(i)->pecados[1];
        qDebug() << _listaHumanos->ver(i)->pecados[2];
        qDebug() << _listaHumanos->ver(i)->pecados[3];
        qDebug() << _listaHumanos->ver(i)->pecados[4];
        qDebug() << _listaHumanos->ver(i)->pecados[5];
        qDebug() << _listaHumanos->ver(i)->pecados[6];
        qDebug() << "--------------------------------";
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    HeapMuerte<Persona*> heap(-1);

    for(int i = 0; i < _listaHumanos->size(); i++){
        heap.agregarElemento(_listaHumanos->ver(i));
    }

    heap.construirHeap();
    ListaOrdenada<Persona*> personasRecorridas = heap.recorrerNiveles(4);

    // Mostrar las personas recorridas
    std::cout << "Personas en los niveles recorridos:" << std::endl;
    for (int i = 0; i < personasRecorridas.size(); i++) {
        Persona* persona = personasRecorridas.ver(i);
        std::cout << "ID: " << persona->ID << ", Nombre: " << persona->nombre.toStdString()
                  << ", Pecados Totales: " << persona->pecadosTotales << std::endl;
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    double prob = (ui->spinBox_2->value())/100.0;
    qDebug() << prob;
    GenerarPandemia(_listaHumanos, prob);
}


void MainWindow::on_pushButton_7_clicked()
{
    EliminarId(arbolBinario, ui->spinBox_3->value());
}

