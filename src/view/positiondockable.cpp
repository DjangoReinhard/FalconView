#include "positiondockable.h"
#include <QtUiTools/QUiLoader>
#include <QFontMetrics>
#include <QGridLayout>
#include <valuemanager.h>
#include <iostream>


PositionDockable::PositionDockable(QFile& uiDesc, const AxisMask& am, QWidget* parent)
 : QDockWidget(tr("Position"), parent)
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
  initializeWidget(uiDesc);
  }


PositionDockable::PositionDockable(QFile& uiDesc, const AxisMask& am, QWidget* parent, QString ledOnStyle, QString ledOffStyle)
 : QDockWidget(tr("Position"), parent)
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
  initializeWidget(uiDesc);
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


void PositionDockable::initializeWidget(QFile& uiDesc) {
  QUiLoader loader;
  QWidget*  w = loader.load(&uiDesc, this);

  uiDesc.close();
  setWidget(w);
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
  ValueModel*  m = vm.getModel("showAbsolute");

  if (!m) vm.setValue("showAbsolute", false);
  connect(vm.getModel("showAbsolute"), &ValueModel::valueChanged, this, &PositionDockable::setAbsolute);
  connect(vm.getModel("absX"), &ValueModel::valueChanged, absX, &LabelAdapter::setValue);
  connect(vm.getModel("absY"), &ValueModel::valueChanged, absY, &LabelAdapter::setValue);
  connect(vm.getModel("absZ"), &ValueModel::valueChanged, absZ, &LabelAdapter::setValue);
  connect(vm.getModel("absA"), &ValueModel::valueChanged, absA, &LabelAdapter::setValue);
  connect(vm.getModel("absB"), &ValueModel::valueChanged, absB, &LabelAdapter::setValue);
  connect(vm.getModel("absC"), &ValueModel::valueChanged, absC, &LabelAdapter::setValue);
  connect(vm.getModel("absU"), &ValueModel::valueChanged, absU, &LabelAdapter::setValue);
  connect(vm.getModel("absV"), &ValueModel::valueChanged, absV, &LabelAdapter::setValue);
  connect(vm.getModel("absW"), &ValueModel::valueChanged, absW, &LabelAdapter::setValue);
  connect(vm.getModel("relX"), &ValueModel::valueChanged, relX, &LabelAdapter::setValue);
  connect(vm.getModel("relY"), &ValueModel::valueChanged, relY, &LabelAdapter::setValue);
  connect(vm.getModel("relZ"), &ValueModel::valueChanged, relZ, &LabelAdapter::setValue);
  connect(vm.getModel("relA"), &ValueModel::valueChanged, relA, &LabelAdapter::setValue);
  connect(vm.getModel("relB"), &ValueModel::valueChanged, relB, &LabelAdapter::setValue);
  connect(vm.getModel("relC"), &ValueModel::valueChanged, relC, &LabelAdapter::setValue);
  connect(vm.getModel("relU"), &ValueModel::valueChanged, relU, &LabelAdapter::setValue);
  connect(vm.getModel("relV"), &ValueModel::valueChanged, relV, &LabelAdapter::setValue);
  connect(vm.getModel("relW"), &ValueModel::valueChanged, relW, &LabelAdapter::setValue);
  connect(vm.getModel("dtgX"), &ValueModel::valueChanged, dtgX, &LabelAdapter::setValue);
  connect(vm.getModel("dtgY"), &ValueModel::valueChanged, dtgY, &LabelAdapter::setValue);
  connect(vm.getModel("dtgZ"), &ValueModel::valueChanged, dtgZ, &LabelAdapter::setValue);
  connect(vm.getModel("dtgA"), &ValueModel::valueChanged, dtgA, &LabelAdapter::setValue);
  connect(vm.getModel("dtgB"), &ValueModel::valueChanged, dtgB, &LabelAdapter::setValue);
  connect(vm.getModel("dtgC"), &ValueModel::valueChanged, dtgC, &LabelAdapter::setValue);
  connect(vm.getModel("dtgU"), &ValueModel::valueChanged, dtgU, &LabelAdapter::setValue);
  connect(vm.getModel("dtgV"), &ValueModel::valueChanged, dtgV, &LabelAdapter::setValue);
  connect(vm.getModel("dtgW"), &ValueModel::valueChanged, dtgW, &LabelAdapter::setValue);
  connect(vm.getModel("homedJoint0"), &ValueModel::valueChanged, this, &PositionDockable::setXHomed);
  connect(vm.getModel("homedJoint1"), &ValueModel::valueChanged, this, &PositionDockable::setYHomed);
  connect(vm.getModel("homedJoint2"), &ValueModel::valueChanged, this, &PositionDockable::setZHomed);
  connect(vm.getModel("homedJoint3"), &ValueModel::valueChanged, this, &PositionDockable::setAHomed);
  connect(vm.getModel("homedJoint4"), &ValueModel::valueChanged, this, &PositionDockable::setBHomed);
  connect(vm.getModel("homedJoint5"), &ValueModel::valueChanged, this, &PositionDockable::setCHomed);
  connect(vm.getModel("homedJoint6"), &ValueModel::valueChanged, this, &PositionDockable::setUHomed);
  connect(vm.getModel("homedJoint7"), &ValueModel::valueChanged, this, &PositionDockable::setVHomed);
  connect(vm.getModel("homedJoint8"), &ValueModel::valueChanged, this, &PositionDockable::setWHomed);
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
  QFontMetrics fm(f);
  QRect r = fm.boundingRect("-9.000,000");
  QSize s = relX->label()->size();
  int nw = int((double)r.width() * 1.2);

  std::cout << "pos min-width: " << r.width() << "\tlabel: " << s.width() << std::endl;
  std::cout << "new pos width: " << nw << std::endl;

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
  absX->label()->setMinimumWidth(nw);
  absY->label()->setMinimumWidth(nw);
  absZ->label()->setMinimumWidth(nw);
  absA->label()->setMinimumWidth(nw);
  absB->label()->setMinimumWidth(nw);
  absC->label()->setMinimumWidth(nw);
  absU->label()->setMinimumWidth(nw);
  absV->label()->setMinimumWidth(nw);
  absW->label()->setMinimumWidth(nw);
  relX->label()->setMinimumWidth(nw);
  relY->label()->setMinimumWidth(nw);
  relZ->label()->setMinimumWidth(nw);
  relA->label()->setMinimumWidth(nw);
  relB->label()->setMinimumWidth(nw);
  relC->label()->setMinimumWidth(nw);
  relU->label()->setMinimumWidth(nw);
  relV->label()->setMinimumWidth(nw);
  relW->label()->setMinimumWidth(nw);
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
  f = dtgX->label()->font();
  nf = QFont(f.family(), size, f.weight(), f.italic());
  fm = QFontMetrics(f);
  r = fm.boundingRect("-9.000,000");
  s = dtgX->label()->size();
  nw = int((double)r.width() * 1.2);

  std::cout << "dtg min-width: " << r.width() << "\tlabel: " << s.width() << std::endl;
  std::cout << "new dtg width: " << nw << std::endl;

  dtgX->label()->setFont(nf);
  dtgY->label()->setFont(nf);
  dtgZ->label()->setFont(nf);
  dtgA->label()->setFont(nf);
  dtgB->label()->setFont(nf);
  dtgC->label()->setFont(nf);
  dtgU->label()->setFont(nf);
  dtgV->label()->setFont(nf);
  dtgW->label()->setFont(nf);
  dtgX->label()->setMinimumWidth(nw);
  dtgY->label()->setMinimumWidth(nw);
  dtgZ->label()->setMinimumWidth(nw);
  dtgA->label()->setMinimumWidth(nw);
  dtgB->label()->setMinimumWidth(nw);
  dtgC->label()->setMinimumWidth(nw);
  dtgU->label()->setMinimumWidth(nw);
  dtgV->label()->setMinimumWidth(nw);
  dtgW->label()->setMinimumWidth(nw);
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
