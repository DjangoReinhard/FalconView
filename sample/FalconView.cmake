#
# common settings for FalconView
#
include(GNUInstallDirs)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_BUILD_TYPE  Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_definitions(USE_PLUGINS)
add_compile_definitions(QT_DISABLE_DEPRECATED_BEFORE=0x060000)
add_compile_definitions(QT_USE_QSTRINGBUILDER)


