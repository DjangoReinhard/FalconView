#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "valuemodel.h"
#include "labeladapter.h"
#include "positionmodel.h"
#include "gcodemodel.h"


class PositionWidget;
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
  void loadFile();

private:
  Ui::MainWindow *ui;
  PositionWidget* pos;
  ValueModel counter;
  PositionModel pm;
  GCodeHighlighter* gh;
  };
#endif // MAINWINDOW_H
