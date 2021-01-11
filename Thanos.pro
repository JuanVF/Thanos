QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/Acciones.cpp \
    Model/RangoEtario.cpp \
    Model/Enemies/Nebula.cpp \
    Model/Enums/eGenero.cpp \
    Model/dataStructures/CircularList.cpp \
    Model/dataStructures/HashMap.cpp \
    Model/dataStructures/LinkedList.cpp \
    Model/dataStructures/Queue.cpp \
    Model/dataStructures/Tree.cpp \
    Model/dataStructures/TreeNode.cpp \
    Model/dataStructures/node.cpp \
    Model/ejercicio.cpp \
    Model/emailsender.cpp \
    Model/estado.cpp \
    Model/familia.cpp \
    Model/genero.cpp \
    Model/jsonmanager.cpp \
    Model/Mundo/mundo.cpp \
    Model/Mundo/persona.cpp \
    Model/thanos.cpp \
    Model/Mundo/ubicacion.cpp \
    Model/utils.cpp \
    main.cpp \
    Controller/mainwindow.cpp

HEADERS += \
    Controller/mainwindow.h \
<<<<<<< HEAD
    Model/Acciones.h \
    Model/RangoEtario.h \
=======
    Model/Enemies/Nebula.h \
    Model/Enums/eGenero.h \
>>>>>>> JuanBranch
    Model/dataStructures/CircularList.h \
    Model/dataStructures/HashMap.h \
    Model/dataStructures/LinkedList.h \
    Model/dataStructures/Queue.h \
    Model/dataStructures/Tree.h \
    Model/dataStructures/TreeNode.h \
    Model/dataStructures/node.h \
    Model/ejercicio.h \
    Model/emailsender.h \
    Model/estado.h \
    Model/familia.h \
    Model/genero.h \
    Model/jsonmanager.h \
    Model/Mundo/mundo.h \
    Model/Mundo/persona.h \
    Model/thanos.h \
    Model/Mundo/ubicacion.h \
    Model/utils.h

FORMS += \
    View/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    paises.json
