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
 : DynWidget(parent)
 , fn(nullptr) {
  setObjectName("TestEdit");
  this->setStyleSheet("background: 0xFF0000;");
  setLayout(new QHBoxLayout);
  QWidget* w = loadFromUI(fileName);

  qDebug() << "object name of top-widget from UI-file:" << w->objectName();

  layout()->addWidget(w);
  layout()->setContentsMargins(0, 0, 0, 0);
  fn     = w->findChild<QLineEdit*>("fileName");
  pbOpen = w->findChild<QPushButton*>("pbOpen");
  pbSave = w->findChild<QPushButton*>("pbSave");
  QGridLayout* gl = w->findChild<QGridLayout*>("gridLayout");
  QWidget* placeHolder = w->findChild<QWidget*>("widget");

  ed     = new GCodeEditor(this);
  gh     = new GCodeHighlighter(ed->document());
  ed->setFocusPolicy(Qt::NoFocus);
  gl->addWidget(ed, 1, 0, 1, 3);
  placeHolder->hide();
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


void TestEdit::openFile() {    
  QWidget*     w = Core().stackedPage("FileManager");
  FileManager* fm = qobject_cast<FileManager*>(w);

  if (fm) {
     fm->setClient(this);
     Core().activatePage("FileManager");
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


void TestEdit::fileSelected(const QString &filePath) {
  loadFile(filePath);
  }


void TestEdit::loadFile(const QVariant& fileName) {
  qDebug() << "TestEdit::loadFile" << fileName;
  ed->loadFile(fileName);
  fn->setText(fileName.toString());
  Core().activatePage(objectName());
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
