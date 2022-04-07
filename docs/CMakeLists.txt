cmake_minimum_required(VERSION 3.16)
#---------------------------------   HELP   ----------------------------------
project(Help)
#-----------------------------------------------------------------------------
#include(FalconView)
include(Interface)
set(DISTFILES
    src/filemanager.md
    src/fixturemanager.md
    src/gcode.md
    src/index.md
    src/info.md
    src/integration.md
    src/jogview.md
    src/lctooltable.md
    src/mdiedit.md
    src/patheditor.md
    src/preferences.md
    src/preview.md
    src/reference.md
    src/settingsnotebook.md
    src/sicodes.md
    src/sipos.md
    src/sispeed.md
    src/sitool.md
    src/sysevents.md
    src/tbappmode.md
    src/tbextend.md
    src/tbmachine.md
    src/tbrunmode.md
    src/testeditor.md
    src/toolbars.md
    src/tooledit.md
    src/toolmanager.md
    )
set(XDistSrc)
foreach(_f ${DISTFILES})
    string(REPLACE ".md" "_de.md" _xf ${_f})
    list(APPEND XDistSrc ${_f})
    list(APPEND XDistSrc ${_xf})
endforeach()
add_custom_target(HelpFile ALL
                  DEPENDS FalconView.qzh
                  )
add_custom_command(OUTPUT FalconView.qzh
    COMMAND ${PROJECT_SOURCE_DIR}/cgenHelp ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR} ${XDistSrc}
    DEPENDS ${XDistSrc}
    COMMENT "compile docs for help file"
    )

