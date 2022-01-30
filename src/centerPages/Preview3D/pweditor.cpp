#include "pweditor.h"
#include <valuemanager.h>
#include <configacc.h>
#include <dynaaction.h>
#include <andcondition.h>
#include <equalcondition.h>
#include <smallercondition.h>
#include <guicore.h>
#include <gcodeeditor.h>
#include <gcodehighlighter.h>
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
 , spV(nullptr)
 , frame(nullptr)
 , view3D(nullptr)
 , previewIsCenter(false) {
  setObjectName("PreView3D");
  setWindowTitle(tr("PreView3D"));
  if (parent) setParent(parent);
  }


QWidget* PreViewEditor::createContent() {
  qDebug() << "view3D address in plugin: " << view3D;
  previewIsCenter = cfg->value("previewIsCenter").toBool();
  TestEdit::createContent();
  view3D->setMinimumSize(200, 200);
  frame = findChild<QFrame*>("GCodeEditorForm");
  if (!previewIsCenter) {
     spV = new QSplitter(Qt::Vertical);
     spV->addWidget(view3D);
     spV->addWidget(frame);
     view3D->installEventFilter(this);
     cfg->beginGroup("PreViewEditor");
     spV->restoreState(cfg->value("vState").toByteArray());
     cfg->endGroup();
     }
  ed->installEventFilter(this);
  ed->setWordWrapMode(QTextOption::NoWrap);
  ed->setReadOnly(true);
  pbOpen->hide();
  pbSave->hide();

  return previewIsCenter ? frame : spV;
  }


void PreViewEditor::connectSignals() {
  // curLine will be set by backend
  connect(vm->getModel("curLine", 0), &ValueModel::valueChanged, this, &PreViewEditor::setCurrentLine);
  // edLine is set by pathEditor
  connect(vm->getModel("edLine", 0), &ValueModel::valueChanged, this, &PreViewEditor::setEditorLine);
  connect(vm->getModel("fileName", " "), &ValueModel::valueChanged, this, &PreViewEditor::reallyLoadFile);
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
  if (spV) {
     cfg->beginGroup("PreViewEditor");
     cfg->setValue("vState", spV->saveState());
     cfg->endGroup();
     }
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
          case Qt::Key_3: view3D->iso1View();  return true;
          case Qt::Key_6: view3D->iso2View();  return true;
          }
       }
    else {
       switch (e->key()) {
         case Qt::Key_F:    view3D->fitAll(); return true;
         case Qt::Key_Up:   prevEditorLine(); return true;
         case Qt::Key_Down: nextEditorLine(); return true;
         }
       }
    }
  return false;
  }


void PreViewEditor::nextEditorLine() {
  ValueModel* m  = vm->getModel("edLine");
  qlonglong   ln = m->getValue().toLongLong();

  core->stopTimer();
  qDebug() << "PV: address of <edLine>" << m;
  m->setValue(ln + 1);
  }


void PreViewEditor::prevEditorLine() {
  ValueModel* m  = vm->getModel("edLine");
  qlonglong   ln = m->getValue().toLongLong();

  core->stopTimer();
  qDebug() << "PV: address of <edLine>" << m;
  m->setValue(ln - 1);
  }


void PreViewEditor::patch(void *pk, void *pc, void *pv, void *pu, bool flag) {
  TestEdit::patch(pk, pc, pv, pu, flag);
  qDebug() << "PVE: viewer has address:" << pu;
  view3D = (OcctQtViewer*)pu;
  }


void PreViewEditor::updateStyles() {
  TestEdit::updateStyles();
  }


QAction* PreViewEditor::viewAction() {
  if (!action) {
     action = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                           , QIcon(":SK_Auto.png")
                           , QIcon(":SK_Auto_active.png")
                           , tr("Auto-mode")
                           , (new AndCondition(new EqualCondition(vm->getModel("taskState"), GuiCore::taskStateOn)
                                             , new EqualCondition(vm->getModel("allHomed"), true)))
                                ->addCondition(new EqualCondition(vm->getModel("errorActive"), false))
                            , new EqualCondition(vm->getModel("appMode"), ApplicationMode::Auto)
                            , this);
     }
  return action;
  }
