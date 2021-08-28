QT       += core gui uitools testlib

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

CONFIG += c++11 testcase no_testcase_installs

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH = src/model src/util src/view src

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/model/positionmodel.cpp \
    src/model/valuemodel.cpp \
    src/view/labeladapter.cpp \
    src/view/gcodeeditor.cpp \
    src/view/positionwidget.cpp \
    src/view/speedinfowidget.cpp \
    src/view/toolinfowidget.cpp \
    src/util/axismask.cpp \
    src/util/gcodehighlighter.cpp \
    src/test/testaxismask.cpp \

HEADERS += \
    src/mainwindow.h \
    src/model/positionmodel.h \
    src/model/valuemodel.h \
    src/view/gcodeeditor.h \
    src/view/labeladapter.h \
    src/view/positionwidget.h \
    src/view/speedinfowidget.h \
    src/view/toolinfowidget.h \
    src/util/axismask.h \
    src/util/gcodehighlighter.h \
    src/util/portable-file-dialogs.h \
    src/test/testaxismask.h \

FORMS += \
    src/UI/Position.ui \
    src/UI/SpeedInfo.ui \
    src/UI/ToolInfo.ui \
    src/UI/mainwindow.ui

TRANSLATIONS += \
    src/i18n/QtScreen_de_DE.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    src/i18n/QtScreen_de_DE.ts
