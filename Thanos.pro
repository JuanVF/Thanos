QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/Avengers/antman.cpp \
    Model/Avengers/ironman.cpp \
    Model/Avengers/spiderman.cpp \
    Model/Enemies/blackdwarf.cpp \
    Model/Enemies/corvusGlaive.cpp \
    Model/Enemies/ebony.cpp \
    Model/Enemies/hashthanos.cpp \
    Model/Enemies/midnight.cpp \
    Model/Mundo/Acciones.cpp \
    Model/Mundo/RangoEtario.cpp \
    Model/Enemies/Nebula.cpp \
    Model/Mundo/paisesvisitados.cpp \
    Model/dataStructures/CircularList.cpp \
    Model/dataStructures/HashMap.cpp \
    Model/dataStructures/Heap.cpp \
    Model/dataStructures/LinkedList.cpp \
    Model/dataStructures/Queue.cpp \
    Model/dataStructures/Tree.cpp \
    Model/dataStructures/TreeNode.cpp \
    Model/dataStructures/datastructures.cpp \
    Model/dataStructures/node.cpp \
    Model/Mundo/ejercicio.cpp \
    Model/emailsender.cpp \
    Model/Mundo/familia.cpp \
    Model/filemanager.cpp \
    Model/jsonmanager.cpp \
    Model/Mundo/mundo.cpp \
    Model/Mundo/persona.cpp \
    Model/thanos.cpp \
    Model/Mundo/ubicacion.cpp \
    Model/Avengers/thor.cpp \
    Model/utils.cpp \
    main.cpp \
    Controller/mainwindow.cpp

HEADERS += \
    Controller/mainwindow.h \
    Model/Avengers/antman.h \
    Model/Avengers/ironman.h \
    Model/Avengers/spiderman.h \
    Model/Enemies/blackdwarf.h \
    Model/Enemies/corvusGlaive.h \
    Model/Enemies/ebony.h \
    Model/Enemies/hashthanos.h \
    Model/Enemies/midnight.h \
    Model/Mundo/Acciones.h \
    Model/Mundo/RangoEtario.h \
    Model/Enemies/Nebula.h \
    Model/Mundo/paisesvisitados.h \
    Model/dataStructures/CircularList.h \
    Model/dataStructures/HashMap.h \
    Model/dataStructures/Heap.h \
    Model/dataStructures/LinkedList.h \
    Model/dataStructures/Queue.h \
    Model/dataStructures/Tree.h \
    Model/dataStructures/TreeNode.h \
    Model/dataStructures/datastructures.h \
    Model/dataStructures/node.h \
    Model/Mundo/ejercicio.h \
    Model/emailsender.h \
    Model/Mundo/familia.h \
    Model/filemanager.h \
    Model/jsonmanager.h \
    Model/Mundo/mundo.h \
    Model/Mundo/persona.h \
    Model/thanos.h \
    Model/Mundo/ubicacion.h \
    Model/Avengers/thor.h \
    Model/utils.h

FORMS += \
    View/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    paises.json
