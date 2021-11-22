#include <editordockable.h>
#include <gcodeeditor.h>
#include <gcodeviewer.h>
#include <valuemanager.h>
#include <configacc.h>
#include <QFile>
#include <QDir>
#include <QUiLoader>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QFileDialog>
#include <gcodehighlighter.h>
#include <QDebug>


EditorDockable::EditorDockable(const QString& name, QWidget* parent)
 : DynCenterWidget(name, tr("Editor"), false, parent) {
  }


EditorDockable::~EditorDockable() {
  }


QWidget* EditorDockable::createContent() {
  QWidget*     rv          = DynCenterWidget::createContent();
  QGridLayout* layout      = findChild<QGridLayout*>("gridLayout");
  QWidget*     placeHolder = findChild<QWidget*>("widget");

  editor = new GCodeEditor(this);
  layout->replaceWidget(placeHolder, editor);
  fileName = findChild<QLineEdit*>("fileName");
  pbOpen   = findChild<QPushButton*>("pbOpen");
  gh       = new GCodeHighlighter(editor->document());

  return rv;
  }


void EditorDockable::connectSignals() {
  ValueManager vm;
  Config       cfg;

  connect(vm.getModel("fileName", " "), &ValueModel::valueChanged, fileName, [=](QVariant name){ fileName->setText(name.toString()); });
  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::Filename)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , fileName
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::Filename)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::Filename)).value<QColor>().rgba(), 0, 16);
                 fileName->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::Filename)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , fileName
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::Filename)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::Filename)).value<QColor>().rgba(), 0, 16);
                 fileName->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::Filename)), fileName->font())
        , &ValueModel::valueChanged
        , fileName
        , [=](){ fileName->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::Filename)).value<QFont>());
                 });

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::GCode)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , editor
        , [=](){ QString arg = QString("background: #%2;")
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::GCode)).value<QColor>().rgba(), 0, 16);
                 editor->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::GCode)), fileName->font())
        , &ValueModel::valueChanged
        , editor
        , [=](){ editor->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::GCode)).value<QFont>());
                 });
  }


void EditorDockable::updateStyles() {
  ValueManager vm;
  Config       cfg;

  fileName->setStyleSheet(QString("color: #%1; background: #%2;")
                                 .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::Filename)).value<QColor>().rgb(), 0, 16)
                                 .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::Filename)).value<QColor>().rgba(), 0, 16));
  fileName->setFont(vm.getValue("cfgF"  + cfg.nameOf(Config::GuiElem::Filename)).value<QFont>());
  editor->setStyleSheet(QString("background: #%2;")
                               .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::GCode)).value<QColor>().rgba(), 0, 16));
  editor->setFont(vm.getValue("cfgF"  + cfg.nameOf(Config::GuiElem::GCode)).value<QFont>());
  }

/*
 * this file dialog blocks the timer for the time of dialog creation only.
 * Then timer keeps running without issue
 */
void EditorDockable::openFile() {
  QDir    dirStart(QDir::homePath() + "/linuxcnc/nc_files");
  QString name = QFileDialog::getOpenFileName(this
                                            , tr("open GCode file")
                                            , dirStart.absolutePath()
                                            , tr("GCode Files (*.ngc *.nc)"));
  if (name.size()) editor->loadFile(QVariant(name));
  }
