#include <patheditor.h>
#include <valuemanager.h>
#include <centerview.h>
#include <guicore.h>
#include <configacc.h>
#include <gcodeeditor.h>
#include <gcodehighlighter.h>
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


PathEditor::PathEditor(QWidget* parent)
 : TestEdit(parent) {
  setObjectName("PathEditor");
  setWindowTitle(tr("PathEditor"));
  }


void PathEditor::connectSignals() {
  connect(ValueManager().getModel("fileName", " "), &ValueModel::valueChanged, this, &PathEditor::reallyLoadFile);
  TestEdit::connectSignals();
  connect(ed, &GCodeEditor::cursorPositionChanged, this, [=](){ ValueManager().setValue("edLine", ed->textCursor().block().blockNumber()); });
  }


// called from TestEdit::fileSelected
void PathEditor::loadFile(const QVariant& fileName) {
  if (GuiCore().checkBE()) {
     qDebug() << "PathEditor::loadFile (backend active)" << fileName;
     GuiCore().beLoadTaskPlan(fileName.toString());
     }
  else ValueManager().setValue("fileName", fileName);
  }


void PathEditor::dirtyChanged(bool dirty) {
  ValueManager().setValue("gcodeDirty", dirty);
  TestEdit::dirtyChanged(dirty);
  }


void PathEditor::reallyLoadFile(const QVariant& fileName) {
  TestEdit::loadFile(fileName);
  Core().setAppMode(ApplicationMode::Edit);
  }


void PathEditor::fileUpdated(const QString& fileName) {
  //TODO: ask backend to reload file
  qDebug() << "PathEdit: file" << fileName << "has been changed - need to trigger backend!";
  }

const QString PathEditor::className = "PathEditor";
