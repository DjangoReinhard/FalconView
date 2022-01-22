# FalconView
## Extending FalconView

**FalconView** was designed so that it can be easily extended.
Let's have a look at project layout first:

```
FalconView
+--docs                 Scripts for Helpfile generation
|  +--src               Helpfiles
+--res                  common resources
|
+--src          
   +--app               the application
   |
   +--baselib           basic stuff for plugins and application    
   +--guiLib            Highlevel stuff for plugins and application    
   +--lcLib             linuxCNC dependant stuff used by app and plugins
   |
   +--nbPages           plugins that become notebook pages (for setup)
   +--centerPages       plugins that are "standalone" center pages
   +--statusInfo        plugins the show status info of linuxCNC backend
```
**FalconView** supports plugins having their own translations and their own resources. All plugins implement ```ViewPluginInterface``` or subclass ```AbstractCenterWidget``` to use basic implementation of grunt stuff.

**The actual distinction of the plugin types depends on the name:**
- libnb* becomes a notebook-page to extend application setup process
- libpp* becomes "standalone" center page, that interacts with the user. It can provide a ```DynaAction```, which is a *QAction*-extension, which can be setup to react on backend state changes.
- libsi* becomes a floating subwindow, that mostly needs no user interaction.

### Prepare

To start with your own plugin you need to choose the kind of your plugin. Let's assume, that you'd like to create a centerpage plugin.

Go to directory 'src/centerPages' and create a directory of your choice. Let's give it a clever name like *'example'*.
Next edit *CMakeLists.txt* from 'src/centerPages' and add your plugin by adding this line:
```
add_subdirectory(example)
```

### CMake
Create a new file in your plugin directory called *CMakeLists.txt* - the recipe for cmake to create a makefile for your plugin.
Start with these lines:

```
cmake_minimum_required(VERSION 3.16)
#------------------------   PLUGIN   -----------------------------------------
project(Example LANGUAGES CXX)
#-----------------------------------------------------------------------------
include(FalconView)
```
cmake version 3.16 brings all the features needed for project **FalconView**.
So force that version too.

Next name your project. As stated earlier we used a clever name *'Example'*. This name is information only. It does not influence the type of your plugin.

Then include the common instructions, that are used by every cmake directory. The file is provided in the sample directory (see [README](README.md)).

Now the **important** part:

```
add_library(ppExample MODULE
    example.cpp
    )
```

Here you confirm that you create a centerpage plugin (the **pp** prefix of Example). *'example.cpp'* contains the sources of your plugin. If your plugin consists of several source-files, add them all to this statement.
Don't care for header files. cmake handles them for you.

On linux systems the name of your library will be enriched by 'lib'-prefix and '.so'-extension. So the binary of your plugin will be called ```libppExample.so```.

You probabely want to use existing application code, so you need to extend your project with some declarations for usage of existing parts. That consists of two statements.

First the project internal libraries:
```
target_link_libraries(ppExample
                      PRIVATE FVBaseLib
                      PRIVATE FVguiLib
                      )
```
Here you tell, that you wonna use baselib and guiLib. But you use them internally and don't want to export their symbols. Keep in mind, that *FVBaseLib* is the name used at ```add_library```-statement of baselib. Not the directory name nor its project name.

Then you might want to use *Qt* and/or *OpenCascade* ...
I already created project definitions for *Qt* and *OpenCascade* so you don't need to recall all the possible names, libraries, include directories ...

Just tell, that you use that foreign project:
```
use_interface_libraries(ppExample
                        IFQt
                        IFOpenCASCADE
                        IFStandard
                        )
```
First (as before) you need to use your library name. Then you use the name of  the project definition.
**FalconView** provides project definitions for:
- Qt    (*IFQt*)
- OpenCascade   (*IFOpenCASCADE*)
- Standard      (*IFStandard*)
- linuxCNC      (*IFlinuxCNC*)
Take care for the exact spelling of the names. Names at linux are case sensitive. This is true for filenames, directory names and of cause cmake names.

### Translation
If you provide localized texts (you should :) ) enrich your *CMakeLists.txt* with these statements (change the language to the one you'd like to provide):
```    
set(TS_FILES
    example_de_DE.ts
    )

if(COMMAND qt_create_translation)
   qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
   qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()    
```

### Source-Code
First the class declaration - the very minimum:
```c++
class Example : public AbstractCenterWidget
{
  Q_OBJECT
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "ViewPluginInterface_iid" FILE "example.json")
#endif
public:
  explicit Example(QWidget* parent = nullptr);
  virtual ~Example() = default;

protected:
  virtual void     connectSignals() override;
  virtual void     updateStyles() override;
  };
```

**NOTE: the very important part:** You have to declare, which interface is implemented by your plugin. Without that, your plugin could not be loaded.
```c++
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "ViewPluginInterface_iid" FILE "example.json")
#endif
```
That *json*-file may be empty, which means it must at least contain:
```c++
{}
```
### Hints
default plugin handling means that page content can be dynamically loaded from a ui-file (QTCreator form definition). If you like to use that feature, use this variant of **constructor**:

```c++
Example::Example(QWidget* parent)
 : AbstractCenterWidget(":Example.ui", parent) {
  setObjectName("Example");
  setWindowTitle(tr("Example"));
  }
```
If you extend ```AbstractCenterWidget``` you get three pointers to access core functionality of **FalconView**. ```AbstractCenterWidget``` cares about the problems created by code duplication sourced by usage of static libraries. So you don't have to worry about thus problems. They already solved.
These are the pointer to access core functionality:
- core - provides most application functionality
- cfg - access configuration (read/write)
- vm - access global variables (incl. linuxCNC backend status)

### Plugin blueprint
- centerPages/MDIEditor - uses dynamic loading of UI-Forms
- centerPages/JogView - uses UI-Form as member variable
- nbPages/LCToolTable - implements editor for linuxCNC tooltable
- nbPages/ToolManager - implements master/detail-view with database backend
- statusInfo/SpeedInfo - implements orientation dependant UI-Form usage
