#include <editordockable.h>
#include <gcodeeditor.h>
#include <QFile>
#include <QDir>
#include <QUiLoader>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QFileDialog>
#include <portable-file-dialogs.h>
#include <gcodehighlighter.h>


EditorDockable::EditorDockable(QFile& uiDesc, QWidget* parent)
 : QDockWidget(tr("Editor"), parent) {
  initializeWidget(uiDesc);
  }


EditorDockable::~EditorDockable() {
  delete gh;
  }


void EditorDockable::initializeWidget(QFile &uiDesc) {
  QUiLoader loader;
  QWidget*  w = loader.load(&uiDesc, this);

  uiDesc.close();
  setWidget(w);
  QPushButton* pbOpen = w->findChild<QPushButton*>("pbOpen");

  connect(pbOpen, &QPushButton::clicked, this, &EditorDockable::loadFile);
  QGridLayout* layout = w->findChild<QGridLayout*>("gridLayout");
  QWidget*     placeHolder = w->findChild<QWidget*>("widget");
  QFont        font;

  font.setFamily("Courier10 BT");   // this font works with bold and QPlainTextEdit
  font.setPointSize(11);
  editor = new GCodeEditor(this);
  editor->setFont(font);
  layout->addWidget(editor, 1, 0, 1, 2);
  placeHolder->hide();
  fileName = w->findChild<QLineEdit*>("fileName");
  gh = new GCodeHighlighter(editor->document());
  }


/*
 * this file dialog blocks the timer for the time of dialog creation only.
 * Then timer keeps running without issue
 */
void EditorDockable::loadFileAlt() {
  QDir dirStart(QDir::homePath() + "/linuxcnc/nc_files");
  QString name = QFileDialog::getOpenFileName(this
                                            , tr("open GCode file")
                                            , dirStart.absolutePath()
                                            , tr("GCode Files (*.ngc *.nc)"));
  if (name.size()) {
     QFile file(name);

     if (file.open(QFile::ReadOnly | QFile::Text)) {
        editor->setPlainText(file.readAll());
        fileName->setText(file.fileName());
        }
     }
  }


/*
 * this file dialog blocks the timer as long as the dialog is open
 */
void EditorDockable::loadFile() {    
  if (!pfd::settings::available()){
     std::cerr << "Portable File Dialogs are not available on this platform. \n"
                  "On linux install zenity, $ sudo apt-get install zenity\n" << std::endl;
     }
  QDir dirStart(QDir::homePath() + "/linuxcnc/nc_files");
  auto f = pfd::open_file(tr("Choose file to open").toStdString()
                        , dirStart.path().toStdString()
                        , { "GCode Files (.ngc)", "*.ngc",
                            "All Files", "*" }
                        , pfd::opt::none);
  if (f.result().size() > 0) {
     QFile file(f.result().at(0).c_str());

     if (file.open(QFile::ReadOnly | QFile::Text)) {
        editor->setPlainText(file.readAll());
        fileName->setText(file.fileName());
        }
     }
  }
