QT += core network
QT -= gui

TARGET = rest-client-test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    client.cpp \
    parser.cpp

HEADERS += \
    client.h \
    logging.h \
    data.h \
    parser.h
