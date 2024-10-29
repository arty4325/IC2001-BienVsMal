#ifndef LECTORARCHIVOS_H
#define LECTORARCHIVOS_H

#include <QString>

class lectorArchivos
{
public:
    lectorArchivos();
    QString read(int option, int cant);
    void appendTextToFile(const QString& filePath, const QString& textToAdd);
    void clearFile(const QString& filePath);
    void deleteLineFromFile(const QString& filePath, const QString& lineToDelete);
};

#endif // LECTORARCHIVOS_H
