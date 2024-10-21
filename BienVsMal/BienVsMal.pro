QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Lector/lectorarchivos.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Estructuras/arbolBinario.h \
    Estructuras/cubetas.h \
    Estructuras/hashmap.h \
    Estructuras/heapMuerte.h \
    Estructuras/listaOrdenada.h \
    Estructuras/nodoAB.h \
    Estructuras/nodoHash.h \
    Estructuras/nodoOrdenado.h \
    Human/algoritmoAmigos.h \
    Human/hacerPecados.h \
    Human/persona.h \
    Human/personaCreator.h \
    Lector/lectorarchivos.h \
    mainwindow.h \
    reencarnacion.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Archivos/apellidos.txt \
    Archivos/paises.txt \
    Archivos/profesiones.txt \
    Archivos/religiones.txt
