#include <pweditor.h>
#include <valuemanager.h>
#include <configacc.h>
#include <core.h>
#include <gcodeeditor.h>
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
 , view3D(view) {
  setObjectName(PreViewEditor::className);
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
  Config cfg;

  cfg.beginGroup(PreViewEditor::className);
  spV->restoreState(cfg.value("vState").toByteArray());
  cfg.endGroup();
  }


void PreViewEditor::connectSignals() {
  connect(ValueManager().getModel("fileName", " "), &ValueModel::valueChanged, this, &PreViewEditor::genPreView);
  TestEdit::connectSignals();
  }


void PreViewEditor::showEvent(QShowEvent* e) {
  if (e->type() == QEvent::Show) {
     view3D->setFocus();
     view3D->fitAll();
     }
  }


void PreViewEditor::keyPressEvent(QKeyEvent* e) {
  qDebug() << "PW-Edit: key pressed: " << e->key();
  switch (e->key()) {
    case Qt::Key_F:
         qDebug() << "PW-Edit: 'F' recognized ...";
         view3D->fitAll();
         e->accept();
         break;
    default:
         TestEdit::keyPressEvent(e);
         break;
    }
  }


void PreViewEditor::closeEvent(QCloseEvent*) {
  Config cfg;

  cfg.beginGroup(PreViewEditor::className);
  cfg.setValue("vState", spV->saveState());
  cfg.endGroup();
  }


void PreViewEditor::genPreView(const QVariant& fileName) {
  qDebug() << "PreViewEditor::genPreView" << fileName;
  CanonIF().toolPath().clear();
  ed->loadFile(fileName);
  fn->setText(fileName.toString());
  Core().parseGCFile(fileName.toString());
  Core().activatePage(PreViewEditor::className);
  Core().setAppMode(ApplicationMode::Auto);
  }


const QString PreViewEditor::className = "PreViewEditor";
