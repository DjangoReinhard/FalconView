#
# linuxCNC project import defintion
#
set(_linuxCNC "")
if(DEFINED ENV{EMC2_HOME})
  file(TO_CMAKE_PATH "$ENV{EMC2_HOME}" _linuxCNC)
  if(_linuxCNC AND IS_DIRECTORY "${_linuxCNC}")
    set(linuxCNC_DIR ${_linuxCNC} CACHE PATH "linuxCNC")
  endif()
endif()

if(linuxCNC_DIR AND IS_DIRECTORY "${linuxCNC_DIR}")
  add_library(IFlinuxCNC INTERFACE)
  add_library(LinuxCNC::IFlinuxCNC ALIAS IFlinuxCNC)
  if(EXISTS "${linuxCNC_DIR}/include/linuxcnc.h")
    target_include_directories(IFlinuxCNC SYSTEM BEFORE
                               INTERFACE ${linuxCNC_DIR}/include
                               INTERFACE ${linuxCNC_DIR}/src
                               INTERFACE ${linuxCNC_DIR}/src/hal
                               INTERFACE ${linuxCNC_DIR}/src/emc/rs274ngc
                               INTERFACE ${linuxCNC_DIR}/src/emc/tooldata
                               INTERFACE /usr/include/python3.9
                               )
  endif()
  if(EXISTS "${linuxCNC_DIR}/lib/liblinuxcnc.a")
    target_link_libraries(IFlinuxCNC
                          INTERFACE ${linuxCNC_DIR}/lib/liblinuxcnc.a
                          INTERFACE ${linuxCNC_DIR}/lib/libposemath.so
                          INTERFACE ${linuxCNC_DIR}/lib/libnml.so
                          INTERFACE ${linuxCNC_DIR}/lib/librs274.so
                          INTERFACE ${linuxCNC_DIR}/lib/liblinuxcncini.so
                          INTERFACE ${linuxCNC_DIR}/lib/libpyplugin.so
                          INTERFACE ${linuxCNC_DIR}/lib/liblinuxcnchal.so
                          INTERFACE ${linuxCNC_DIR}/lib/libtooldata.so
                          )
    target_link_directories(IFlinuxCNC BEFORE
                            INTERFACE ${linuxCNC_DIR}/lib
                            )
  endif()
else()
    set(linuxCNC_DIR-NOT_FOUND "" CACHE PATH "linuxCNC")
endif()
