#include <pweditor.h>
#include <valuemanager.h>
#include <configmgr.h>
#include <gcodeeditor.h>
#include <gcodehighlighter.h>
#include <occtviewer.h>
#include <QSplitter>
#include <QFileDialog>
#include <QLabel>
#include <QDir>
#include <QVariant>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QPushButton>


PreViewEditor::PreViewEditor(const QString& fileName, OcctQtViewer* view, QWidget* parent)
 : DynWidget(parent)
 , view(view) {
  setObjectName("PreViewEditor");
  this->setStyleSheet("background: 0xFF0000;");
  setLayout(new QHBoxLayout);
  spV = new QSplitter(Qt::Vertical);
  QWidget* w = loadFromUI(fileName);

  view->setMinimumSize(400, 400);
  view->setParent(this);
  spV->addWidget(view);
  spV->addWidget(w);
  fn     = w->findChild<QLineEdit*>("fileName");
  pbOpen = w->findChild<QPushButton*>("pbOpen");
  pbSave = w->findChild<QPushButton*>("pbSave");
  QGridLayout* gl = w->findChild<QGridLayout*>("gridLayout");
  QWidget* placeHolder = w->findChild<QWidget*>("widget");

  ed     = new GCodeEditor(this);
  gh     = new GCodeHighlighter(ed->document());
  ed->setReadOnly(true);
  ed->setFocusPolicy(Qt::NoFocus);
  gl->addWidget(ed, 1, 0, 1, 3);
  placeHolder->hide();
  layout()->addWidget(spV);
  pbOpen->hide();
  pbSave->hide();
  connectSignals();
  updateStyles();
  }


void PreViewEditor::connectSignals() {
    ValueManager vm;
    Config       cfg;

    connect(vm.getModel("fileName", " "), &ValueModel::valueChanged, this, &PreViewEditor::loadFile);
    connect(vm.getModel(QString("cfgBg" + cfg.guiSettings[6]), QColor(Qt::white))
          , &ValueModel::valueChanged
          , fn
          , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                        .arg(ValueManager().getValue("cfgFg" + cfg.guiSettings[6]).value<QColor>().rgb(), 0, 16)
                                        .arg(ValueManager().getValue("cfgBg" + cfg.guiSettings[6]).value<QColor>().rgba(), 0, 16);
                   fn->setStyleSheet(arg);
                   });
    connect(vm.getModel(QString("cfgFg" + cfg.guiSettings[6]), QColor(Qt::black))
          , &ValueModel::valueChanged
          , fn
          , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                        .arg(ValueManager().getValue("cfgFg" + cfg.guiSettings[6]).value<QColor>().rgb(), 0, 16)
                                        .arg(ValueManager().getValue("cfgBg" + cfg.guiSettings[6]).value<QColor>().rgba(), 0, 16);
                   fn->setStyleSheet(arg);
                   });
    connect(vm.getModel(QString("cfgF" + cfg.guiSettings[6]), fn->font())
          , &ValueModel::valueChanged
          , fn
          , [=](){ fn->setFont(ValueManager().getValue("cfgF" + cfg.guiSettings[6]).value<QFont>());
                   });

    connect(vm.getModel(QString("cfgBg" + cfg.guiSettings[7]), QColor(Qt::white))
          , &ValueModel::valueChanged
          , ed
          , [=](){ QString arg = QString("background: #%2;")
                                        .arg(ValueManager().getValue("cfgBg" + cfg.guiSettings[7]).value<QColor>().rgba(), 0, 16);
                   ed->setStyleSheet(arg);
                   });
    connect(vm.getModel(QString("cfgF" + cfg.guiSettings[7]), ed->font())
          , &ValueModel::valueChanged
          , ed
          , [=](){ ed->setFont(ValueManager().getValue("cfgF" + cfg.guiSettings[7]).value<QFont>());
                   });
  }


void PreViewEditor::openFile() {
  QDir dirStart(QDir::homePath() + "/linuxcnc/nc_files");
  QString name = QFileDialog::getOpenFileName(this
                                            , tr("open GCode file")
                                            , dirStart.absolutePath()
                                            , tr("GCode Files (*.ngc *.nc)"));
  if (name.size()) loadFile(QVariant(name));
  }


void PreViewEditor::loadFile(const QVariant& fileName) {
  ed->loadFile(fileName);
  fn->setText(fileName.toString());
  }


void PreViewEditor::updateStyles() {
    ValueManager vm;
    Config       cfg;

    fn->setStyleSheet(QString("color: #%1; background: #%2;")
                                   .arg(ValueManager().getValue("cfgFg" + cfg.guiSettings[6]).value<QColor>().rgb(), 0, 16)
                                   .arg(ValueManager().getValue("cfgBg" + cfg.guiSettings[6]).value<QColor>().rgba(), 0, 16));
    fn->setFont(vm.getValue("cfgF"  + cfg.guiSettings[6]).value<QFont>());
    ed->setStyleSheet(QString("background: #%2;")
                                 .arg(ValueManager().getValue("cfgBg" + cfg.guiSettings[7]).value<QColor>().rgba(), 0, 16));
    ed->setFont(vm.getValue("cfgF"  + cfg.guiSettings[7]).value<QFont>());
  }
