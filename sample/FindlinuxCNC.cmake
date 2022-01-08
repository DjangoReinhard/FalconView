#
# linuxCNC project import defintion
#
set(_ENV_linuxCNC "")
if(DEFINED ENV{EMC2_HOME})
    file(TO_CMAKE_PATH "$ENV{EMC2_HOME}" _ENV_linuxCNC)
endif()
if(_ENV_linuxCNC AND IS_DIRECTORY "${_ENV_linuxCNC}")
  set(LinuxCNC_DIR ${_ENV_linuxCNC} CACHE PATH "linuxCNC")
  if(EXISTS "${_ENV_linuxCNC}/include/linuxcnc.h")
    set(linuxCNC_INCLUDE_DIRS ${_ENV_linuxCNC}/include
                              ${_ENV_linuxCNC}/src
                              ${_ENV_linuxCNC}/src/emc/rs274ngc
                              ${_ENV_linuxCNC}/src/emc/tooldata
        )
  endif()
  if(EXISTS "${_ENV_linuxCNC}/lib/liblinuxcnc.a")
    set(linuxCNC_LIBRARIES ${_ENV_linuxCNC}/lib/liblinuxcnc.a
                           ${_ENV_linuxCNC}/lib/libposemath.so
                           ${_ENV_linuxCNC}/lib/libnml.so
                           ${_ENV_linuxCNC}/lib/librs274.so
                           ${_ENV_linuxCNC}/lib/liblinuxcncini.so
                           ${_ENV_linuxCNC}/lib/libpyplugin.so
                           ${_ENV_linuxCNC}/lib/liblinuxcnchal.so
                           ${_ENV_linuxCNC}/lib/libtooldata.so
        )
  endif()
endif()
