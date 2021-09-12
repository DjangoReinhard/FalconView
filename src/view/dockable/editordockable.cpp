#include <editordockable.h>
#include <gcodeeditor.h>
#include <gcodeviewer.h>
#include <valuemanager.h>
#include <config.h>
#include <QFile>
#include <QDir>
#include <QUiLoader>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QFileDialog>
#include <QScrollBar>
#include <gcodehighlighter.h>
#include <QDebug>


EditorDockable::EditorDockable(const QString& name, QWidget* parent)
 : Dockable(name, tr("Editor"), parent) {
  initializeWidget();
  }


EditorDockable::~EditorDockable() {
  //delete gh;
  }


void EditorDockable::initializeWidget() {
  QGridLayout* layout      = findChild<QGridLayout*>("gridLayout");
  QWidget*     placeHolder = findChild<QWidget*>("widget");

  editor = new GCodeEditor(this);
//  editor = new GCodeViewer(this);
  layout->addWidget(editor, 1, 0, 1, 2);
  placeHolder->hide();
  fileName = findChild<QLineEdit*>("fileName");
  pbOpen   = findChild<QPushButton*>("pbOpen");
  gh       = new GCodeHighlighter(editor->document());
//  pbOpen->hide();

  connectSignals();
  updateStyles();
  }


void EditorDockable::connectSignals() {
  ValueManager vm;
  Config       cfg;

  connect(vm.getModel("fileName", " "), &ValueModel::valueChanged, fileName, [=](QVariant name){ fileName->setText(name.toString()); });
  connect(vm.getModel(QString("cfgBg" + cfg.guiSettings[6]), QColor(Qt::white))
        , &ValueModel::valueChanged
        , fileName
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.guiSettings[6]).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.guiSettings[6]).value<QColor>().rgba(), 0, 16);
                 fileName->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.guiSettings[6]), QColor(Qt::black))
        , &ValueModel::valueChanged
        , fileName
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.guiSettings[6]).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.guiSettings[6]).value<QColor>().rgba(), 0, 16);
                 fileName->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.guiSettings[6]), fileName->font())
        , &ValueModel::valueChanged
        , fileName
        , [=](){ fileName->setFont(ValueManager().getValue("cfgF" + cfg.guiSettings[6]).value<QFont>());
                 });

  connect(vm.getModel(QString("cfgBg" + cfg.guiSettings[7]), QColor(Qt::white))
        , &ValueModel::valueChanged
        , editor
        , [=](){ QString arg = QString("background: #%2;")
                                      .arg(ValueManager().getValue("cfgBg" + cfg.guiSettings[7]).value<QColor>().rgba(), 0, 16);
                 editor->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.guiSettings[7]), fileName->font())
        , &ValueModel::valueChanged
        , editor
        , [=](){ editor->setFont(ValueManager().getValue("cfgF" + cfg.guiSettings[6]).value<QFont>());
                 });
  }


void EditorDockable::updateStyles() {
  ValueManager vm;
  Config       cfg;

  fileName->setStyleSheet(QString("color: #%1; background: #%2;")
                                 .arg(ValueManager().getValue("cfgFg" + cfg.guiSettings[6]).value<QColor>().rgb(), 0, 16)
                                 .arg(ValueManager().getValue("cfgBg" + cfg.guiSettings[6]).value<QColor>().rgba(), 0, 16));
  fileName->setFont(vm.getValue("cfgF"  + cfg.guiSettings[6]).value<QFont>());
  editor->setStyleSheet(QString("background: #%2;")
                               .arg(ValueManager().getValue("cfgBg" + cfg.guiSettings[7]).value<QColor>().rgba(), 0, 16));
  editor->setFont(vm.getValue("cfgF"  + cfg.guiSettings[7]).value<QFont>());

  }

/*
void EditorDockable::setLine(QVariant line) {
  qDebug() << "should set editor to line #" << line.toInt();
  editor->verticalScrollBar()->setValue(line.toInt());
  }
*/

/*
 * this file dialog blocks the timer for the time of dialog creation only.
 * Then timer keeps running without issue
 */
void EditorDockable::openFile() {
  QDir dirStart(QDir::homePath() + "/linuxcnc/nc_files");
  QString name = QFileDialog::getOpenFileName(this
                                            , tr("open GCode file")
                                            , dirStart.absolutePath()
                                            , tr("GCode Files (*.ngc *.nc)"));
  if (name.size()) editor->loadFile(QVariant(name));
  }
