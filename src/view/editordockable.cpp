#include <editordockable.h>
#include <gcodeeditor.h>
#include <gcodeviewer.h>
#include <valuemanager.h>
#include <QFile>
#include <QDir>
#include <QUiLoader>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QFileDialog>
#include <QScrollBar>
#include <portable-file-dialogs.h>
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
  QPushButton* pbOpen = findChild<QPushButton*>("pbOpen");
  QGridLayout* layout = findChild<QGridLayout*>("gridLayout");
  QWidget*     placeHolder = findChild<QWidget*>("widget");
  QFont        font;

  font.setFamily("Courier10 BT");   // this font works with bold and QPlainTextEdit
  font.setPointSize(11);
//  editor = new GCodeEditor(this);
  editor = new GCodeViewer(this);
  editor->setFont(font);
  layout->addWidget(editor, 1, 0, 1, 2);
  placeHolder->hide();
  fileName = findChild<QLineEdit*>("fileName");
  gh = new GCodeHighlighter(editor->document());
  ValueManager vm;

//connect(pbOpen, &QPushButton::clicked, this, &EditorDockable::openFile);
  pbOpen->hide();
  connect(vm.getModel("fileName", " "), &ValueModel::valueChanged, fileName, [=](QVariant name){ fileName->setText(name.toString()); });
  }


void EditorDockable::setLine(QVariant line) {
  qDebug() << "should set editor to line #" << line.toInt();
  editor->verticalScrollBar()->setValue(line.toInt());
  }


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


/*
 * this file dialog blocks the timer as long as the dialog is open
 *
void EditorDockable::openFileAlt() {
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
*/
