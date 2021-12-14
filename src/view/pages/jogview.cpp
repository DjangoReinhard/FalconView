#include <jogview.h>
#include <valuemanager.h>
#include <axismask.h>
#include <core.h>
#include <QDebug>
#include <QKeyEvent>
#include <QTranslator>


JogView::JogView(QWidget* parent)
 : DynCenterWidget(QString(), JogView::className, false, parent)
 , ui(new Ui::JogForm()) {
  }


JogView::~JogView() {
  }


QWidget* JogView::createContent() {
  setupUi(this);
  setObjectName(JogView::className);
  setWindowTitle(tr("JogView"));

  return nullptr;
  }


void JogView::connectSignals() {
  connect(ui->cbSingleStep, &QCheckBox::toggled, this, &JogView::singleStep);
  connect(ui->jXn, &QPushButton::clicked, this, [=]() { jog(0, -1); });
  connect(ui->jXp, &QPushButton::clicked, this, [=]() { jog(0,  1); });
  connect(ui->jYn, &QPushButton::clicked, this, [=]() { jog(1, -1); });
  connect(ui->jYp, &QPushButton::clicked, this, [=]() { jog(1,  1); });
  connect(ui->jZn, &QPushButton::clicked, this, [=]() { jog(2, -1); });
  connect(ui->jZp, &QPushButton::clicked, this, [=]() { jog(2,  1); });
  connect(ui->jAn, &QPushButton::clicked, this, [=]() { jog(3, -1); });
  connect(ui->jAp, &QPushButton::clicked, this, [=]() { jog(3,  1); });
  connect(ui->jBn, &QPushButton::clicked, this, [=]() { jog(4, -1); });
  connect(ui->jBp, &QPushButton::clicked, this, [=]() { jog(4,  1); });
  connect(ui->jCn, &QPushButton::clicked, this, [=]() { jog(5, -1); });
  connect(ui->jCp, &QPushButton::clicked, this, [=]() { jog(5,  1); });
  connect(ui->jUn, &QPushButton::clicked, this, [=]() { jog(6, -1); });
  connect(ui->jUp, &QPushButton::clicked, this, [=]() { jog(6,  1); });
  connect(ui->jVn, &QPushButton::clicked, this, [=]() { jog(7, -1); });
  connect(ui->jVp, &QPushButton::clicked, this, [=]() { jog(7,  1); });
  connect(ui->jWn, &QPushButton::clicked, this, [=]() { jog(8, -1); });
  connect(ui->jWp, &QPushButton::clicked, this, [=]() { jog(8,  1); });
  }


void JogView::jog(int axis, int step) {
  qDebug() << "jog:" << axis << "step:" << step;
  }


void JogView::singleStep(bool) {
  bool isSingleStep = ui->cbSingleStep->isChecked();

  ui->jXn->setCheckable(!isSingleStep);
  ui->jXp->setCheckable(!isSingleStep);
  ui->jYn->setCheckable(!isSingleStep);
  ui->jYp->setCheckable(!isSingleStep);
  ui->jZn->setCheckable(!isSingleStep);
  ui->jZp->setCheckable(!isSingleStep);
  ui->jAn->setCheckable(!isSingleStep);
  ui->jAp->setCheckable(!isSingleStep);
  ui->jBn->setCheckable(!isSingleStep);
  ui->jBp->setCheckable(!isSingleStep);
  ui->jCn->setCheckable(!isSingleStep);
  ui->jCp->setCheckable(!isSingleStep);
  ui->jUn->setCheckable(!isSingleStep);
  ui->jUp->setCheckable(!isSingleStep);
  ui->jVn->setCheckable(!isSingleStep);
  ui->jVp->setCheckable(!isSingleStep);
  ui->jWn->setCheckable(!isSingleStep);
  ui->jWp->setCheckable(!isSingleStep);
  }


void JogView::setupUi(DynCenterWidget *parent) {
  qDebug() << "JogView::setupUi() ...";
  ui->setupUi(parent);
  const AxisMask& am = Core().axisMask();

  if (!am.hasXAxis()) {
     ui->jXn->hide();
     ui->jXp->hide();
     }
  if (!am.hasYAxis()) {
     ui->jYn->hide();
     ui->jYp->hide();
     }
  if (!am.hasYAxis()) {
     ui->jYn->hide();
     ui->jYp->hide();
     }
  if (!am.hasZAxis()) {
     ui->jZn->hide();
     ui->jZp->hide();
     }
  if (!am.hasAAxis()) {
     ui->jAn->hide();
     ui->jAp->hide();
     }
  if (!am.hasBAxis()) {
     ui->jBn->hide();
     ui->jBp->hide();
     }
  if (!am.hasCAxis()) {
     ui->jCn->hide();
     ui->jCp->hide();
     }
  if (!am.hasUAxis()) {
     ui->jUn->hide();
     ui->jUp->hide();
     }
  if (!am.hasVAxis()) {
     ui->jVn->hide();
     ui->jVp->hide();
     }
  if (!am.hasWAxis()) {
     ui->jWn->hide();
     ui->jWp->hide();
     }
  }


void JogView::updateStyles() {
  }


void JogView::keyPressEvent(QKeyEvent* e) {
  bool shift = e->modifiers() == Qt::ShiftModifier;

  switch (e->key()) {
    case Qt::Key_X: jog(0, shift ? -1 : 1); break;
    case Qt::Key_Y: jog(1, shift ? -1 : 1); break;
    case Qt::Key_Z: jog(2, shift ? -1 : 1); break;
    case Qt::Key_A: jog(3, shift ? -1 : 1); break;
    case Qt::Key_B: jog(4, shift ? -1 : 1); break;
    case Qt::Key_C: jog(5, shift ? -1 : 1); break;
    case Qt::Key_U: jog(6, shift ? -1 : 1); break;
    case Qt::Key_V: jog(7, shift ? -1 : 1); break;
    case Qt::Key_W: jog(8, shift ? -1 : 1); break;
    default: DynCenterWidget::keyPressEvent(e); break;
    }
  }

const QString& JogView::className = "JogView";
