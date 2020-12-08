QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/dataStructures/CircularList.cpp \
    Model/dataStructures/LinkedList.cpp \
    Model/dataStructures/Queue.cpp \
    Model/dataStructures/node.cpp \
    Model/thanos.cpp \
    main.cpp \
    Controller/mainwindow.cpp

HEADERS += \
    Controller/mainwindow.h \
    Model/dataStructures/CircularList.h \
    Model/dataStructures/LinkedList.h \
    Model/dataStructures/Queue.h \
    Model/dataStructures/node.h \
    Model/thanos.h

FORMS += \
    View/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
