#ifndef CORE_H
#define CORE_H
#include <QString>
class Kernel;
class OcctQtViewer;
class ToolTable;
class LcProperties;
class MainView;


class Core
{
public:
  Core(const QString& iniFileName, const QString& appName, const QString& group = "SRD");
  Core() {}
  void          parseGCFile(const QString& fileName);
  void          setViewStack(MainView* v);
  OcctQtViewer* view3D();
  ToolTable&    toolTable();
  LcProperties& lcProperties();
  MainView*     viewStack();


private:
  friend class Config;
  Kernel*       core();

  static Kernel* kernel;
  };
#endif
