#include <testEdit.h>
#include <valuemanager.h>
#include <configacc.h>
#include <gcodeeditor.h>
#include <gcodehighlighter.h>
#include <occtviewer.h>
#include <mainview.h>
#include <filemanager.h>
#include <core.h>
#include <QSplitter>
#include <QFileDialog>
#include <QLabel>
#include <QDir>
#include <QDebug>
#include <QVariant>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QPushButton>


TestEdit::TestEdit(const QString& fileName, QWidget* parent)
 : DynCenterWidget(fileName, TestEdit::className, false, parent)
 , fn(nullptr) {
  this->setStyleSheet("background: 0xFF0000;");
  }

QWidget* TestEdit::createContent() {
  QWidget* rv = DynCenterWidget::createContent();

  fn     = findChild<QLineEdit*>("fileName");
  pbOpen = findChild<QPushButton*>("pbOpen");
  pbSave = findChild<QPushButton*>("pbSave");
  QGridLayout* gl = findChild<QGridLayout*>("gridLayout");
  QWidget* placeHolder = findChild<QWidget*>("widget");

  ed = new GCodeEditor(this);
  gh = new GCodeHighlighter(ed->document());
  ed->setFocusPolicy(Qt::NoFocus);
//  gl->addWidget(ed, 1, 0, 1, 3);
//  placeHolder->hide();
  gl->replaceWidget(placeHolder, ed);

  return rv;
  }


void TestEdit::connectSignals() {
    ValueManager vm;
    Config       cfg;

    connect(pbOpen, &QPushButton::clicked, this, &TestEdit::openFile);
    connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::Filename)), QColor(Qt::white))
          , &ValueModel::valueChanged
          , fn
          , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                        .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::Filename)).value<QColor>().rgb(), 0, 16)
                                        .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::Filename)).value<QColor>().rgba(), 0, 16);
                   fn->setStyleSheet(arg);
                   });
    connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::Filename)), QColor(Qt::black))
          , &ValueModel::valueChanged
          , fn
          , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                        .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::Filename)).value<QColor>().rgb(), 0, 16)
                                        .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::Filename)).value<QColor>().rgba(), 0, 16);
                   fn->setStyleSheet(arg);
                   });
    connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::Filename)), fn->font())
          , &ValueModel::valueChanged
          , fn
          , [=](){ fn->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::Filename)).value<QFont>());
                   });

    connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::GCode)), QColor(Qt::white))
          , &ValueModel::valueChanged
          , ed
          , [=](){ QString arg = QString("background: #%2;")
                                        .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::GCode)).value<QColor>().rgba(), 0, 16);
                   ed->setStyleSheet(arg);
                   });
    connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::GCode)), ed->font())
          , &ValueModel::valueChanged
          , ed
          , [=](){ ed->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::GCode)).value<QFont>());
                   });
  }


// opens fileManager
void TestEdit::openFile() {    
  QWidget*     w = Core().stackedPage(FileManager::className);
  FileManager* fm = qobject_cast<FileManager*>(w);

  if (fm) {
     fm->setClient(this);
     Core().activatePage(FileManager::className);
     }
  }


void TestEdit::showEvent(QShowEvent* e) {
  if (e->type() == QEvent::Show) {
     if (ed->numLines() > 1) ed->setFocus();
     else                    pbOpen->setFocus();
     }
  }


QString TestEdit::pageName() {
  return objectName();
  }


// callback for fileManager
void TestEdit::fileSelected(const QString& filePath) {
  loadFile(filePath);
  }


void TestEdit::loadFile(const QVariant& fileName) {
  qDebug() << "TestEdit::loadFile" << fileName;
  QFileInfo fi(fileName.toString());

  if (!fi.exists() || fi.size() < 1) {
     qDebug() << "TestEdit::loadFile: >" << fileName << "< is invalid";
     return;
     }
  ed->loadFile(fi.absoluteFilePath());
  fn->setText(fi.absoluteFilePath());
  // show editor again
  Core().setAppMode(ApplicationMode::XEdit);
  }


void TestEdit::updateStyles() {
  ValueManager vm;
  Config       cfg;

  fn->setStyleSheet(QString("color: #%1; background: #%2;")
                           .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::Filename)).value<QColor>().rgb(), 0, 16)
                           .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::Filename)).value<QColor>().rgba(), 0, 16));
  fn->setFont(vm.getValue("cfgF"  + cfg.nameOf(Config::GuiElem::Filename)).value<QFont>());
  ed->setStyleSheet(QString("background: #%2;")
                           .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::GCode)).value<QColor>().rgba(), 0, 16));
  ed->setFont(vm.getValue("cfgF"  + cfg.nameOf(Config::GuiElem::GCode)).value<QFont>());
  }


const QString TestEdit::className = "TestEdit";
