#include <patheditor.h>
#include <pweditor.h>
#include <valuemanager.h>
#include <centerview.h>
#include <core.h>
#include <configacc.h>
#include <gcodeeditor.h>
#include <gcodehighlighter.h>
#include <occtviewer.h>
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


PathEditor::PathEditor(const QString& fileName, QWidget* parent)
 : TestEdit(fileName, parent) {
  setObjectName(PathEditor::className);
  setWindowTitle(tr("PathEditor"));  
  }


void PathEditor::connectSignals() {
  connect(ValueManager().getModel("fileName", " "), &ValueModel::valueChanged, this, &PathEditor::reallyLoadFile);
  TestEdit::connectSignals();
  connect(ed, &GCodeEditor::cursorPositionChanged, this, [=](){ ValueManager().setValue("edLine", ed->textCursor().block().blockNumber()); });
  }


// called from TestEdit::fileSelected
void PathEditor::loadFile(const QVariant& fileName) {
  if (Core().checkBE()) {
     qDebug() << "PathEditor::loadFile (backend active)" << fileName;
     Core().beLoadTaskPlan(fileName.toString());
     }
  else ValueManager().setValue("fileName", fileName);
  }


void PathEditor::reallyLoadFile(const QVariant& fileName) {
  TestEdit::loadFile(fileName);
  Core().setAppMode(ApplicationMode::Edit);
  }


void PathEditor::fileUpdated(const QString& fileName) {
  //TODO: ask backend to reload file
  }

const QString PathEditor::className = "PathEditor";
