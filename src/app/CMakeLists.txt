cmake_minimum_required(VERSION 3.16)
project(FalconView LANGUAGES CXX)
set(CMAKE_PREFIX_PATH "/opt/qt5.15/5.15.2/gcc_64" CACHE PATH "Qt5 Toolkit")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/local/lib/cmake/opencascade")
set(LinuxCNC_DIR      "/usr/local/src/linuxcnc-deb11" CACHE PATH "LinuxCNC")
set(CMAKE_BUILD_TYPE  Debug)
add_compile_definitions(USE_PLUGINS)

find_package(Qt5 REQUIRED COMPONENTS
             Gui
             Widgets
             Core
             Sql
             UiTools
             Xml
             LinguistTools
             )
find_package(OpenCASCADE COMPONENTS
             FoundationClasses
             ModelingData
             ModelingAlgorithms
             Visualization
             ApplicationFramework
             Draw
             PATHS ${OpenCASCADE_DIR} NO_DEFAULT_PATH
             )
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    main.cpp
    control/abstractcondition.cpp
    control/andcondition.cpp
    control/dynaaction.cpp
    control/equalcondition.cpp
    control/falsecondition.cpp
    control/greatercondition.cpp
    control/mainwindow.cpp
    control/multistatetoolbutton.cpp
    control/notcondition.cpp
    control/orcondition.cpp
    control/smallercondition.cpp
    control/testmain.cpp
    control/truecondition.cpp
    model/falconviewdb.cpp
    model/tool.cpp
    model/toolcategory.cpp
    util/multistateaction.cpp
    view/dockable.cpp
    view/micon.cpp
    view/plugindialog.cpp
    )

set(FORMS
    UI/mainwindow.ui
    )

set(TS_FILES
    i18n/FalconView_de_DE.ts
    )

add_executable(FalconView ${SOURCES} ${FORMS})
target_include_directories(FalconView
                           PUBLIC UI
                           PUBLIC control
                           PUBLIC model
                           PUBLIC util
                           PUBLIC view
                           PRIVATE ../plugPages
                           PRIVATE ${LinuxCNC_DIR}/include
                           PRIVATE ${LinuxCNC_DIR}/src
                           PRIVATE ${LinuxCNC_DIR}/src/emc/rs274ngc
                           PRIVATE ${LinuxCNC_DIR}/src/emc/tooldata
                           PRIVATE ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
                           PRIVATE ${OpenCASCADE_INCLUDE_DIR}
                           )
target_link_libraries(FalconView
                      PRIVATE favi_BaseLib
                      PRIVATE favi_lcLib
                      PRIVATE Qt${QT_VERSION_MAJOR}::Gui
                      PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                      PRIVATE Qt${QT_VERSION_MAJOR}::Core
                      PRIVATE Qt${QT_VERSION_MAJOR}::Sql
                      PRIVATE Qt${QT_VERSION_MAJOR}::UiTools
                      PRIVATE Qt${QT_VERSION_MAJOR}::Xml
                      PRIVATE ${LinuxCNC_DIR}/lib/linuxcnc
                      PRIVATE ${LinuxCNC_DIR}/lib/posemath
                      PRIVATE ${LinuxCNC_DIR}/lib/nml
                      PRIVATE ${LinuxCNC_DIR}/lib/rs274
                      PRIVATE ${LinuxCNC_DIR}/lib/linuxcncini
                      PRIVATE ${LinuxCNC_DIR}/lib/pyplugin
                      PRIVATE ${LinuxCNC_DIR}/lib/linuxcnchal
                      PRIVATE ${LinuxCNC_DIR}/lib/tooldata
                      PRIVATE m stdc++ boost_python39 python3.9 crypt pthread dl util
                      TKernel TKMath TKService TKV3d TKOpenGl
                      TKBRep TKIGES TKSTL TKVRML TKSTEP TKSTEPAttr TKSTEP209
                      TKSTEPBase TKGeomBase TKGeomAlgo TKG3d TKG2d
                      TKXSBase TKShHealing TKHLR TKTopAlgo TKMesh TKPrim
                      TKCDF TKBool TKBO TKFillet TKOffset TKLCAF TKCAF TKVCAF
                      TKBin TKXml
                      )

if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()


