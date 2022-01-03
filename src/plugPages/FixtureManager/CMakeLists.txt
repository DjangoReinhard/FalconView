cmake_minimum_required(VERSION 3.16)
project(FixtureManager LANGUAGES CXX)
set(CMAKE_BUILD_TYPE  Debug)
add_compile_definitions(USE_PLUGINS)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    fixturemanager.cpp
    fixtureedit.cpp
    )
set(FORMS
    Fixture.ui
    )
set(TS_FILES
    fixture_de_DE.ts
    )
add_library(ppFixtureManager SHARED ${SOURCES} ${FORMS})
target_include_directories(ppFixtureManager
                           PRIVATE ${LinuxCNC_DIR}/include
                           PRIVATE ${LinuxCNC_DIR}/src
                           PRIVATE ${LinuxCNC_DIR}/src/emc/rs274ngc
                           PRIVATE ${LinuxCNC_DIR}/src/emc/tooldata
                           PRIVATE ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
                           PRIVATE ${OpenCASCADE_INCLUDE_DIR}
                           )
target_link_libraries(ppFixtureManager
                      PRIVATE FVBaseLib
                      PRIVATE FVlcLib
                      PRIVATE Qt${QT_VERSION_MAJOR}::Gui
                      PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                      PRIVATE Qt${QT_VERSION_MAJOR}::Core
                      PRIVATE Qt${QT_VERSION_MAJOR}::Sql
                      PRIVATE Qt${QT_VERSION_MAJOR}::UiTools
                      PRIVATE Qt${QT_VERSION_MAJOR}::Xml
                      PRIVATE ${LIB_LC} ${LIB_PM} ${LIB_NML} ${LIB_RS}
                      PRIVATE ${LIB_LCI} ${LIB_PP} ${LIB_LH} ${LIB_TD}
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


