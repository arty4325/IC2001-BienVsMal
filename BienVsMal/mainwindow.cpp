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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lectorArchivos* lector = new lectorArchivos();
    QString baseDir = QCoreApplication::applicationDirPath();
    QString fileBitacora = baseDir + "/Archivostxt/bitacoraMuerte.txt";
    lector->clearFile(fileBitacora);
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
    PersonaCreator* personaCreator = new PersonaCreator(10000, _listaHumanos, humanosCadaPais);
    personaCreator->generarPersonas(100, 10, 100, 10, 10);
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
    //quite lo que habia dicho de imprimir que podria ser lo que lo hace lento
}


void MainWindow::on_pushButton_5_clicked()
{
    HeapMuerte<Persona*> heap(-1);

    for(int i = 0; i < _listaHumanos->size(); i++){
        if(_listaHumanos-> ver(i)->vivo){
            heap.agregarElemento(_listaHumanos->ver(i));
        }
    }

    heap.construirHeap();
    ListaOrdenada<Persona*> personasRecorridas = heap.recorrerNiveles(4);

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
        textoBitacora += personaIdString + "    "
                         + persona -> nombre + "    " +
                         persona -> apellido + "    " +
                         persona -> pais + "    " +
                         persona -> creencia + "    " +
                         persona -> profesion + "    " +
                         persona -> timestampNacimiento + "    " +
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
    qDebug() << prob;
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

    //TODO vaciar la consulta humanidad
    NodoOrdenado<Persona*>* personaNodo = _listaHumanos->primerNodo;
    QString baseDir = QCoreApplication::applicationDirPath();
    QString path = baseDir + "/Archivostxt/humanidad.txt";
    lectorArchivos* lector = new lectorArchivos();
    qDebug() << path;
    while(personaNodo != nullptr){
        lector->appendTextToFile(path, personaNodo->data->getInfo());
        personaNodo = personaNodo->next;
    }
}


void MainWindow::on_pushButton_9_clicked()
{
    // arbolAngeles->ponerEnBitacora();
}


void MainWindow::on_pushButton_10_clicked()
{
    NodoOrdenado<Persona*>* personaNodo = _listaHumanos->primerNodo;
    int reencBuscadas = ui->spinBox_4->value();
    while(personaNodo != nullptr){
        if(personaNodo->data->reencarnaciones->size() == reencBuscadas){
            qDebug() << personaNodo->data->getInfo();
        }
        personaNodo = personaNodo->next;
    }
}


void MainWindow::on_pushButton_11_clicked()
{
    algoritmoPaisesPecadores(humanosCadaPais);
}

