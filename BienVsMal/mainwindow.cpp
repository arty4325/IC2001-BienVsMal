#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Estructuras/listaOrdenada.h"
#include "Human/persona.h"
#include "Human/personaCreator.h"
#include "Estructuras/arbolBinario.h"
#include <QSpinBox>
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
    personaCreator->generarPersonas(5, 5, 5, 5, 5);
    qDebug() << _listaHumanos->size();
    /**
    for(int i = 0; i < 10000; i++){
        qDebug() << _listaHumanos->ver(i)->ID << " " << _listaHumanos->ver(i)->nombre << " " << _listaHumanos->ver(i)->apellido << " " << _listaHumanos->ver(i)->pais << " " <<
            _listaHumanos->ver(i)->creencia << " " << _listaHumanos->ver(i)->profesion << " " << _listaHumanos ->ver(i) ->timestampNacimiento;
    }
    **/

}


void MainWindow::on_pushButton_2_clicked()
{
    arbolBinario = new ArbolBinario(_listaHumanos);
}


void MainWindow::on_pushButton_3_clicked()
{
    arbolBinario->buscarNodoEnListaConID(ui->spinBox->value());
}

