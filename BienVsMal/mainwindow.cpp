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
#include "Lector/lectorarchivos.h"
#include "Estructuras/ArbolAngeles.h"
#include "Human/algoritmoPaisesPecadores.h"
#include <QProcess>
#include <QString>
#include <QTcpSocket>
#include <QCoreApplication>
#include <QTextStream>

ListaOrdenada<Persona*>* _listaHumanos = new ListaOrdenada<Persona*>();
ArbolBinario* arbolBinario;
ListaOrdenada<Persona*>* humanosCadaPais[100];
ArbolAngeles* arbolAngeles;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lectorArchivos* lector = new lectorArchivos();
    QString baseDir = QCoreApplication::applicationDirPath();
    QString fileBitacora = baseDir + "/Archivostxt/bitacoraMuerte.txt";
    QString fileHumanidad = baseDir + "/Archivostxt/humanidad.txt";
    QString fileSalvacion = baseDir + "/Archivostxt/salvacion.txt";
    lector->clearFile(fileBitacora);
    lector->clearFile(fileHumanidad);
    lector->clearFile(fileSalvacion);
    arbolAngeles = new ArbolAngeles(arbolBinario);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    for(int i=0;i<100;i++){
        humanosCadaPais[i] = new ListaOrdenada<Persona*>;
    }
    // Aqui tengo que pasar cuantos humanos voy a crear

    PersonaCreator* personaCreator = new PersonaCreator(ui->cantHumanos->value(), _listaHumanos, humanosCadaPais);
    // Los boundaries son
    // 1000, 1000, 100, 20, 100
    // int cantNombres, int cantApellidos, int cantPais, int cantCreencia, int cantProfesion
    personaCreator->generarPersonas(ui->cantNombres->value(), ui->cantApellidos->value(), ui->cantPaises->value(), ui->cantReligiones->value(), ui->cantProfesiones->value());
    // qDebug() << _listaHumanos->size();
    algoritmoAmigos(_listaHumanos);

    QTextBrowser* txbInfoHumanidad = ui->txbInfoArbolHumanos;
    txbInfoHumanidad->clear();
    txbInfoHumanidad->append("Información de los humanos en el último nivel: ");
    arbolBinario = new ArbolBinario(_listaHumanos, txbInfoHumanidad);
    txbInfoHumanidad->append("Cantidad de niveles en árbol: " + QString::number(arbolBinario->niveles));
    txbInfoHumanidad->append("Cantidad de nodos en árbol: " + QString::number(pow(2,arbolBinario->niveles)-1));
    txbInfoHumanidad->append("Cantidad de humanos: " + QString::number(_listaHumanos->size()));


}


void MainWindow::on_pushButton_2_clicked()
{
    algoritmoAmigos(_listaHumanos);
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->txbConsultas->clear();
    NodoOrdenado<Persona*>* personaNodo = arbolBinario->buscarNodoEnListaConID(ui->spinBox->value());
    if(personaNodo  == nullptr){
        ui->txbConsultas->append("No existe una persona con ese ID");
        return;
    }
    Persona* persona = personaNodo->data;
    ui->txbConsultas->append(QString::number(persona ->ID) + " | " + persona->nombre + " " + persona->apellido + " | " + persona->pais + " | " + persona->creencia + " | " + persona->profesion);
    ui->txbConsultas->append("Nació: " + persona->timestampNacimiento);
    ui->txbConsultas->append("Tiene " + QString::number(persona->pecadosTotales) + " pecados en total");
    if(!persona->vivo){
        ui->txbConsultas->append("Está muerto en este momento");
    } else {
        ui->txbConsultas->append("Está vivo en este momento");
    }
    ui->txbConsultas->append("Ha reencarnado " + QString::number(persona->reencarnaciones->size()) + " veces");
    for(int i=0;i<persona->reencarnaciones->size();i++){
        ui->txbConsultas->append(persona->reencarnaciones->ver(i)->infoReencarnacion());
    }
    ui->txbConsultas->append("_________________________________________________");
    ui->txbConsultas->append("Tiene de amigos a " + QString::number(persona->amigos->size()) + " personas:");
    for(int i = 0; i<persona->amigos->size();i++){
        Amigo* amigo = persona->amigos->ver(i);
        if(amigo != nullptr){
            ui->txbConsultas->append(QString::number(amigo->ID) + " | " + amigo->nombre + " " + amigo->apellido + " | " + amigo->pais + " | " + amigo->creencia + " | " + amigo->profesion);
        }
    }
    ui->txbConsultas->append("_________________________________________________");

    ui->txbConsultas->append("Es amigo de:");
    NodoOrdenado<Persona*>* tmp = _listaHumanos->primerNodo;
    while(tmp != nullptr){
        if(tmp->data == persona){
            tmp = tmp->next;
            continue;
        }
        if(tmp->data->revisarAmigos(persona)){
            ui->txbConsultas->append(QString::number(tmp->data->ID) + " | " + tmp->data->nombre + " " + tmp->data->apellido + " | " + tmp->data->pais + " | " + tmp->data->creencia + " | " + tmp->data->profesion);
        }
        tmp = tmp->next;
    }

}


void MainWindow::on_pushButton_4_clicked()
{
    HacerPecados(_listaHumanos);
    //quite lo que habia dicho de imprimir que podria ser lo que lo hace lento
}


void MainWindow::on_pushButton_5_clicked()
{
    HeapMuerte<Persona*> heap(ui->heapMatar->value());

    for(int i = 0; i < _listaHumanos->size(); i++){
        if(_listaHumanos-> ver(i)->vivo){
            heap.agregarElemento(_listaHumanos->ver(i));
        }
    }

    heap.construirHeap();
    ListaOrdenada<Persona*> personasRecorridas = heap.recorrerNiveles(ui->nivelesMatar->value());

    // Mostrar las personas recorridas
    std::cout << "Personas en los niveles recorridos:" << std::endl;
    QString baseDir = QCoreApplication::applicationDirPath();
    QString filePath = baseDir + "/Archivostxt/muerteActual.txt";
    QString fileBitacora = baseDir + "/Archivostxt/bitacoraMuerte.txt";
    lectorArchivos* lector = new lectorArchivos();
    lector->clearFile(baseDir + "/Archivostxt/muerteActual.txt");
    for (int i = 0; i < personasRecorridas.size(); i++) {
        Persona* persona = personasRecorridas.ver(i);
        persona->vivo = false;
        std::cout << "ID: " << persona->ID << ", Nombre: " << persona->nombre.toStdString()
                  << ", Pecados Totales: " << persona->pecadosTotales << std::endl;
        // Aqui es donde tengo que guardar la informacion en el archivo
        QString textoBitacora = "";
        QDateTime fechaHoraActual = QDateTime::currentDateTime();
        QString fechaHoraTexto = fechaHoraActual.toString("yyyy-MM-dd HH:mm:ss");
        QString personaIdString = QString::number(persona->ID);
        QString personaPecadosTotales = QString::number(persona ->pecadosTotales);
        QString amigos = "";
        for(int i = 0; i < persona->amigos->size(); i++){
            QString idAmigo = QString::number(persona->amigos->ver(i)->ID);
            amigos += idAmigo + " " + persona->amigos->ver(i)->nombre ;
        };
        QString cantReencarnaciones = QString::number(persona->reencarnaciones->cantItems);
        textoBitacora += personaIdString + "\t"
                         + persona -> nombre + "\t" +
                         persona -> apellido + "\t" +
                         persona -> pais + "\t" +
                         persona -> creencia + "\t" +
                         persona -> profesion + "\t" +
                         persona -> timestampNacimiento + "\t" +
                         personaPecadosTotales;
        lector->appendTextToFile(filePath, textoBitacora);
        lector->appendTextToFile(fileBitacora, textoBitacora);
    }
    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 12345); // Conectar al servidor

    if (socket.waitForConnected()) {
        qDebug() << "Conectado al servidor!";

        // Enviar un mensaje al servidor
        QString correo;
        QString filePath;
        correo = ui->correoElectronico->toPlainText();
        QString baseDir = QCoreApplication::applicationDirPath();
        filePath = baseDir + "/Archivostxt/muerteActual.txt";
        socket.write((correo + " " + filePath).toUtf8());
        socket.flush();

        // No esperamos respuesta, así que simplemente cerramos la conexión
        socket.disconnectFromHost();
        qDebug() << "Mensaje enviado y conexión cerrada.";
    } else {
        qDebug() << "Error al conectar al servidor!";
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    double prob = (ui->spinBox_2->value())/100.0;
    // qDebug() << prob;
    GenerarPandemia(_listaHumanos, prob);
    QString baseDir = QCoreApplication::applicationDirPath();
    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 12345); // Conectar al servidor

    if (socket.waitForConnected()) {
        qDebug() << "Conectado al servidor!";

        // Enviar un mensaje al servidor
        QString correo;
        QString filePath;
        correo = ui->correoElectronico->toPlainText();
        QString baseDir = QCoreApplication::applicationDirPath();
        filePath = baseDir + "/Archivostxt/muerteActual.txt";
        socket.write((correo + " " + filePath).toUtf8());
        socket.flush();

        // No esperamos respuesta, así que simplemente cerramos la conexión
        socket.disconnectFromHost();
        qDebug() << "Mensaje enviado y conexión cerrada.";
    } else {
        qDebug() << "Error al conectar al servidor!";
    }
}


void MainWindow::on_pushButton_7_clicked()
{
    EliminarId(arbolBinario, ui->spinBox_3->value(), ui->correoElectronico->toPlainText());
}


void MainWindow::on_pushButton_8_clicked()
{
    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 12345); // Conectar al servidor

    if (socket.waitForConnected()) {
        qDebug() << "Conectado al servidor!";

        // Enviar un mensaje al servidor
        QString correo;
        QString filePath;
        correo = ui->correoElectronico->toPlainText();
        QString baseDir = QCoreApplication::applicationDirPath();
        filePath = baseDir + "/Archivostxt/bitacoraMuerte.txt";
        socket.write((correo + " " + filePath).toUtf8());
        socket.flush();

        // No esperamos respuesta, así que simplemente cerramos la conexión
        socket.disconnectFromHost();
        qDebug() << "Mensaje enviado y conexión cerrada.";
    } else {
        qDebug() << "Error al conectar al servidor!";
    }
}


void MainWindow::on_btnConsultarHumanidad_clicked()
{
    ui->txbConsultas->clear();
    //TODO vaciar la consulta humanidad
    NodoOrdenado<Persona*>* personaNodo = _listaHumanos->primerNodo;
    while(personaNodo != nullptr){
        ui->txbConsultas->append((personaNodo->data->getInfo()));
        ui->txbConsultas->append("");
        personaNodo = personaNodo->next;
    }
}


void MainWindow::on_pushButton_9_clicked()
{

    lectorArchivos* lector = new lectorArchivos();
    QString baseDir = QCoreApplication::applicationDirPath();
    QString fileArbolAngeles = baseDir + "/Archivostxt/arbolAngeles.txt";
    lector->clearFile(fileArbolAngeles);
    arbolAngeles->ponerEnBitacora();
    //
}


void MainWindow::on_pushButton_10_clicked()
{
    ui->txbConsultas->clear();
    NodoOrdenado<Persona*>* personaNodo = _listaHumanos->primerNodo;
    int reencBuscadas = ui->spinBox_4->value();
    while(personaNodo != nullptr){
        if(personaNodo->data->reencarnaciones->size() == reencBuscadas){
            ui->txbConsultas->append((personaNodo->data->getInfo()));
        }
        personaNodo = personaNodo->next;
    }
}


void MainWindow::on_pushButton_11_clicked()
{
    ui->txbConsultas->clear();
    algoritmoPaisesPecadores(humanosCadaPais, ui->txbConsultas);
}


void MainWindow::on_pushButton_12_clicked()
{
    //arbolAngeles->getArbol(arbolBinario);
    lectorArchivos* lector = new lectorArchivos();
    QString baseDir = QCoreApplication::applicationDirPath();
    QString fileSalvacion = baseDir + "/Archivostxt/salvacion.txt";
    lector->clearFile(fileSalvacion);
    arbolAngeles->salvacion(arbolBinario);
    // Ahora quiero mandar esto al correo :)
    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 12345); // Conectar al servidor

    if (socket.waitForConnected()) {
        qDebug() << "Conectado al servidor!";

        // Enviar un mensaje al servidor
        QString correo;
        QString filePath;
        correo = ui->correoElectronico->toPlainText();
        QString baseDir = QCoreApplication::applicationDirPath();
        filePath = baseDir + "/Archivostxt/salvacion.txt";
        socket.write((correo + " " + filePath).toUtf8());
        socket.flush();

        // No esperamos respuesta, así que simplemente cerramos la conexión
        socket.disconnectFromHost();
        qDebug() << "Mensaje enviado y conexión cerrada.";
    } else {
        qDebug() << "Error al conectar al servidor!";
    }

}


void MainWindow::on_pushButton_13_clicked()
{
    HeapMuerte<Persona*> heap(ui->verHeapMuerte->value());

    for(int i = 0; i < _listaHumanos->size(); i++){
        if(_listaHumanos-> ver(i)->vivo){
            heap.agregarElemento(_listaHumanos->ver(i));
        }
    }

    heap.construirHeap();

    //qDebug() << heap.printHeap();

    // Configuración para habilitar el scroll en el QTextEdit
    ui->txbHeap->clear();
    ui->txbHeap->setWordWrapMode(QTextOption::NoWrap); // Evita el ajuste de línea
    ui->txbHeap->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded); // Scroll horizontal
    ui->txbHeap->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); // Scroll vertical
    ui->txbHeap->append(heap.printHeap());
}


