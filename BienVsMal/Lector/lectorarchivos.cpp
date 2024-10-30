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
    // qDebug() << baseDir;
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
    case 6:
        filePath = baseDir + "/Archivostxt/bitacoraMuerte.txt";
        break;
    default:
        return "";
    }

    // Intentar abrir el archivo seleccionado
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No se pudo abrir el archivo: " << filePath;
        return "";
    }

    QTextStream in(&file);
    QString content;
    int currentLine = 0;

    // Leer línea por línea hasta alcanzar el número de líneas deseado o hasta el final si cant es -1
    while (!in.atEnd() && (cant == -1 || currentLine < cant)) {
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

void lectorArchivos::clearFile(const QString& filePath) {
    QFile file(filePath);

    // Intentar abrir el archivo en modo de solo escritura (WriteOnly) sin Append para que se limpie
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Archivo abierto y vaciado correctamente, no es necesario escribir nada
        file.close();  // Cerrar el archivo
    } else {
        qDebug() << "No se pudo abrir el archivo para vaciarlo: " << filePath;
    }
}

void lectorArchivos::deleteLineFromFile(const QString& filePath, const QString& lineToDelete) {
    QFile file(filePath);

    // Verificar si el archivo existe y se puede leer
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No se pudo abrir el archivo para leer: " << filePath;
        return;
    }

    // Leer todas las líneas del archivo
    QStringList lines;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        // Agregar solo las líneas que no coinciden con la línea a eliminar
        if (line != lineToDelete) {
            lines << line;
        }
    }
    file.close();

    // Reescribir el archivo con las líneas restantes
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream out(&file);
        for (const QString& line : lines) {
            out << line << "\n";
        }
        file.close();
        // qDebug() << "Línea eliminada del archivo:" << lineToDelete;
    } else {
        qDebug() << "No se pudo abrir el archivo para escribir: " << filePath;
    }
}


