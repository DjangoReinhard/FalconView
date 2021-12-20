#include <testEdit.h>
#include <valuemanager.h>
#include <configacc.h>
#include <gcodeeditor.h>
#include <gcodehighlighter.h>
#include <occtviewer.h>
#include <centerview.h>
#include <dynframe.h>
#include <filemanager.h>
#include <core.h>
#include <QInputDialog>
#include <QSplitter>
#include <QMessageBox>
#include <QFileDialog>
#include <QKeyEvent>
#include <QAction>
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
  setObjectName(TestEdit::className);
  setWindowTitle(tr("TestEdit"));
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
//  ed->setFocusPolicy(Qt::NoFocus);
  gl->replaceWidget(placeHolder, ed);
  pbSave->setEnabled(ed->document()->isModified());
  ed->installEventFilter(this);

  return rv;
  }


void TestEdit::connectSignals() {
    ValueManager vm;
    Config       cfg;

    connect(pbOpen, &QPushButton::clicked, this, &TestEdit::openFile);
    connect(ed->document(), &QTextDocument::modificationChanged, pbSave, &QPushButton::setEnabled);
//    connect(ed, &QPlainTextEdit::textChanged, this, &TestEdit::textChanged);
    connect(pbSave, &QPushButton::clicked, this, &TestEdit::saveFile);
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
  QWidget*     w  = Core().stackedPage(FileManager::className);
  DynFrame*    df = qobject_cast<DynFrame*>(w);
  FileManager* fm = qobject_cast<FileManager*>(df->centerWidget());

  if (fm) {
     fm->setClient(this);
     Core().activatePage(FileManager::className);
     }
  }


void TestEdit::showEvent(QShowEvent* e) {
  qDebug() << "TestEdit::showEvent ..."   ;
  DynCenterWidget::showEvent(e);
  if (e->type() == QEvent::Show) {
     if (ed->numLines() > 1) ed->setFocus();
     else                    pbOpen->setFocus();
     }
  }


void TestEdit::closeEvent(QCloseEvent*) {
  qDebug() << "TestEdit[" << objectName() << "] - " << fn->text();
  Config cfg;

  cfg.beginGroup(objectName());
  cfg.setValue("fileName", fn->text());
  cfg.endGroup();
  }


QString TestEdit::pageName() {
  return objectName();
  }


// callback for fileManager
void TestEdit::fileSelected(const QString& filePath) {
  qDebug() << "TestEdit::fileSelected(" << filePath << ")";
  loadFile(filePath);
  }


void TestEdit::loadFile(const QVariant& fileName) {
  qDebug() << "TestEdit::loadFile" << fileName;
  QFileInfo fi(fileName.toString());

  if (!fi.exists() || fi.size() < 1) {
     Core().riseError(tr("TestEdit::loadFile: %1 is invalid").arg(fileName.toString()));
     return;
     }
  ed->loadFile(fi.absoluteFilePath());
  fn->setText(fi.absoluteFilePath());

  // show editor again
  qDebug() << "TestEdit[" << objectName() << "] - set appmode to XEdit(6)";
  if (objectName() == "TestEdit")      Core().setAppMode(ApplicationMode::XEdit);
  else if (objectName() == "PathEdit") Core().setAppMode(ApplicationMode::Edit);
  else                                 Core().setAppMode(ApplicationMode::Auto);
  }


void TestEdit::saveFile() {
  QString fileName = fn->text();

  if (Core().move2Backup(fileName)) {
     QString content = ed->document()->toPlainText();
     QFile   of(fileName);

     if (of.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&of);

        content.replace(',', '.');
        out << content;
        of.flush();
        of.close();
        QTextBlock  b = ed->textCursor().block();

        ed->setPlainText(content);
        ed->setTextCursor(QTextCursor(b));
        fileUpdated(fileName);
        }
     else Core().riseError(tr("Failed to write file %1").arg(fileName));
     }
  else Core().riseError(tr("Failed to create backup of file %1").arg(fileName));
  }


bool TestEdit::eventFilter(QObject*, QEvent* event) {
  if (event->type() == QEvent::KeyPress) {
     QKeyEvent* e = static_cast<QKeyEvent*>(event);

     switch (e->key()) {
       case Qt::Key_S:
            if (e->modifiers() == Qt::CTRL) {
               if (pbSave->isEnabled()) {
                  pbSave->click();
                  return true;
                  }
               } break;
       case Qt::Key_F:
            if (e->modifiers() == Qt::CTRL) {
               bool    ok;
               QString text = QInputDialog::getText(this
                                                  , tr("QInputDialog::getText()")
                                                  , tr("Search text:")
                                                  , QLineEdit::Normal
                                                  , "G0"
                                                  , &ok);
               if (ok && !text.isEmpty()) {
                  QTextCursor tc = ed->document()->find(text, ed->textCursor().anchor());

                  if (tc.isNull()) tc = ed->document()->find(text);
                  ed->setTextCursor(tc);
                  }
               } break;
       }
     }
  return false;
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

  cfg.beginGroup(objectName());
  QString lastFile = cfg.value("fileName").toString();
  cfg.endGroup();
  QFile ncFile(lastFile);

  if (ncFile.exists()) loadFile(ncFile.fileName());
  }


void TestEdit::fileUpdated(const QString&)  {}

const QString& TestEdit::className = "TestEdit";
