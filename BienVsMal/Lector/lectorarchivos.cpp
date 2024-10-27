#include "lectorarchivos.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QCoreApplication>

lectorArchivos::lectorArchivos() {}

QString lectorArchivos::read(int option, int cant) {
    QString filePath;

    // Obtener el directorio de la aplicación
    QString baseDir = QCoreApplication::applicationDirPath();

    // Seleccionar archivo basado en el número de opción
    qDebug() << baseDir;
    switch (option) {
    case 1:
        filePath = baseDir + "/Archivostxt/nombres.txt";
        break;
    case 2:
        filePath = baseDir + "/Archivostxt/apellidos.txt";
        break;
    case 3:
        filePath = baseDir + "/Archivostxt/paises.txt";
        break;
    case 4:
        filePath = baseDir + "/Archivostxt/religiones.txt";
        break;
    case 5:
        filePath = baseDir + "/Archivostxt/profesiones.txt";
        break;
    default:
        return "";
    }

    //qDebug() << "Ruta del archivo: " << filePath;  // Depuración de la ruta del archivo

    // Intentar abrir el archivo seleccionado
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // No se pudo abrir el archivo seleccionado
        qDebug() << "No se pudo abrir el archivo: " << filePath;
        return "";
    }

    QTextStream in(&file);
    QString content;
    int currentLine = 0;

    // Leer línea por línea hasta alcanzar el número de líneas deseado
    while (!in.atEnd() && currentLine < cant) {
        QString line = in.readLine();  // Leer una línea
        content += line + "\n";        // Añadirla al contenido a devolver
        currentLine++;                 // Incrementar el contador de líneas
    }

    file.close();  // Cerrar el archivo
    return content.trimmed();  // Devolver el contenido leído
}

void lectorArchivos::appendTextToFile(const QString& filePath, const QString& textToAdd) { // Esta funcion lo que quiere es a un archivo, agregarle texto
    QFile file(filePath);
    QDir dir = QFileInfo(filePath).absoluteDir();

    // Si el filePath que se esta pasando no existe, es creado
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            // Esto ocurre si no se pudo crear el directorio por alguna razon
            return;
        }
    }

    // Se abre el archivo, observe que esta en writeOnly, y Append para que no se pierda lo qeu se tiene
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << textToAdd << "\n";  // Escribe el texto en el archivo y añade un salto de línea
        file.close();
    } else {
        // Esto se ejecuta si no se pudo completar la accion
    }
}
