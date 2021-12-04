#include <pweditor.h>
#include <valuemanager.h>
#include <configacc.h>
#include <core.h>
#include <gcodeeditor.h>
#include <gcodehighlighter.h>
#include <occtviewer.h>
#include <canonif.h>
#include <jogview.h>
#include <AIS_ViewCube.hxx>
#include <AIS_InteractiveContext.hxx>
#include <toolstatus.h>
#include <curcodesstatus.h>
#include <positionstatus.h>
#include <speedstatus.h>
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

PreViewEditor::PreViewEditor(const QString& fileName, OcctQtViewer* view, bool statusInPreview, QWidget* parent)
 : TestEdit(fileName, parent)
 , frame(nullptr)
 , jp(nullptr)
 , view3D(view)
 , posStat(nullptr)
 , ccStat(nullptr)
 , toolStat(nullptr)
 , speedStat(nullptr)
 , statusInPreview(statusInPreview) {
  setObjectName(PreViewEditor::className);
  setWindowTitle(PreViewEditor::className);
  }


QWidget* PreViewEditor::createContent() {
  TestEdit::createContent();
  spV = new QSplitter(Qt::Vertical);
  view3D->setMinimumSize(400, 400);
  frame = findChild<QFrame*>("GCodeEditorForm");
  spV->addWidget(view3D);
  spV->addWidget(frame);
  ed->setWordWrapMode(QTextOption::NoWrap);
  ed->setReadOnly(true);
  pbOpen->hide();
  pbSave->hide();
  jp = new JogView();
  ValueManager().setValue("fileName", "janeDoe");
  createDecorations(view3D, statusInPreview);
  Config cfg;

  cfg.beginGroup(PreViewEditor::className);
  spV->restoreState(cfg.value("vState").toByteArray());
  cfg.endGroup();

  return spV;
  }


void PreViewEditor::connectSignals() {
  connect(ValueManager().getModel("fileName", " "), &ValueModel::valueChanged, this, &PreViewEditor::genPreView);
  connect(ValueManager().getModel("curLine", 0), &ValueModel::valueChanged, this, &PreViewEditor::setCurrentLine);
  TestEdit::connectSignals();
  }


void PreViewEditor::showEvent(QShowEvent* e) {
  if (e->type() == QEvent::Show) {
     view3D->setFocus();
     view3D->fitAll();
     }
  }


void PreViewEditor::setCurrentLine(const QVariant& line) {
  QTextDocument* d  = ed->document();
  QTextBlock     b0 = d->findBlockByLineNumber(fmax(0, line.toInt() - 3));
  QTextBlock     b1 = d->findBlockByLineNumber(line.toInt() - 2);
  QTextCursor    c0(b0);
  QTextCursor    c1(b1);

//  qDebug() << "PWE::setCurrentLine(" << line << ")";
  ed->moveCursor(QTextCursor::End);
  ed->setTextCursor(c0);
  ed->setTextCursor(c1);
  }


void PreViewEditor::closeEvent(QCloseEvent*) {
  Config cfg;

  cfg.beginGroup(PreViewEditor::className);
  cfg.setValue("vState", spV->saveState());
  cfg.endGroup();
  }


void PreViewEditor::createDecorations(OcctQtViewer *v, bool sip) {
  if (!sip) return;
  QGridLayout* gl = new QGridLayout(v);

  v->setLayout(gl);
  toolStat = new ToolStatus(":/src/UI/ToolInfo.ui");
  ccStat = new CurCodesStatus(":/src/UI/VCurCodes.ui");
  posStat = new PositionStatus(":/src/UI/Position.ui", Core().axisMask());
  speedStat = new SpeedStatus(":/src/UI/VSpeedInfo.ui");
  QSpacerItem* hs = new QSpacerItem(250, 30, QSizePolicy::Maximum, QSizePolicy::Ignored);
  QSpacerItem* vs = new QSpacerItem(20, 350, QSizePolicy::Ignored, QSizePolicy::Maximum);

  toolStat->initialize();
  ccStat->initialize();
  posStat->initialize();
  speedStat->initialize();
  gl->setColumnStretch(0, 0);
  gl->setColumnStretch(1, 1);
  gl->setColumnStretch(2, 20);
  gl->setColumnStretch(3, 0);
  gl->setRowStretch(0, 0);
  gl->setRowStretch(1, 1);
  gl->setRowStretch(2, 20);
  gl->addWidget(ccStat, 0, 0, 3, 1);
  gl->addWidget(toolStat, 0, 1, 1, 2);
  gl->addWidget(speedStat, 0, 4, 3, 1);
  gl->addWidget(posStat, 1, 1, 1, 1);
  gl->addItem(hs, 1, 2);
  gl->addItem(vs, 2, 1);
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


void PreViewEditor::toggleSub() {
  QWidget* oldSub = spV->widget(1);
  QWidget* old;

  if (oldSub == frame) {
     jp->initialize();
     old = spV->replaceWidget(1, jp);
     }
  else {
     old = spV->replaceWidget(1, frame);
     }
  qDebug() << "old widget: " << old;;
  }

const QString PreViewEditor::className = "3D Preview";
