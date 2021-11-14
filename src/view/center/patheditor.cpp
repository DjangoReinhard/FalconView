#include <patheditor.h>
#include <valuemanager.h>
#include <mainview.h>
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

  }


void PathEditor::connectSignals() {
  connect(ValueManager().getModel("fileName", " "), &ValueModel::valueChanged, this, &PathEditor::reallyLoadFile);
  TestEdit::connectSignals();
  }


// called from TestEdit::fileSelected
void PathEditor::loadFile(const QVariant& fileName) {
  if (Core().isBackendActive()) {
     qDebug() << "PathEditor::loadFile (backend active)" << fileName;
     //TODO: send command to backend, which in turn changes filename vm
     }
  else ValueManager().setValue("fileName", fileName);
  }


void PathEditor::reallyLoadFile(const QVariant& fileName) {
  TestEdit::loadFile(fileName);
  Core().setAppMode(ApplicationMode::Edit);
  }


const QString PathEditor::className = "PathEditor";
