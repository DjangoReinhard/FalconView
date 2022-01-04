cmake_minimum_required(VERSION 3.16)
#---------------------------------   HELP   ----------------------------------
project(Help)
#-----------------------------------------------------------------------------
include(FalconView)
set(SOURCES
    src/filemanager.md
    src/fixturemanager.md
    src/index.md
    src/info.md
    src/integration.md
    src/jogview.md
    src/lctooltable.md
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
set(XSources)
foreach(_f ${SOURCES})
    string(REPLACE ".md" "_de.md" _xf ${_f})
    list(APPEND XSources ${_f})
    list(APPEND XSources ${_xf})
endforeach()
add_custom_target(HelpFile)
add_custom_command(TARGET HelpFile POST_BUILD
    COMMAND ${PROJECT_SOURCE_DIR}/cgenHelp ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR} ${XSources}
    DEPENDS ${XSources}
    COMMENT "compile docs for help file"
    )

