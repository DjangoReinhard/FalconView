#ifndef CORE_H
#define CORE_H
#include <QString>
class Kernel;
class OcctQtViewer;
class ToolTable;
class LcProperties;
class MainView;
class QWidget;
class AxisMask;


class Core
{
public:
  Core(const QString& iniFileName, const QString& appName, const QString& group = "SRD");
  Core() {}

  void            parseGCFile(const QString& fileName);
  void            activatePage(const QString& pageName);
  QWidget*        stackedPage(const QString& pageName);
  const AxisMask& axisMask() const;

  void          setViewStack(MainView* v);
  OcctQtViewer* view3D();
  ToolTable&    toolTable();
  LcProperties& lcProperties();


private:
  friend class Config;
  Kernel*       core();
  const Kernel* core() const;

  static Kernel* kernel;
  };
#endif
