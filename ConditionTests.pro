QT       += core gui uitools testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 testcase no_testcase_installs

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += src/util \
               src/model

SOURCES = \
    src/test/testengine.cpp \
    src/util/andcondition.cpp \
    src/model/valuemodel.cpp \
    src/util/abstractcondition.cpp \
    src/util/equalcondition.cpp \
    src/util/greatercondition.cpp \
    src/util/notcondition.cpp \
    src/util/orcondition.cpp \
    src/util/smallercondition.cpp

HEADERS = \
    src/model/valuemodel.h \
    src/util/abstractcondition.h \
    src/util/andcondition.h \
    src/util/equalcondition.h \
    src/util/greatercondition.h \
    src/util/notcondition.h \
    src/util/orcondition.h \
    src/util/smallercondition.h


unix:!mac {
  LIBS += -Wl,-rpath=$${_PRO_FILE_PWD_}/lc/lib
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

