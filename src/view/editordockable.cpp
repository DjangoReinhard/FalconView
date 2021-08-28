#include <editordockable.h>
#include <QFile>
#include <QDir>
#include <QUiLoader>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
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
  QFont font;

  font.setFamily("Hack");
  font.setFixedPitch(true);
  font.setPointSize(10);

  editor   = w->findChild<QTextEdit*>("editor");
  fileName = w->findChild<QLineEdit*>("fileName");
  editor->setFont(font);
  gh = new GCodeHighlighter(editor->document());
  }


void EditorDockable::loadFile() {
  if (!pfd::settings::available()){
     std::cerr << "Portable File Dialogs are not available on this platform. \n"
                  "On linux install zenity, $ sudo apt-get install zenity\n" << std::endl;
     }
  QDir dirStart("~/linuxcnc/nc_files");
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
