#include <jogview.h>
#include <configacc.h>
#include <valuemanager.h>
#include <axismask.h>
#include <core.h>
#include <QDebug>
#include <QKeyEvent>
#include <QTranslator>


JogView::JogView(QWidget* parent)
 : DynCenterWidget(QString(), JogView::className, false, parent)
 , ui(new Ui::JogForm()) {
  setObjectName(JogView::className);
  setWindowTitle(tr("JogView"));
  }


JogView::~JogView() {
  }


//[TRAJ]
//COORDINATES = X Y Y Z W A
//LINEAR_UNITS = mm
//ANGULAR_UNITS = degree
//DEFAULT_LINEAR_VELOCITY = 20.00
//MAX_LINEAR_VELOCITY = 200.00
QWidget* JogView::createContent() {
  setupUi(this);
  defSpeed = Core().lcProperties().value("TRAJ", "DEFAULT_LINEAR_VELOCITY").toDouble() * 60;
  maxSpeed = Core().lcProperties().value("TRAJ", "MAX_LINEAR_VELOCITY").toDouble() * 60;
  jogVelChanged();
  sliderChanged(ui->slJog->value());

  return nullptr;
  }


void JogView::connectSignals() {
  connect(ui->cbSingleStep, &QCheckBox::toggled, this, &JogView::singleStep);
  connect(ui->jXn, &QToolButton::clicked, this, [=]() { jog(0, -1); });
  connect(ui->jXp, &QToolButton::clicked, this, [=]() { jog(0,  1); });
  connect(ui->jYn, &QToolButton::clicked, this, [=]() { jog(1, -1); });
  connect(ui->jYp, &QToolButton::clicked, this, [=]() { jog(1,  1); });
  connect(ui->jZn, &QToolButton::clicked, this, [=]() { jog(2, -1); });
  connect(ui->jZp, &QToolButton::clicked, this, [=]() { jog(2,  1); });
  connect(ui->jAn, &QToolButton::clicked, this, [=]() { jog(3, -1); });
  connect(ui->jAp, &QToolButton::clicked, this, [=]() { jog(3,  1); });
  connect(ui->jBn, &QToolButton::clicked, this, [=]() { jog(4, -1); });
  connect(ui->jBp, &QToolButton::clicked, this, [=]() { jog(4,  1); });
  connect(ui->jCn, &QToolButton::clicked, this, [=]() { jog(5, -1); });
  connect(ui->jCp, &QToolButton::clicked, this, [=]() { jog(5,  1); });
  connect(ui->jUn, &QToolButton::clicked, this, [=]() { jog(6, -1); });
  connect(ui->jUp, &QToolButton::clicked, this, [=]() { jog(6,  1); });
  connect(ui->jVn, &QToolButton::clicked, this, [=]() { jog(7, -1); });
  connect(ui->jVp, &QToolButton::clicked, this, [=]() { jog(7,  1); });
  connect(ui->jWn, &QToolButton::clicked, this, [=]() { jog(8, -1); });
  connect(ui->jWp, &QToolButton::clicked, this, [=]() { jog(8,  1); });
  connect(ui->cbRapid, &QCheckBox::toggled, this, &JogView::jogVelChanged);
  connect(ui->slJog, &QSlider::valueChanged, this, &JogView::sliderChanged);
  connect(ui->rOOO1, &QRadioButton::toggled, this, &JogView::stepSizeChanged);
  connect(ui->rOO1, &QRadioButton::toggled, this, &JogView::stepSizeChanged);
  connect(ui->rO1, &QRadioButton::toggled, this, &JogView::stepSizeChanged);
  connect(ui->rO5, &QRadioButton::toggled, this, &JogView::stepSizeChanged);
  }


//[TRAJ]
//COORDINATES = X Y Y Z W A
//LINEAR_UNITS = mm
//ANGULAR_UNITS = degree
//DEFAULT_LINEAR_VELOCITY = 20.00
//MAX_LINEAR_VELOCITY = 200.00
void JogView::jog(int axis, int step) {
  qDebug() << "jog:"  << axis << "step:" << step;
  qDebug() << "size:" << ui->cmdJogSpeed->size();
  }


void JogView::sliderChanged(const QVariant& v) {
  qDebug() << "jog speed override:" << v;
  double jogFactor = v.toDouble();
  double jogSpeed  = ui->cbRapid->isChecked() ? maxSpeed : defSpeed;

  jogSpeed *= jogFactor / 100.0;
  QString templ = QString("<p><b>%1</b></p><p>&nbsp;</p><p>%2 %</p>")
                         .arg(Core().locale().toString(jogSpeed, 'f', 0))
                         .arg(jogFactor, 0, 'f', 0);

  ui->curJog->setText(templ);
  }


void JogView::jogVelChanged() {
  if (ui->cbRapid->isChecked())
     ui->cmdJogSpeed->setText(Core().locale().toString(maxSpeed, 'f', 0));
  else
     ui->cmdJogSpeed->setText(Core().locale().toString(defSpeed, 'f', 0));
  sliderChanged(ui->slJog->value());
  }


void JogView::stepSizeChanged() {
  if (ui->rOOO1->isChecked())     stepSize = 0.001;
  else if (ui->rOO1->isChecked()) stepSize = 0.01;
  else if (ui->rO1->isChecked())  stepSize = 0.1;
  else if (ui->rO5->isChecked())  stepSize = 0.5;
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
