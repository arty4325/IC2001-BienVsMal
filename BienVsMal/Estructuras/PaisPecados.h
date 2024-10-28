#ifndef PAISPECADOS_H
#define PAISPECADOS_H
#include <QString>

struct PaisPecados{
    QString pais;
    int pecados;

    PaisPecados(QString _pais){
        pais = _pais;
        pecados = 0;
    }

    bool operator<(const PaisPecados &other) const {
        return pecados < other.pecados;
    }
};

#endif // PAISPECADOS_H
