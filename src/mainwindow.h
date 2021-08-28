#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "valuemodel.h"
#include "labeladapter.h"
#include "positionmodel.h"
#include "gcodehighlighter.h"


class PositionDockable;
class ToolInfoDockable;
class SpeedInfoDockable;
class EditorDockable;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
 ~MainWindow();

public slots:
  void count();

protected:
  void createDockings();

private:
  Ui::MainWindow*     ui;
  PositionDockable*   pos;
  ToolInfoDockable*   ti;
  SpeedInfoDockable*  si;
  EditorDockable*     ed;
  ValueModel          counter;
  PositionModel       pm;
  GCodeHighlighter*   gh;
  };
#endif // MAINWINDOW_H
