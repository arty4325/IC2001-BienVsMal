#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Estructuras/listaOrdenada.h"
#include "Human/persona.h"
#include "Human/personaCreator.h"
#include "Estructuras/arbolBinario.h"
#include <QSpinBox>
#include "Human/algoritmoAmigos.h"
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
    qDebug() << persona->nombre << " " << persona->apellido << " " << persona->pais << " " << persona->creencia;

    qDebug() << "Amigos:" << persona->amigos->size();
    for(int i = 0; i<persona->amigos->size();i++){
        Persona* amigo = persona->amigos->ver(i);
        qDebug() << amigo->nombre << " " << amigo->apellido << " " << amigo->pais << " " << amigo->creencia;
        qDebug() << "__________";
    }
    qDebug() << "_________________________________________________";



}

