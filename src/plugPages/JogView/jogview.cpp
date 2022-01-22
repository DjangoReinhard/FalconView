#include "jogview.h"
#include <configacc.h>
#include <valuemanager.h>
#include <dynaaction.h>
#include <andcondition.h>
#include <equalcondition.h>
#include <smallercondition.h>
#include <axismask.h>
#include <guicore.h>
#include <QDebug>
#include <QKeyEvent>
#include <QButtonGroup>
#include <QToolButton>
#include <QTranslator>


JogView::JogView(QWidget* parent)
 : AbstractCenterWidget(QString(), parent)
 , ui(new Ui::JogForm()) {
  setObjectName("JogView");
  setWindowTitle(tr("JogView"));
  }


JogView::~JogView() {
  }


void JogView::closeEvent(QCloseEvent* e) {
  QWidget::closeEvent(e);
  }


QWidget* JogView::createContent() {
  setupUi(this);
// button groups don't support unchecking of checked button,
// so we need an ugly hack like this :(
  ui->jXn->init(ui->jXp);
  ui->jXp->init(ui->jXn);
  ui->jYn->init(ui->jYp);
  ui->jYp->init(ui->jYn);
  ui->jZn->init(ui->jZp);
  ui->jZp->init(ui->jZn);
  ui->jAn->init(ui->jAp);
  ui->jAp->init(ui->jAn);
  ui->jBn->init(ui->jBp);
  ui->jBp->init(ui->jBn);
  ui->jCn->init(ui->jCp);
  ui->jCp->init(ui->jCn);
  ui->jUn->init(ui->jUp);
  ui->jUp->init(ui->jUn);
  ui->jVn->init(ui->jVp);
  ui->jVp->init(ui->jVn);
  ui->jWn->init(ui->jWp);
  ui->jWp->init(ui->jWn);

  rbl.append(ui->rOOO1);
  rbl.append(ui->rOO1);
  rbl.append(ui->rO1);
  rbl.append(ui->rO5);
  ui->rOOO1->installEventFilter(this);
  ui->rOO1->installEventFilter(this);
  ui->rO1->installEventFilter(this);
  ui->rO5->installEventFilter(this);
  ui->slJog->installEventFilter(this);
  defSpeed = core->defaultVelocity();
  maxSpeed = core->maxVelocity();
  singleStep(ui->cbSingleStep->isChecked());
  setStepSize();
  jogVelChanged();
  sliderChanged(ui->slJog->value());

  return nullptr;
  }


void JogView::connectSignals() {
  connect(ui->jXn, &QToolButton::clicked, this, [=]() { jog(ui->jXn, 0, -1); });
  connect(ui->jXp, &QToolButton::clicked, this, [=]() { jog(ui->jXp, 0,  1); });
  connect(ui->jYn, &QToolButton::clicked, this, [=]() { jog(ui->jYn, 1, -1); });
  connect(ui->jYp, &QToolButton::clicked, this, [=]() { jog(ui->jYp, 1,  1); });
  connect(ui->jZn, &QToolButton::clicked, this, [=]() { jog(ui->jZn, 2, -1); });
  connect(ui->jZp, &QToolButton::clicked, this, [=]() { jog(ui->jZp, 2,  1); });
  connect(ui->jAn, &QToolButton::clicked, this, [=]() { jog(ui->jAn, 3, -1); });
  connect(ui->jAp, &QToolButton::clicked, this, [=]() { jog(ui->jAp, 3,  1); });
  connect(ui->jBn, &QToolButton::clicked, this, [=]() { jog(ui->jBn, 4, -1); });
  connect(ui->jBp, &QToolButton::clicked, this, [=]() { jog(ui->jBp, 4,  1); });
  connect(ui->jCn, &QToolButton::clicked, this, [=]() { jog(ui->jCn, 5, -1); });
  connect(ui->jCp, &QToolButton::clicked, this, [=]() { jog(ui->jCp, 5,  1); });
  connect(ui->jUn, &QToolButton::clicked, this, [=]() { jog(ui->jUn, 6, -1); });
  connect(ui->jUp, &QToolButton::clicked, this, [=]() { jog(ui->jUp, 6,  1); });
  connect(ui->jVn, &QToolButton::clicked, this, [=]() { jog(ui->jVn, 7, -1); });
  connect(ui->jVp, &QToolButton::clicked, this, [=]() { jog(ui->jVp, 7,  1); });
  connect(ui->jWn, &QToolButton::clicked, this, [=]() { jog(ui->jWn, 8, -1); });
  connect(ui->jWp, &QToolButton::clicked, this, [=]() { jog(ui->jWp, 8,  1); });

  connect(vm->getModel("jogFactor"),   &ValueModel::valueChanged, this, &JogView::sliderChanged);
  connect(vm->getModel("jogRapid"),    &ValueModel::valueChanged, ui->cbRapid, [=](const QVariant& v){ ui->cbRapid->setChecked(v.toBool()); });
  connect(vm->getModel("jogStepSize"), &ValueModel::valueChanged, this, &JogView::stepSizeChanged);

  connect(ui->cbSingleStep, &QCheckBox::toggled, this, &JogView::singleStep);
  connect(ui->cbRapid, &QCheckBox::toggled, this, &JogView::jogVelChanged);
  connect(ui->slJog, &QSlider::valueChanged, this, &JogView::sliderChanged);
  connect(ui->rOOO1, &QRadioButton::toggled, this, &JogView::setStepSize);
  connect(ui->rOO1, &QRadioButton::toggled, this, &JogView::setStepSize);
  connect(ui->rO1, &QRadioButton::toggled, this, &JogView::setStepSize);
  connect(ui->rO5, &QRadioButton::toggled, this, &JogView::setStepSize);
  }


void JogView::jog(QWidget* o, int axis, int step) {
  qDebug() << "jog:"  << axis << "dir:" << step;
  double speed = jogSpeed / 60.0;

  if (ui->cbHome->isChecked()) {
     core->beHomeAxis(axis);
     }
  else {
     if (ui->cbSingleStep->isChecked()) {
        qDebug() << "step single step of size:" << stepSize << "with:" << speed;
        core->beJogStep(axis, stepSize, step * speed);
        }
     else {
        QToolButton* tb = static_cast<QToolButton*>(o);

        if ((tb && tb->isChecked()) || !tb) {
           qDebug() << "start jogging with speed" << speed;
           core->beJogStart(axis, step * speed);
           }
        else {
           qDebug() << "stop jogging of axis" << axis;
           core->beJogStop(axis);
           }
        }
     }
  }


void JogView::sliderChanged(const QVariant& v) {
//  qDebug() << "jog speed override:" << v;
  double jogFactor = v.toDouble();

  vm->setValue("jogFactor", v);
  jogSpeed  = (ui->cbRapid->isChecked() ? maxSpeed : defSpeed)
            * jogFactor / 100.0;
  QString templ = QString("<p><b>%1</b></p><p>&nbsp;</p><p>%2 %</p>")
                         .arg(core->locale().toString(jogSpeed, 'f', 0))
                         .arg(jogFactor, 0, 'f', 0);

  ui->curJog->setText(templ);
  }


void JogView::jogVelChanged() {
//  vm->setValue("jogRapid", ui->cbRapid->isChecked());
  if (ui->cbRapid->isChecked())
     ui->cmdJogSpeed->setText(core->locale().toString(maxSpeed, 'f', 0));
  else
     ui->cmdJogSpeed->setText(core->locale().toString(defSpeed, 'f', 0));
  sliderChanged(ui->slJog->value());
  }


void JogView::stepSizeChanged(const QVariant &stepSize) {
  double ss = stepSize.toDouble();

  if (ss == 0.001)     ui->rOOO1->setChecked(true);
  else if (ss == 0.01) ui->rOO1->setChecked(true);
  else if (ss == 0.1)  ui->rO1->setChecked(true);
  else if (ss == 0.5)  ui->rO5->setChecked(true);
  }


void JogView::setStepSize() {
  if (ui->rOOO1->isChecked())     stepSize = 0.001;
  else if (ui->rOO1->isChecked()) stepSize = 0.01;
  else if (ui->rO1->isChecked())  stepSize = 0.1;
  else if (ui->rO5->isChecked())  stepSize = 0.5;
  vm->setValue("jogStepSize", stepSize);
  }


void JogView::incStepSize() {
  for (int i=0; i < rbl.size(); ++i) {
      switch (i) {
        case 0: if (rbl.at(i)->isChecked()) {
             rbl.at(1)->setChecked(true);
             return;
             }
             [[fallthrough]];
        case 1: if (rbl.at(i)->isChecked()) {
             rbl.at(2)->setChecked(true);
             return;
             }
             [[fallthrough]];
        case 2: if (rbl.at(i)->isChecked()) {
             rbl.at(3)->setChecked(true);
             return;
             }
             [[fallthrough]];
        case 3: if (rbl.at(i)->isChecked()) {
             rbl.at(0)->setChecked(true);
             return;
             }
        }
      }
  }


void JogView::decStepSize() {
  for (int i=0; i < rbl.size(); ++i) {
      switch (i) {
        case 0: if (rbl.at(i)->isChecked()) {
             rbl.at(3)->setChecked(true);
             return;
             }
             [[fallthrough]];
        case 1: if (rbl.at(i)->isChecked()) {
             rbl.at(0)->setChecked(true);
             return;
             }
             [[fallthrough]];
        case 2: if (rbl.at(i)->isChecked()) {
             rbl.at(1)->setChecked(true);
             return;
             }
             [[fallthrough]];
        case 3: if (rbl.at(i)->isChecked()) {
             rbl.at(2)->setChecked(true);
             return;
             }
        }
      }
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


void JogView::setupUi(AbstractCenterWidget *parent) {
  qDebug() << "JogView::setupUi() ...";
  ui->setupUi(parent);
  AxisMask am(core->axisMask());

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


bool JogView::eventFilter(QObject*, QEvent* event) {
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent* e = static_cast<QKeyEvent*>(event);

    switch (e->key()) {
      case Qt::Key_Up: {
           int value = ui->slJog->value() + 1;

           if (value > 100) value = 100;
           ui->slJog->setValue(value);
           return true;
           }
           [[fallthrough]];
      case Qt::Key_Down: {
           int value = ui->slJog->value() - 1;

           if (value < 0) value = 0;
           ui->slJog->setValue(value);
           return true;
           }
           [[fallthrough]];
      case Qt::Key_Right:
           incStepSize();
           return true;
      case Qt::Key_Left:
           decStepSize();
           return true;
      }
    }
  return false;
  }


void JogView::keyPressEvent(QKeyEvent* e) {
  if (e->modifiers() == Qt::ShiftModifier) {
     switch (e->key()) {
       case Qt::Key_X: ui->jXp->click(); break;
       case Qt::Key_Y: ui->jYp->click(); break;
       case Qt::Key_Z: ui->jZp->click(); break;
       case Qt::Key_A: ui->jAp->click(); break;
       case Qt::Key_B: ui->jBp->click(); break;
       case Qt::Key_C: ui->jCp->click(); break;
       case Qt::Key_U: ui->jUp->click(); break;
       case Qt::Key_V: ui->jVp->click(); break;
       case Qt::Key_W: ui->jWp->click(); break;
       default: AbstractCenterWidget::keyPressEvent(e); break;
       }
     }
  else {
     switch (e->key()) {
       case Qt::Key_X: ui->jXn->toggle(); break;
       case Qt::Key_Y: ui->jYn->toggle(); break;
       case Qt::Key_Z: ui->jZn->toggle(); break;
       case Qt::Key_A: ui->jAn->toggle(); break;
       case Qt::Key_B: ui->jBn->toggle(); break;
       case Qt::Key_C: ui->jCn->toggle(); break;
       case Qt::Key_U: ui->jUn->toggle(); break;
       case Qt::Key_V: ui->jVn->toggle(); break;
       case Qt::Key_W: ui->jWn->toggle(); break;
       default: AbstractCenterWidget::keyPressEvent(e); break;
       }
     }
  }


void JogView::showEvent(QShowEvent* e) {
  QWidget::showEvent(e);
  }


QAction* JogView::viewAction() {
  if (!action) {
     action = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                           , QIcon(":SK_Manual.png")
                           , QIcon(":SK_Manual_active.png")
                           , tr("Manual-mode")
                           , (new AndCondition(new EqualCondition(vm->getModel("taskState"), GuiCore::taskStateOn)
                                             , new SmallerCondition(vm->getModel("execState"), GuiCore::taskWaiting4Motion)))
                                ->addCondition(new EqualCondition(vm->getModel("errorActive"), false))
                           , new EqualCondition(vm->getModel("appMode"), ApplicationMode::Manual)
                           , this);
     }
  return action;
  }
