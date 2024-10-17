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
    switch (option) {
    case 1:
        filePath = baseDir + "/Archivostxt/apellidos.txt";
        break;
    case 2:
        filePath = baseDir + "/Archivostxt/nombres.txt";
        break;
    case 3:
        filePath = baseDir + "/Archivostxt/paises.txt";
        break;
    case 4:
        filePath = baseDir + "/Archivostxt/profesiones.txt";
        break;
    case 5:
        filePath = baseDir + "/Archivostxt/religiones.txt";
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
