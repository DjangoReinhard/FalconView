QT       += core gui uitools testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 testcase no_testcase_installs

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    axismask.cpp \
    gcodehighlighter.cpp \
    gcodemodel.cpp \
    labeladapter.cpp \
    main.cpp \
    mainwindow.cpp \
    positionmodel.cpp \
    positionwidget.cpp \
    testaxismask.cpp \
    valuemodel.cpp

HEADERS += \
    axismask.h \
    gcodehighlighter.h \
    gcodemodel.h \
    labeladapter.h \
    mainwindow.h \
    positionmodel.h \
    positionwidget.h \
    testaxismask.h \
    valuemodel.h

FORMS += \
    Position.ui \
    mainwindow.ui

TRANSLATIONS += \
    QtScreen_de_DE.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
