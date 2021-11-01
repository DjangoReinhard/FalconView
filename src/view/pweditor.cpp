#include <pweditor.h>
#include <valuemanager.h>
#include <configacc.h>
#include <core.h>
#include <gcodeeditor.h>
#include <mainview.h>
#include <gcodehighlighter.h>
#include <occtviewer.h>
#include <canonif.h>
#include <AIS_ViewCube.hxx>
#include <AIS_InteractiveContext.hxx>
#include <QSplitter>
#include <QFileDialog>
#include <QLabel>
#include <QDir>
#include <QTime>
#include <QVariant>
#include <QLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QPushButton>


PreViewEditor::PreViewEditor(const QString& fileName, OcctQtViewer* view, QWidget* parent)
 : TestEdit(fileName, parent)
 , view(view) {
  setObjectName("PreViewEditor");
  spV = new QSplitter(Qt::Vertical);
  view->setMinimumSize(400, 400);
  QWidget* w = layout()->itemAt(0)->widget();

  layout()->removeWidget(w);
  spV->addWidget(view);
  spV->addWidget(w);
  ed->setWordWrapMode(QTextOption::NoWrap);
  ed->setReadOnly(true);
  layout()->addWidget(spV);
  pbOpen->hide();
  pbSave->hide();
  ValueManager().setValue("fileName", "janeDoe");
  }


void PreViewEditor::connectSignals() {
  connect(ValueManager().getModel("fileName", " "), &ValueModel::valueChanged, this, &PreViewEditor::genPreView);
  TestEdit::connectSignals();
  }


void PreViewEditor::showEvent(QShowEvent* e) {
  if (e->type() == QEvent::Show) {
     view->setFocus();
     view->fitAll();
     }
  }


void PreViewEditor::genPreView(const QVariant& fileName) {
  qDebug() << "PreViewEditor::loadFile" << fileName;
  CanonIF().toolPath().clear();
  ed->loadFile(fileName);
  fn->setText(fileName.toString());
  Core().parseGCFile(fileName.toString());
  view->showPath(CanonIF().toolPath());
  Core().viewStack()->activatePage("PreviewEditor");
  }
