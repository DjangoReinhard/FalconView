#include <positiondockable.h>
#include <valuemanager.h>
#include <QtUiTools/QUiLoader>
#include <QFontMetrics>
#include <QGridLayout>
#include <QString>
#include <QFile>
#include <iostream>


PositionDockable::PositionDockable(const QString& fileName, const AxisMask& am, QWidget* parent)
 : Dockable(fileName, tr("Position"), parent)
 , lblX(nullptr)
 , lblY(nullptr)
 , lblZ(nullptr)
 , lblA(nullptr)
 , lblB(nullptr)
 , lblC(nullptr)
 , lblU(nullptr)
 , lblV(nullptr)
 , lblW(nullptr)
 , ledX(nullptr)
 , ledY(nullptr)
 , ledZ(nullptr)
 , ledA(nullptr)
 , ledB(nullptr)
 , ledC(nullptr)
 , ledU(nullptr)
 , ledV(nullptr)
 , ledW(nullptr)
 , relX(nullptr)
 , relY(nullptr)
 , relZ(nullptr)
 , relA(nullptr)
 , relB(nullptr)
 , relC(nullptr)
 , relU(nullptr)
 , relV(nullptr)
 , relW(nullptr)
 , absX(nullptr)
 , absY(nullptr)
 , absZ(nullptr)
 , absA(nullptr)
 , absB(nullptr)
 , absC(nullptr)
 , absU(nullptr)
 , absV(nullptr)
 , absW(nullptr)
 , dtgX(nullptr)
 , dtgY(nullptr)
 , dtgZ(nullptr)
 , dtgA(nullptr)
 , dtgB(nullptr)
 , dtgC(nullptr)
 , dtgU(nullptr)
 , dtgV(nullptr)
 , dtgW(nullptr)
 , height(0)
 , absolute(true)
 , axisMask(am)
 , ledOn("background: #0F0")
 , ledOff("background: red") {
  initializeWidget(widget());
  }


PositionDockable::PositionDockable(const QString& fileName, const AxisMask& am, QWidget* parent, QString ledOnStyle, QString ledOffStyle)
 : Dockable(fileName, tr("Position"), parent)
 , lblX(nullptr)
 , lblY(nullptr)
 , lblZ(nullptr)
 , lblA(nullptr)
 , lblB(nullptr)
 , lblC(nullptr)
 , lblU(nullptr)
 , lblV(nullptr)
 , lblW(nullptr)
 , ledX(nullptr)
 , ledY(nullptr)
 , ledZ(nullptr)
 , ledA(nullptr)
 , ledB(nullptr)
 , ledC(nullptr)
 , ledU(nullptr)
 , ledV(nullptr)
 , ledW(nullptr)
 , relX(nullptr)
 , relY(nullptr)
 , relZ(nullptr)
 , relA(nullptr)
 , relB(nullptr)
 , relC(nullptr)
 , relU(nullptr)
 , relV(nullptr)
 , relW(nullptr)
 , absX(nullptr)
 , absY(nullptr)
 , absZ(nullptr)
 , absA(nullptr)
 , absB(nullptr)
 , absC(nullptr)
 , absU(nullptr)
 , absV(nullptr)
 , absW(nullptr)
 , dtgX(nullptr)
 , dtgY(nullptr)
 , dtgZ(nullptr)
 , dtgA(nullptr)
 , dtgB(nullptr)
 , dtgC(nullptr)
 , dtgU(nullptr)
 , dtgV(nullptr)
 , dtgW(nullptr)
 , height(0)
 , absolute(true)
 , axisMask(am)
 , ledOn(ledOnStyle)
 , ledOff(ledOffStyle) {
  initializeWidget(widget());
  }


PositionDockable::~PositionDockable() {
  delete relX;
  delete relY;
  delete relZ;
  delete relA;
  delete relB;
  delete relC;
  delete relU;
  delete relV;
  delete relW;
  delete absX;
  delete absY;
  delete absZ;
  delete absA;
  delete absB;
  delete absC;
  delete absU;
  delete absV;
  delete absW;
  delete dtgX;
  delete dtgY;
  delete dtgZ;
  delete dtgA;
  delete dtgB;
  delete dtgC;
  delete dtgU;
  delete dtgV;
  delete dtgW;
  }


void PositionDockable::initializeWidget(QWidget* /* w */) {
  relX = new LabelAdapter(findChild<QLabel*>("posX"));
  relY = new LabelAdapter(findChild<QLabel*>("posY"));
  relZ = new LabelAdapter(findChild<QLabel*>("posZ"));
  relA = new LabelAdapter(findChild<QLabel*>("posA"));
  relB = new LabelAdapter(findChild<QLabel*>("posB"));
  relC = new LabelAdapter(findChild<QLabel*>("posC"));
  relU = new LabelAdapter(findChild<QLabel*>("posU"));
  relV = new LabelAdapter(findChild<QLabel*>("posV"));
  relW = new LabelAdapter(findChild<QLabel*>("posW"));

  absX = new LabelAdapter(new QLabel("0.000", this));
  absY = new LabelAdapter(new QLabel("0.000", this));
  absZ = new LabelAdapter(new QLabel("0.000", this));
  absA = new LabelAdapter(new QLabel("0.000", this));
  absB = new LabelAdapter(new QLabel("0.000", this));
  absC = new LabelAdapter(new QLabel("0.000", this));
  absU = new LabelAdapter(new QLabel("0.000", this));
  absV = new LabelAdapter(new QLabel("0.000", this));
  absW = new LabelAdapter(new QLabel("0.000", this));

  absX->label()->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
  absY->label()->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
  absZ->label()->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
  absA->label()->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
  absB->label()->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
  absC->label()->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
  absU->label()->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
  absV->label()->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
  absW->label()->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

  QGridLayout* gl = findChild<QGridLayout*>("gridLayout");

  gl->addWidget(absX->label(), 0, 2);
  gl->addWidget(absY->label(), 1, 2);
  gl->addWidget(absZ->label(), 2, 2);
  gl->addWidget(absA->label(), 3, 2);
  gl->addWidget(absB->label(), 4, 2);
  gl->addWidget(absC->label(), 5, 2);
  gl->addWidget(absU->label(), 6, 2);
  gl->addWidget(absV->label(), 7, 2);
  gl->addWidget(absW->label(), 8, 2);

  lblX = findChild<QLabel*>("lblX");
  lblY = findChild<QLabel*>("lblY");
  lblZ = findChild<QLabel*>("lblZ");
  lblA = findChild<QLabel*>("lblA");
  lblB = findChild<QLabel*>("lblB");
  lblC = findChild<QLabel*>("lblC");
  lblU = findChild<QLabel*>("lblU");
  lblV = findChild<QLabel*>("lblV");
  lblW = findChild<QLabel*>("lblW");

  ledX = findChild<QLabel*>("ledX");
  ledY = findChild<QLabel*>("ledY");
  ledZ = findChild<QLabel*>("ledZ");
  ledA = findChild<QLabel*>("ledA");
  ledB = findChild<QLabel*>("ledB");
  ledC = findChild<QLabel*>("ledC");
  ledU = findChild<QLabel*>("ledU");
  ledV = findChild<QLabel*>("ledV");
  ledW = findChild<QLabel*>("ledW");

  dtgX = new LabelAdapter(findChild<QLabel*>("dtgX"));
  dtgY = new LabelAdapter(findChild<QLabel*>("dtgY"));
  dtgZ = new LabelAdapter(findChild<QLabel*>("dtgZ"));
  dtgA = new LabelAdapter(findChild<QLabel*>("dtgA"));
  dtgB = new LabelAdapter(findChild<QLabel*>("dtgB"));
  dtgC = new LabelAdapter(findChild<QLabel*>("dtgC"));
  dtgU = new LabelAdapter(findChild<QLabel*>("dtgU"));
  dtgV = new LabelAdapter(findChild<QLabel*>("dtgV"));
  dtgW = new LabelAdapter(findChild<QLabel*>("dtgW"));

  setLblStyles("background: white;");
  setRelStyles("color: blue; background: #DDDDFF;");
  setAbsStyles("color: green; background: #DDFFDD;");
  setDtgStyles("color: orange; background: #FFFFDD");

  setXHomed(false);
  setYHomed(false);
  setZHomed(false);
  setAHomed(false);
  setBHomed(false);
  setCHomed(false);
  setUHomed(false);
  setVHomed(false);
  setWHomed(false);

  setRelative();
  connectSignals();
  setFontSize(relX->label()->font().pointSize());
  }


void PositionDockable::connectSignals() {
  ValueManager vm;

  connect(vm.getModel("showAbsolute", false), &ValueModel::valueChanged, this, &PositionDockable::setAbsolute);
  connect(vm.getModel("axisMask", 0x01FF), &ValueModel::valueChanged, this, &PositionDockable::setAxisMask);
  connect(vm.getModel("absX", 0), &ValueModel::valueChanged, absX, &LabelAdapter::setValue);
  connect(vm.getModel("absY", 0), &ValueModel::valueChanged, absY, &LabelAdapter::setValue);
  connect(vm.getModel("absZ", 0), &ValueModel::valueChanged, absZ, &LabelAdapter::setValue);
  connect(vm.getModel("absA", 0), &ValueModel::valueChanged, absA, &LabelAdapter::setValue);
  connect(vm.getModel("absB", 0), &ValueModel::valueChanged, absB, &LabelAdapter::setValue);
  connect(vm.getModel("absC", 0), &ValueModel::valueChanged, absC, &LabelAdapter::setValue);
  connect(vm.getModel("absU", 0), &ValueModel::valueChanged, absU, &LabelAdapter::setValue);
  connect(vm.getModel("absV", 0), &ValueModel::valueChanged, absV, &LabelAdapter::setValue);
  connect(vm.getModel("absW", 0), &ValueModel::valueChanged, absW, &LabelAdapter::setValue);
  connect(vm.getModel("relX", 0), &ValueModel::valueChanged, relX, &LabelAdapter::setValue);
  connect(vm.getModel("relY", 0), &ValueModel::valueChanged, relY, &LabelAdapter::setValue);
  connect(vm.getModel("relZ", 0), &ValueModel::valueChanged, relZ, &LabelAdapter::setValue);
  connect(vm.getModel("relA", 0), &ValueModel::valueChanged, relA, &LabelAdapter::setValue);
  connect(vm.getModel("relB", 0), &ValueModel::valueChanged, relB, &LabelAdapter::setValue);
  connect(vm.getModel("relC", 0), &ValueModel::valueChanged, relC, &LabelAdapter::setValue);
  connect(vm.getModel("relU", 0), &ValueModel::valueChanged, relU, &LabelAdapter::setValue);
  connect(vm.getModel("relV", 0), &ValueModel::valueChanged, relV, &LabelAdapter::setValue);
  connect(vm.getModel("relW", 0), &ValueModel::valueChanged, relW, &LabelAdapter::setValue);
  connect(vm.getModel("dtgX", 0), &ValueModel::valueChanged, dtgX, &LabelAdapter::setValue);
  connect(vm.getModel("dtgY", 0), &ValueModel::valueChanged, dtgY, &LabelAdapter::setValue);
  connect(vm.getModel("dtgZ", 0), &ValueModel::valueChanged, dtgZ, &LabelAdapter::setValue);
  connect(vm.getModel("dtgA", 0), &ValueModel::valueChanged, dtgA, &LabelAdapter::setValue);
  connect(vm.getModel("dtgB", 0), &ValueModel::valueChanged, dtgB, &LabelAdapter::setValue);
  connect(vm.getModel("dtgC", 0), &ValueModel::valueChanged, dtgC, &LabelAdapter::setValue);
  connect(vm.getModel("dtgU", 0), &ValueModel::valueChanged, dtgU, &LabelAdapter::setValue);
  connect(vm.getModel("dtgV", 0), &ValueModel::valueChanged, dtgV, &LabelAdapter::setValue);
  connect(vm.getModel("dtgW", 0), &ValueModel::valueChanged, dtgW, &LabelAdapter::setValue);
  connect(vm.getModel("homedJoint0", false), &ValueModel::valueChanged, this, &PositionDockable::setXHomed);
  connect(vm.getModel("homedJoint1", false), &ValueModel::valueChanged, this, &PositionDockable::setYHomed);
  connect(vm.getModel("homedJoint2", false), &ValueModel::valueChanged, this, &PositionDockable::setZHomed);
  connect(vm.getModel("homedJoint3", false), &ValueModel::valueChanged, this, &PositionDockable::setAHomed);
  connect(vm.getModel("homedJoint4", false), &ValueModel::valueChanged, this, &PositionDockable::setBHomed);
  connect(vm.getModel("homedJoint5", false), &ValueModel::valueChanged, this, &PositionDockable::setCHomed);
  connect(vm.getModel("homedJoint6", false), &ValueModel::valueChanged, this, &PositionDockable::setUHomed);
  connect(vm.getModel("homedJoint7", false), &ValueModel::valueChanged, this, &PositionDockable::setVHomed);
  connect(vm.getModel("homedJoint8", false), &ValueModel::valueChanged, this, &PositionDockable::setWHomed);
  }


void PositionDockable::setAxisMask(QVariant am) {
  if (axisMask.toInt() != am.toInt())  {
     axisMask = am.toInt();
     updatePos();
     }
  }


void PositionDockable::setRelative() {
  setAbsolute(QVariant(false));
  }


void PositionDockable::setAbsolute(QVariant arg) {
  bool abs = arg.toBool();

  if (abs != absolute)  {
     absolute = abs;
     updatePos();
     }
  }


void PositionDockable::updatePos() {
  if (absolute) {
     relX->label()->hide();
     absX->label()->show();
     relY->label()->hide();
     absY->label()->show();
     relZ->label()->hide();
     absZ->label()->show();
     relA->label()->hide();
     absA->label()->show();
     relB->label()->hide();
     absB->label()->show();
     relC->label()->hide();
     absC->label()->show();
     relU->label()->hide();
     absU->label()->show();
     relV->label()->hide();
     absV->label()->show();
     relW->label()->hide();
     absW->label()->show();
     }
  else {
     relX->label()->show();
     absX->label()->hide();
     relY->label()->show();
     absY->label()->hide();
     relZ->label()->show();
     absZ->label()->hide();
     relA->label()->show();
     absA->label()->hide();
     relB->label()->show();
     absB->label()->hide();
     relC->label()->show();
     absC->label()->hide();
     relU->label()->show();
     absU->label()->hide();
     relV->label()->show();
     absV->label()->hide();
     relW->label()->show();
     absW->label()->hide();
     }
  setActive();
  }

void PositionDockable::setActive() {
  if (!axisMask.hasXAxis()) {
     ledX->hide();
     relX->label()->hide();
     absX->label()->hide();
     lblX->hide();
     dtgX->label()->hide();
     }
  if (!axisMask.hasYAxis()) {
     ledY->hide();
     relY->label()->hide();
     absY->label()->hide();
     lblY->hide();
     dtgY->label()->hide();
     }
  if (!axisMask.hasZAxis()) {
     ledZ->hide();
     relZ->label()->hide();
     absZ->label()->hide();
     lblZ->hide();
     dtgZ->label()->hide();
     }
  if (!axisMask.hasAAxis()) {
     ledA->hide();
     relA->label()->hide();
     absA->label()->hide();
     lblA->hide();
     dtgA->label()->hide();
     }
  if (!axisMask.hasBAxis()) {
     ledB->hide();
     relB->label()->hide();
     absB->label()->hide();
     lblB->hide();
     dtgB->label()->hide();
     }
  if (!axisMask.hasCAxis()) {
     ledC->hide();
     relC->label()->hide();
     absC->label()->hide();
     lblC->hide();
     dtgC->label()->hide();
     }
  if (!axisMask.hasUAxis()) {
     ledU->hide();
     relU->label()->hide();
     absU->label()->hide();
     lblU->hide();
     dtgU->label()->hide();
     }
  if (!axisMask.hasVAxis()) {
     ledV->hide();
     relV->label()->hide();
     absV->label()->hide();
     lblV->hide();
     dtgV->label()->hide();
     }
  if (!axisMask.hasWAxis()) {
     ledW->hide();
     relW->label()->hide();
     absW->label()->hide();
     lblW->hide();
     dtgW->label()->hide();
     }
  }


void PositionDockable::setAbsStyles(QString styles) {
  absX->label()->setStyleSheet(styles);
  absY->label()->setStyleSheet(styles);
  absZ->label()->setStyleSheet(styles);
  absA->label()->setStyleSheet(styles);
  absB->label()->setStyleSheet(styles);
  absC->label()->setStyleSheet(styles);
  absU->label()->setStyleSheet(styles);
  absV->label()->setStyleSheet(styles);
  absW->label()->setStyleSheet(styles);
  }


void PositionDockable::setRelStyles(QString styles) {
  relX->label()->setStyleSheet(styles);
  relY->label()->setStyleSheet(styles);
  relZ->label()->setStyleSheet(styles);
  relA->label()->setStyleSheet(styles);
  relB->label()->setStyleSheet(styles);
  relC->label()->setStyleSheet(styles);
  relU->label()->setStyleSheet(styles);
  relV->label()->setStyleSheet(styles);
  relW->label()->setStyleSheet(styles);
  }


void PositionDockable::setLblStyles(QString styles) {
  lblX->setStyleSheet(styles);
  lblY->setStyleSheet(styles);
  lblZ->setStyleSheet(styles);
  lblA->setStyleSheet(styles);
  lblB->setStyleSheet(styles);
  lblC->setStyleSheet(styles);
  lblU->setStyleSheet(styles);
  lblV->setStyleSheet(styles);
  lblW->setStyleSheet(styles);
  }


void PositionDockable::setDtgStyles(QString styles) {
  dtgX->label()->setStyleSheet(styles);
  dtgY->label()->setStyleSheet(styles);
  dtgZ->label()->setStyleSheet(styles);
  dtgA->label()->setStyleSheet(styles);
  dtgB->label()->setStyleSheet(styles);
  dtgC->label()->setStyleSheet(styles);
  dtgU->label()->setStyleSheet(styles);
  dtgV->label()->setStyleSheet(styles);
  dtgW->label()->setStyleSheet(styles);
  }


void PositionDockable::setFontSize(int size) {
  QFont f = relX->label()->font();
  QFont nf = QFont(f.family(), size, f.weight(), f.italic());

  absX->label()->setFont(nf);
  absY->label()->setFont(nf);
  absZ->label()->setFont(nf);
  absA->label()->setFont(nf);
  absB->label()->setFont(nf);
  absC->label()->setFont(nf);
  absU->label()->setFont(nf);
  absV->label()->setFont(nf);
  absW->label()->setFont(nf);
  relX->label()->setFont(nf);
  relY->label()->setFont(nf);
  relZ->label()->setFont(nf);
  relA->label()->setFont(nf);
  relB->label()->setFont(nf);
  relC->label()->setFont(nf);
  relU->label()->setFont(nf);
  relV->label()->setFont(nf);
  relW->label()->setFont(nf);

  f = lblX->font();
  nf = QFont(f.family(), size, f.weight(), f.italic());

  lblX->setFont(nf);
  lblY->setFont(nf);
  lblZ->setFont(nf);
  lblA->setFont(nf);
  lblB->setFont(nf);
  lblC->setFont(nf);
  lblU->setFont(nf);
  lblV->setFont(nf);
  lblW->setFont(nf);

  QFontMetrics fm = QFontMetrics(f);
  int w = 3 + fm.horizontalAdvance('W');

  lblX->setMinimumWidth(w);
  lblY->setMinimumWidth(w);
  lblZ->setMinimumWidth(w);
  lblA->setMinimumWidth(w);
  lblB->setMinimumWidth(w);
  lblC->setMinimumWidth(w);
  lblU->setMinimumWidth(w);
  lblV->setMinimumWidth(w);
  lblW->setMinimumWidth(w);

  f = lblX->font();
  nf = QFont(f.family(), size, f.weight(), f.italic());

  dtgX->label()->setFont(nf);
  dtgY->label()->setFont(nf);
  dtgZ->label()->setFont(nf);
  dtgA->label()->setFont(nf);
  dtgB->label()->setFont(nf);
  dtgC->label()->setFont(nf);
  dtgU->label()->setFont(nf);
  dtgV->label()->setFont(nf);
  dtgW->label()->setFont(nf);
  }


void PositionDockable::resizeEvent(QResizeEvent* e) {
  int h = e->size().height();

  if (h == height) return;
  height = h;
  int w = e->size().width();
  QFont f = relX->label()->font();
  int ns = int((((double)h - DockingTitleHeight)/axisMask.activeAxis()) / 4.3);

  std::cout << "\nnew size: " << h << "x" << w
            << "\trow: " << ((h - DockingTitleHeight)/axisMask.activeAxis()) << std::endl;
  std::cout << " font-size: " << f.pointSize()  << "\ttodo: " << ns << std::endl;

  if (ns != f.pointSize()) setFontSize(ns);
  }


void PositionDockable::setXHomed(QVariant homed) {
  ledX->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionDockable::setYHomed(QVariant homed) {
  ledY->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionDockable::setZHomed(QVariant homed) {
  ledZ->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionDockable::setAHomed(QVariant homed) {
  ledA->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionDockable::setBHomed(QVariant homed) {
  ledB->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionDockable::setCHomed(QVariant homed) {
  ledC->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionDockable::setUHomed(QVariant homed) {
  ledU->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionDockable::setVHomed(QVariant homed) {
  ledV->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionDockable::setWHomed(QVariant homed) {
  ledW->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }
