cmake_minimum_required(VERSION 3.16)
#--------------------------------   LIB   ------------------------------------
project(lcLib LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(FalconView)
add_library(FVlcLib STATIC
    control/LCInter.cpp
    control/axismask.cpp
    control/canonif.cpp
    control/canonifsettings.cpp
    control/commandwriter.cpp
    control/errorreader.cpp
    control/gcodehighlighter.cpp
    control/guicore.cpp
    control/guikernel.cpp
    control/helpengine.cpp
    control/positioncalculator.cpp
    control/statusreader.cpp
    model/lcproperties.cpp
    model/linecodes.cpp
    model/stupidtoolchangerif.cpp
    model/toolentry.cpp
    model/tooltable.cpp
    util/Geom_HelixData.cpp
    util/HHelixCurveAdaptor.cpp
    util/HelixCurveAdaptor.cpp
    util/HelixCurveAdaptor_CylinderEvaluator.cpp
    util/ally3d.cpp
    util/graphicfactory.cpp
    util/guikernelcreator.cpp
    util/pluginpagefactory.cpp
    view/abscenterwidget.cpp
    view/centerpage.cpp
    view/filemanager.cpp
    view/gcodeeditor.cpp
    view/gcodeinfo.cpp
    view/helpbrowser.cpp
    view/helpcontentwidget.cpp
    view/helpdockable.cpp
    view/helpkeywordwidget.cpp
    view/helpview.cpp
    view/jogbutton.cpp
    view/numlabel.cpp
    view/occtviewer.cpp
    view/pagestack.cpp
    view/settingsnb.cpp
    view/testEdit.cpp
    )
set(TS_FILES
    lcLib_de_DE.ts
    )
target_include_directories(FVlcLib
                           PUBLIC control
                           PUBLIC model
                           PUBLIC util
                           PUBLIC view
                           PRIVATE ../plugPages
                           )
target_link_libraries(FVlcLib
                      PRIVATE FVBaseLib
                      )
use_interface_libraries(FVlcLib
                        IFlinuxCNC
                        IFQt
                        IFOpenCASCADE
                        IFStandard
                        )
if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()


#  ##============================================================================
#  ## https://stackoverflow.com/questions/32183975/how-to-print-all-the-properties-of-a-target-in-cmake/56738858#56738858
#  ## https://stackoverflow.com/a/56738858/3743145
#  ## Get all properties that cmake supports
#  execute_process(COMMAND cmake --help-property-list OUTPUT_VARIABLE CMAKE_PROPERTY_LIST)
#  ## Convert command output into a CMake list
#  STRING(REGEX REPLACE ";" "\\\\;" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")
#  STRING(REGEX REPLACE "\n" ";" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")
#  list(REMOVE_DUPLICATES CMAKE_PROPERTY_LIST)
#  
#  function(print_target_properties tgt)
#      if(NOT TARGET ${tgt})
#        message("There is no target named '${tgt}'")
#        return()
#      endif()
#  
#      foreach (prop ${CMAKE_PROPERTY_LIST})
#          string(REPLACE "<CONFIG>" "${CMAKE_BUILD_TYPE}" prop ${prop})
#          get_target_property(propval ${tgt} ${prop})
#          if (propval)
#              message ("${tgt} ${prop} = ${propval}")
#          endif()
#      endforeach(prop)
#  endfunction(print_target_properties)
#  ##----------------------------------------------------------------------------
#  
#  message("    --------")
#  print_target_properties(IFlinuxCNC)
#  message("    --------")
#  print_target_properties(IFQt)
#  message("    --------")
#  print_target_properties(IFOpenCASCADE)
#  message("    --------")
#  print_target_properties(IFStandard)
#  message("    --------")
#  print_target_properties(FVlcLib)
#  message("    --------")
