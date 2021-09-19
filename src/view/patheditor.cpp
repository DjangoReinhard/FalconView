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
  setObjectName("PathEditor");
  }


void PathEditor::loadFile(const QVariant& fileName) {
  qDebug() << "PathEditor::loadFile" << fileName;
  ed->loadFile(fileName);
  fn->setText(fileName.toString());
  ValueManager().getModel("fileName", " ")->setValue(fileName.toString());
  Core().viewStack()->activatePage("PreViewEditor");
  }
