QT       += core gui uitools testlib \
    widgets

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

CONFIG += c++11 testcase no_testcase_installs

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += src/model \
               src/util \
               src/view \
               src

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/model/positionmodel.cpp \
    src/model/valuemodel.cpp \
    src/view/editordockable.cpp \
    src/view/labeladapter.cpp \
    src/view/gcodeeditor.cpp \
    src/view/overlay.cpp \
    src/view/positiondockable.cpp \
    src/view/settingswidget.cpp \
    src/view/speedinfodockable.cpp \
    src/util/axismask.cpp \
    src/util/gcodehighlighter.cpp \
    src/test/testaxismask.cpp \
    src/view/toolinfodockable.cpp

HEADERS += \
    src/mainwindow.h \
    src/model/positionmodel.h \
    src/model/valuemodel.h \
    src/view/editordockable.h \
    src/view/gcodeeditor.h \
    src/view/labeladapter.h \
    src/view/overlay.h \
    src/view/positiondockable.h \
    src/view/settingswidget.h \
    src/view/speedinfodockable.h \
    src/util/axismask.h \
    src/util/gcodehighlighter.h \
    src/util/portable-file-dialogs.h \
    src/test/testaxismask.h \
    src/view/toolinfodockable.h

FORMS += \
    src/UI/GCodeEditor.ui \
    src/UI/Overlay.ui \
    src/UI/Position.ui \
    src/UI/Settings.ui \
    src/UI/SpeedInfo.ui \
    src/UI/ToolInfo.ui \
    src/UI/mainwindow.ui

TRANSLATIONS += \
    src/i18n/QtUi_de_DE.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    src/i18n/QtUi_de_DE.ts

RESOURCES += QtUi.qrc

