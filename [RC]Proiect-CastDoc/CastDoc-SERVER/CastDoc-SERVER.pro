TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += thread c++11

SOURCES += \
    ../server.c

include(deployment.pri)
qtcAddDeployment()

DISTFILES += \
    ../castdoc.cfg

HEADERS += \
    ../functions.h
