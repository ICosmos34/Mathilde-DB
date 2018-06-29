#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Magazzino
TEMPLATE = app


SOURCES += main.cpp\
    iofile.cpp \
    account.cpp \
    memorymanager.cpp \
    product.cpp \
    memory.cpp \
    adminui.cpp \
    controller.cpp \
    login.cpp \
    dbaccess.cpp \
    changeui.cpp \
    editpassword.cpp

HEADERS  += \
    main.h \
    iofile.h \
    account.h \
    definition.h \
    memorymanager.h \
    product.h \
    memory.h \
    adminui.h \
    controller.h \
    login.h \
    dbaccess.h \
    changeui.h \
    editpassword.h

FORMS    += \
    adminui.ui \
    login.ui \
    dbaccess.ui \
    changeui.ui \
    editpassword.ui

RESOURCES += \
    res.qrc
