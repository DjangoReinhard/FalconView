#include <patheditor.h>
#include <valuemanager.h>
#include <configacc.h>
#include <gcodeeditor.h>
#include <gcodehighlighter.h>
#include <occtviewer.h>
#include <QSplitter>
#include <QFileDialog>
#include <QLabel>
#include <QDir>
#include <QVariant>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QPushButton>


PathEditor::PathEditor(const QString& fileName, QWidget* parent)
 : TestEdit(fileName, parent) {
  setObjectName("PathEditor");
  }


void PathEditor::loadFile(const QVariant& fileName) {
  ed->loadFile(fileName);
  fn->setText(fileName.toString());
  ValueManager().getModel("fileName", " ")->setValue(fileName.toString());
  }
