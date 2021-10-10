QT       += core gui uitools sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = QtUi

INCLUDEPATH += \
    src      \
    src/model \
    src/nml  \
    src/util \
    src/view \
    src/view/dockable \
    lc/include \
    lc/src \

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/model/config.cpp \
    src/model/dbconnection.cpp \
    src/model/direntry.cpp \
    src/model/dirmodel.cpp \
    src/model/filemodel.cpp \
    src/model/gcodeinfo.cpp \
    src/model/lcproperties.cpp \
    src/model/positioncalculator.cpp \
    src/model/toolcategory.cpp \
    src/model/toolcategorymodel.cpp \
    src/model/tool.cpp \
    src/model/toolentry.cpp \
    src/model/toolmodel.cpp \
    src/model/tooltable.cpp \
    src/model/valuemanager.cpp \
    src/model/valuemodel.cpp \
    src/nml/statusreader.cpp \
    src/util/abstractcondition.cpp \
    src/util/axismask.cpp \
    src/util/equalcondition.cpp \
    src/util/gcodehighlighter.cpp \
    src/util/greatercondition.cpp \
    src/util/smallercondition.cpp \
    src/view/dockable/curcodesdockable.cpp \
    src/view/dockable/dockable.cpp \
    src/view/dockable/editordockable.cpp \
    src/view/dockable/maindockable.cpp \
    src/view/dockable/positiondockable.cpp \
    src/view/dockable/speedinfodockable.cpp \
    src/view/dockable/toolinfodockable.cpp \
    src/view/dynwidget.cpp \
    src/view/filemanager.cpp \
    src/view/gcodeeditor.cpp \
    src/view/gcodeviewer.cpp \
    src/view/labeladapter.cpp \
    src/view/mainview.cpp \
    src/view/micon.cpp \
    src/view/overlay.cpp \
    src/view/pweditor.cpp \
    src/view/settingswidget.cpp \
    src/view/splitwidget.cpp \
    src/view/tooleditor.cpp \
    src/view/toolmanager.cpp \

HEADERS += \
    src/mainwindow.h \
    src/model/config.h \
    src/model/dbconnection.h \
    src/model/direntry.h \
    src/model/dirmodel.h \
    src/model/filemodel.h \
    src/model/gcodeinfo.h \
    src/model/lcproperties.h \
    src/model/positioncalculator.h \
    src/model/toolcategory.h \
    src/model/toolcategorymodel.h \
    src/model/toolentry.h \
    src/model/tool.h \
    src/model/toolmodel.h \
    src/model/tooltable.h \
    src/model/valuemanager.h \
    src/model/valuemodel.h \
    src/nml/insulatePose.h \
    src/nml/statusreader.h \
    src/util/abstractcondition.h \
    src/util/axismask.h \
    src/util/equalcondition.h \
    src/util/gcodehighlighter.h \
    src/util/greatercondition.h \
    src/util/KeyCodes.h \
    src/util/smallercondition.h \
    src/view/dockable/curcodesdockable.h \
    src/view/dockable/dockable.h \
    src/view/dockable/editordockable.h \
    src/view/dockable/maindockable.h \
    src/view/dockable/positiondockable.h \
    src/view/dockable/speedinfodockable.h \
    src/view/dockable/toolinfodockable.h \
    src/view/dynwidget.h \
    src/view/filemanager.h \
    src/view/gcodeeditor.h \
    src/view/gcodeviewer.h \
    src/view/labeladapter.h \
    src/view/mainview.h \
    src/view/micon.h \
    src/view/overlay.h \
    src/view/pweditor.h \
    src/view/settingswidget.h \
    src/view/splitwidget.h \
    src/view/tooleditor.h \
    src/view/toolmanager.h \

FORMS += \
    src/UI/CurCodes.ui \
    src/UI/GCodeEditor.ui \
    src/UI/mainwindow.old.ui \
    src/UI/mainwindow.ui \
    src/UI/Overlay.ui \
    src/UI/Position.ui \
    src/UI/Settings.ui \
    src/UI/SpeedInfo.ui \
    src/UI/ToolEditor.ui \
    src/UI/ToolInfo.ui \

unix:!mac {
  LIBS += -Wl,-rpath=$${_PRO_FILE_PWD_}/lc/lib
  QMAKE_CXXFLAGS += -std=gnu++11
}

LIBS += \
  -L$${_PRO_FILE_PWD_}/lc/lib \
  -lm \
  -llinuxcnc \
  -lnml

TRANSLATIONS += \
    src/i18n/QtUi_de_DE.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    src/i18n/QtUi_de_DE.ts

RESOURCES += QtUi.qrc
