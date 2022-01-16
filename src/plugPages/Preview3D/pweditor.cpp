#include "pweditor.h"
#include <valuemanager.h>
#include <configacc.h>
#include <guicore.h>
#include <gcodeeditor.h>
#include <gcodehighlighter.h>
//#include <canonif.h>
//#include <toolstatus.h>
//#include <curcodesstatus.h>
//#include <positionstatus.h>
//#include <speedstatus.h>

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
#include <QSpacerItem>

#include <occtviewer.h>
#include <AIS_ViewCube.hxx>
#include <AIS_InteractiveContext.hxx>


PreViewEditor::PreViewEditor(QWidget* parent)
 : TestEdit()
 , frame(nullptr)
 , view3D(nullptr)
 , posStat(nullptr)
 , ccStat(nullptr)
 , toolStat(nullptr)
 , speedStat(nullptr)
 , statusInPreview(false) {
  setObjectName("PreView3D");
  setWindowTitle(tr("PreView3D"));
  if (parent) setParent(parent);
  }


QWidget* PreViewEditor::createContent() {
  qDebug() << "view3D address in plugin: " << view3D;
  statusInPreview = cfg->value("statusInPreview").toBool();
  TestEdit::createContent();
  spV = new QSplitter(Qt::Vertical);
  view3D->setMinimumSize(200, 200);
  frame = findChild<QFrame*>("GCodeEditorForm");
  spV->addWidget(view3D);
  spV->addWidget(frame);
  ed->setWordWrapMode(QTextOption::NoWrap);
  ed->setReadOnly(true);
  pbOpen->hide();
  pbSave->hide();
  //TODO: move!
  createDecorations(view3D, statusInPreview);
  cfg->beginGroup("PreViewEditor");
  spV->restoreState(cfg->value("vState").toByteArray());
  cfg->endGroup();
  view3D->installEventFilter(this);
  ed->installEventFilter(this);

  return spV;
  }


void PreViewEditor::connectSignals() {
  // curLine will be set by backend
  connect(vm->getModel("curLine", 0), &ValueModel::valueChanged, this, &PreViewEditor::setCurrentLine);
  // edLine is set by pathEditor
  connect(vm->getModel("edLine", 0), &ValueModel::valueChanged, this, &PreViewEditor::setEditorLine);
  TestEdit::connectSignals();
  }


void PreViewEditor::showEvent(QShowEvent* e) {
  TestEdit::showEvent(e);
  if (e->type() == QEvent::Show) {
     ed->setFocus();
     view3D->fitAll();
     }
  }


void PreViewEditor::setCurrentLine(const QVariant& line) {
  QTextDocument* d  = ed->document();
  QTextBlock     b0 = d->findBlockByLineNumber(fmax(0, line.toInt() - 3));
  QTextBlock     b1 = d->findBlockByLineNumber(line.toInt() - 2);
  QTextCursor    c0(b0);
  QTextCursor    c1(b1);

  qDebug() << "PWE::setCurrentLine(" << line << ")";
  ed->moveCursor(QTextCursor::End);
  ed->setTextCursor(c0);
  ed->setTextCursor(c1);
  }


void PreViewEditor::setEditorLine(const QVariant& line) {
  QTextDocument* d  = ed->document();
  QTextBlock     b0 = d->findBlockByLineNumber(fmax(0, line.toInt()));

  qDebug() << "PWE::setEditorLine(" << line << ")";

  ed->moveCursor(QTextCursor::End);
  ed->setTextCursor(QTextCursor(b0));
  }


void PreViewEditor::closeEvent(QCloseEvent* e) {
  cfg->beginGroup("PreViewEditor");
  cfg->setValue("vState", spV->saveState());
  cfg->endGroup();
  TestEdit::closeEvent(e);
  }


QString PreViewEditor::currentRow() const {
  return ed->textCursor().block().text();
  }


long PreViewEditor::curLine() const {
  return ed->textCursor().block().blockNumber();
  }


bool PreViewEditor::eventFilter(QObject*, QEvent* event) {
  if (event->type() == QEvent::KeyPress) {
     QKeyEvent* e = static_cast<QKeyEvent*>(event);

     if (e->modifiers() == Qt::CTRL) {
        switch (e->key()) {
          case Qt::Key_T: view3D->topView();   return true;
          case Qt::Key_R: view3D->rightView(); return true;
          case Qt::Key_L: view3D->leftView();  return true;
          case Qt::Key_B: view3D->backView();  return true;
          case Qt::Key_F: view3D->frontView(); return true;
          case Qt::Key_3: view3D->isoView();   return true;
          }
       }
    else if (e->key() == Qt::Key_F) {
       view3D->fitAll();
       return true;
       }
    }
  return false;
  }


void PreViewEditor::createDecorations(OcctQtViewer *v, bool sip) {
  if (!sip) return;
  QGridLayout* gl = new QGridLayout(v);

  qDebug() << "\tTODO: need to rethink create decorations!";
  assert(!sip);
  v->setLayout(gl);
//  ccStat    = new CurCodesStatus(":/src/UI/VCurCodes.ui");
//  toolStat  = new ToolStatus(":/src/UI/ToolInfo.ui", statusInPreview);
//  speedStat = new SpeedStatus(":/src/UI/VSpeedInfo.ui");
//  posStat   = new PositionStatus(":/src/UI/Position.ui", GuiCore().axisMask());
  QSpacerItem* hs = new QSpacerItem(250, 30, QSizePolicy::Maximum, QSizePolicy::Ignored);
  QSpacerItem* vs = new QSpacerItem(20, 350, QSizePolicy::Ignored, QSizePolicy::Maximum);

//  toolStat->initialize();
//  ccStat->initialize();
//  posStat->initialize();
//  speedStat->initialize();
  gl->setColumnStretch(0, 0);
  gl->setColumnStretch(1, 1);
  gl->setColumnStretch(2, 20);
  gl->setColumnStretch(3, 0);
  gl->setRowStretch(0, 0);
  gl->setRowStretch(1, 1);
  gl->setRowStretch(2, 20);
//  gl->addWidget(ccStat, 0, 0, 3, 1);
//  gl->addWidget(toolStat, 0, 1, 1, 2);
//  gl->addWidget(speedStat, 0, 4, 3, 1);
//  gl->addWidget(posStat, 1, 1, 1, 1);
  gl->addItem(hs, 1, 2);
  gl->addItem(vs, 2, 1);
  }


//void PreViewEditor::genPreView(const QVariant& fileName) {
//  qDebug() << "PreViewEditor::genPreView" << fileName;
//  CanonIF().toolPath().clear();
//  ed->loadFile(fileName);
//  fn->setText(fileName.toString());
////  core->parseGCFile(fileName.toString());
////  core->setAppMode(ApplicationMode::Auto);
//  }


void PreViewEditor::patch(void *pk, void *pc, void *pv, void *pu) {
  TestEdit::patch(pk, pc, pv, pu);
  qDebug() << "PVE: viewer has address:" << pu;
  view3D = (OcctQtViewer*)pu;
  }


void PreViewEditor::updateStyles() {
  TestEdit::updateStyles();
  }


void PreViewEditor::toggleSub() {
//  QWidget* oldSub = spV->widget(1);
//  QWidget* old;

//  if (oldSub == frame) old = spV->replaceWidget(1, jp);
//  else                 old = spV->replaceWidget(1, frame);
//  qDebug() << "old widget: " << old;
  }
