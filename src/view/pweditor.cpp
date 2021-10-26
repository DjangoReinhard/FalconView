#include <pweditor.h>
#include <valuemanager.h>
#include <configacc.h>
#include <core.h>
#include <gcodeeditor.h>
#include <gcodehighlighter.h>
#include <occtviewer.h>
#include <AIS_ViewCube.hxx>
#include <AIS_InteractiveContext.hxx>
#include <QSplitter>
#include <QFileDialog>
#include <QLabel>
#include <QDir>
#include <QTime>
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
  Core().parseGCFile(fileName.toString());
  }


void PreViewEditor::genPreview(const QString &fileName) {
  QFile        gcFile(fileName);

//  if (gcFile.exists()) {
//     LcProperties lcProps(getenv("INI_FILE_NAME"));
//     ToolTable    tt(lcProps.toolTableFileName());
//     CanonIF      ci(lcProps, tt);
//     LCInterface  lcIF(lcProps, tt);

//     ci.setTraverseColor(QColor(Qt::cyan));
//     ci.setFeedColor(QColor(Qt::white));
//     ci.setLimitsColor(QColor(150, 255, 150));
//     lcIF.setupToolTable();

//     qDebug() << "gonna parse gcode-file: " << gcFile.fileName();
//     QTime       start = QTime::currentTime();

//     lcIF.parseInline(gcFile.fileName());
//     QTime end  = QTime::currentTime();
//     long delta = end.msecsSinceStartOfDay() - start.msecsSinceStartOfDay();

//     qDebug() << "parsing of " << gcFile.fileName() << " took: " << delta << "ms";

//     view->Context()->RemoveAll(false);
//     for (auto shape : CanonIF().toolPath()) {
//         view->Context()->Display(shape, AIS_WireFrame, 0, false);
//         }
//     view->Context()->Display(view->Cube(), 0, 0, false);
//     view->View()->FitAll(0.01, false);
//     }
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
