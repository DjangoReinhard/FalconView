#include <testEdit.h>
#include <valuemanager.h>
#include <configacc.h>
#include <guicore.h>
#include <gcodeeditor.h>
#include <gcodehighlighter.h>
#include <centerpage.h>
#include <filemanager.h>
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


TestEdit::TestEdit(QWidget* parent)
 : AbstractCenterWidget(parent)
 , fn(nullptr) {
  setObjectName("TestEdit");
  setWindowTitle(tr("TestEdit"));
  }


QWidget* TestEdit::createContent() {
  QWidget* rv = AbstractCenterWidget::createContent();

  fn     = findChild<QLineEdit*>("fileName");
  pbOpen = findChild<QPushButton*>("pbOpen");
  pbSave = findChild<QPushButton*>("pbSave");
  QGridLayout* gl = findChild<QGridLayout*>("gridLayout");
  QWidget* placeHolder = findChild<QWidget*>("widget");

  ed = new GCodeEditor(this);
  gh = new GCodeHighlighter(ed->document());
  gl->replaceWidget(placeHolder, ed);
  pbSave->setEnabled(ed->document()->isModified());
  ed->installEventFilter(this);

  return rv;
  }


void TestEdit::connectSignals() {
    connect(pbOpen, &QPushButton::clicked, this, &TestEdit::openFile);
    connect(ed->document(), &QTextDocument::modificationChanged, this, &TestEdit::dirtyChanged);
    connect(pbSave, &QPushButton::clicked, this, &TestEdit::saveFile);
    connect(vm->getModel(QString("cfgBg" + cfg->nameOf(Config::GuiElem::Filename)), QColor(Qt::white))
          , &ValueModel::valueChanged
          , fn
          , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                        .arg(vm->getValue("cfgFg" + cfg->nameOf(Config::GuiElem::Filename)).value<QColor>().rgb(), 0, 16)
                                        .arg(vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::Filename)).value<QColor>().rgba(), 0, 16);
                   fn->setStyleSheet(arg);
                   });
    connect(vm->getModel(QString("cfgFg" + cfg->nameOf(Config::GuiElem::Filename)), QColor(Qt::black))
          , &ValueModel::valueChanged
          , fn
          , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                        .arg(vm->getValue("cfgFg" + cfg->nameOf(Config::GuiElem::Filename)).value<QColor>().rgb(), 0, 16)
                                        .arg(vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::Filename)).value<QColor>().rgba(), 0, 16);
                   fn->setStyleSheet(arg);
                   });
    connect(vm->getModel(QString("cfgF" + cfg->nameOf(Config::GuiElem::Filename)), fn->font())
          , &ValueModel::valueChanged
          , fn
          , [=](){ fn->setFont(vm->getValue("cfgF" + cfg->nameOf(Config::GuiElem::Filename)).value<QFont>());
                   });

    connect(vm->getModel(QString("cfgBg" + cfg->nameOf(Config::GuiElem::GCode)), QColor(Qt::white))
          , &ValueModel::valueChanged
          , ed
          , [=](){ QString arg = QString("background: #%2;")
                                        .arg(vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::GCode)).value<QColor>().rgba(), 0, 16);
                   ed->setStyleSheet(arg);
                   });
    connect(vm->getModel(QString("cfgF" + cfg->nameOf(Config::GuiElem::GCode)), ed->font())
          , &ValueModel::valueChanged
          , ed
          , [=](){ ed->setFont(vm->getValue("cfgF" + cfg->nameOf(Config::GuiElem::GCode)).value<QFont>());
                   });
  }


// opens fileManager
void TestEdit::openFile() {    
  QWidget*     w   = core->stackedPage(FileManager::className);
  CenterPage*  chk = reinterpret_cast<CenterPage*>(w);
  FileManager* fm  = reinterpret_cast<FileManager*>(chk->centerWidget());

  if (fm) {
     fm->setClient(this);
     core->setAppMode(ApplicationMode::SelectFile);
//     core->activatePage(FileManager::className);
     }
  }


void TestEdit::showEvent(QShowEvent* e) {
  qDebug() << "TestEdit::showEvent ..."   ;
  AbstractCenterWidget::showEvent(e);
  if (e->type() == QEvent::Show) {
     if (ed->numLines() > 1) ed->setFocus();
     else                    pbOpen->setFocus();
     }
  }


void TestEdit::closeEvent(QCloseEvent*) {
  qDebug() << "TestEdit[" << objectName() << "] - " << fn->text();
  cfg->beginGroup(objectName());
  cfg->setValue("fileName", fn->text());
  cfg->endGroup();
  }


QString TestEdit::pageName() {
  return objectName();
  }


void TestEdit::dirtyChanged(bool dirty) {
  pbSave->setEnabled(dirty);
  if (dirty) fn->setText(this->fileName + " [*]");
  else       fn->setText(this->fileName);
  }


// callback for fileManager
void TestEdit::fileSelected(const QString& filePath) {
  qDebug() << "TestEdit::fileSelected(" << filePath << ")";  
  loadFile(filePath);
  }


void TestEdit::loadFile(const QVariant& fileName) {
  qDebug() << "TestEdit::loadFile" << fileName;

  if (fileName.toString().isEmpty()) return;
  QString   activeFile = vm->getValue("fileName").toString();
  QFileInfo fi(fileName.toString());

  if (objectName() == "TestEdit" && activeFile == fileName.toString()) {
     core->riseError(tr("selected file is already loaded as active gcode file."
                         "Please use active editor - can't load a file in both editors."));
     core->setAppMode(ApplicationMode::XEdit);
     return;
     }
  if (!fi.exists() || fi.size() < 1) {
     core->riseError(tr("TestEdit::loadFile: %1 is invalid").arg(fileName.toString()));
     return;
     }
  if (ed->loadFile(fi.absoluteFilePath())) {
     this->fileName = fi.absoluteFilePath();
     fn->setText(this->fileName);
     }
  // show editor again
  qDebug() << "TestEdit[" << objectName() << "] - set appmode to XEdit(6)";
  if (objectName() == "TestEdit")      core->setAppMode(ApplicationMode::XEdit);
  else if (objectName() == "PathEdit") core->setAppMode(ApplicationMode::Edit);
  else                                 core->setAppMode(ApplicationMode::Auto);
  }


void TestEdit::saveFile() {
  if (core->move2Backup(fileName)) {
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
     else core->riseError(tr("Failed to write file %1").arg(fileName));
     }
  else core->riseError(tr("Failed to create backup of file %1").arg(fileName));
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
  fn->setStyleSheet(QString("color: #%1; background: #%2;")
                           .arg(vm->getValue("cfgFg" + cfg->nameOf(Config::GuiElem::Filename)).value<QColor>().rgb(), 0, 16)
                           .arg(vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::Filename)).value<QColor>().rgba(), 0, 16));
  fn->setFont(vm->getValue("cfgF"  + cfg->nameOf(Config::GuiElem::Filename)).value<QFont>());
  ed->setStyleSheet(QString("background: #%2;")
                           .arg(vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::GCode)).value<QColor>().rgba(), 0, 16));
  ed->setFont(vm->getValue("cfgF"  + cfg->nameOf(Config::GuiElem::GCode)).value<QFont>());
  }


void TestEdit::restoreState() {
  qDebug() << "TE::restoreState() - I am" << objectName() << "- wt" << windowTitle();
  cfg->beginGroup(objectName());
  QString lastFile = cfg->value("fileName").toString();
  cfg->endGroup();
  QFile ncFile(lastFile);

  if (ncFile.exists()) loadFile(ncFile.fileName());
  else                 qDebug() << "what a mess - no file to restore!";
  }


void TestEdit::fileUpdated(const QString&)  {}
