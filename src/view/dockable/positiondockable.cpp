#include <positiondockable.h>
#include <valuemanager.h>
#include <configacc.h>
#include <QtUiTools/QUiLoader>
#include <QFontMetrics>
#include <QGridLayout>
#include <QString>
#include <QFont>
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
 , droRel(nullptr)
 , droAbs(nullptr)
 , droDtg(nullptr)
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
 , droRel(nullptr)
 , droAbs(nullptr)
 , droDtg(nullptr)
 , height(0)
 , absolute(true)
 , axisMask(am)
 , ledOn(ledOnStyle)
 , ledOff(ledOffStyle) {
  initializeWidget(widget());
  }


PositionDockable::~PositionDockable() {
    /*
  for (int i=0; i < 9; ++i) {
      delete droRel[i];
      delete droDtg[i];
      delete droAbs[i]->label();
      delete droAbs[i];
      }
  delete droRel;
  delete droAbs;
  delete droDtg;
  */
  }


void PositionDockable::initializeWidget(QWidget* /* w */) {
  droRel = new LabelAdapter*[9];
  droAbs = new LabelAdapter*[9];
  droDtg = new LabelAdapter*[9];
  QGridLayout* gl = findChild<QGridLayout*>("gridLayout");

  for (int i=0; i < 9; ++i) {
      droRel[i] = new LabelAdapter(findChild<QLabel*>(QString("pos") + a[i]));
      droDtg[i] = new LabelAdapter(findChild<QLabel*>(QString("dtg") + a[i]));
      droAbs[i] = new LabelAdapter(new QLabel("0.000", this));

      droAbs[i]->label()->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
      droAbs[i]->label()->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
      gl->addWidget(droAbs[i]->label(), i, 2);
      }
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
  updateStyles();
  }


void PositionDockable::updateStyles() {
  ValueManager vm;
  Config       cfg;
  QColor       colBg = vm.getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroAbs)).value<QColor>();
  QColor       colFg = vm.getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroAbs)).value<QColor>();
  QFont        font  = vm.getValue("cfgF"  + cfg.nameOf(Config::GuiElem::DroAbs)).value<QFont>();

  for (int i=0; i < 9; ++i) {
      droAbs[i]->label()->setStyleSheet(QString("color: #%1; background: #%2;").arg(colFg.rgb(), 0, 16).arg(colBg.rgba(), 0, 16));
      droAbs[i]->label()->setFont(font);
      }
  colBg = vm.getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroDtg)).value<QColor>();
  colFg = vm.getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroDtg)).value<QColor>();
  font  = vm.getValue("cfgF"  + cfg.nameOf(Config::GuiElem::DroDtg)).value<QFont>();

  for (int i=0; i < 9; ++i) {
      droDtg[i]->label()->setStyleSheet(QString("color: #%1; background: #%2;").arg(colFg.rgb(), 0, 16).arg(colBg.rgba(), 0, 16));
      droDtg[i]->label()->setFont(font);
      }
  colBg = vm.getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroRel)).value<QColor>();
  colFg = vm.getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroRel)).value<QColor>();
  font  = vm.getValue("cfgF"  + cfg.nameOf(Config::GuiElem::DroRel)).value<QFont>();

  for (int i=0; i < 9; ++i) {
      droRel[i]->label()->setStyleSheet(QString("color: #%1; background: #%2;").arg(colFg.rgb(), 0, 16).arg(colBg.rgba(), 0, 16));
      droRel[i]->label()->setFont(font);
      }
  colBg = vm.getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>();
  colFg = vm.getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>();
  font  = vm.getValue("cfgF"  + cfg.nameOf(Config::GuiElem::DroTitle)).value<QFont>();
  QString style = QString("color: #%1; background: #%2;").arg(colFg.rgb(), 0, 16).arg(colBg.rgba(), 0, 16);

  lblX->setStyleSheet(style);
  lblX->setFont(font);
  lblY->setStyleSheet(style);
  lblY->setFont(font);
  lblZ->setStyleSheet(style);
  lblZ->setFont(font);
  lblA->setStyleSheet(style);
  lblA->setFont(font);
  lblB->setStyleSheet(style);
  lblB->setFont(font);
  lblC->setStyleSheet(style);
  lblC->setFont(font);
  lblU->setStyleSheet(style);
  lblU->setFont(font);
  lblV->setStyleSheet(style);
  lblV->setFont(font);
  lblW->setStyleSheet(style);
  lblW->setFont(font);
  }

void PositionDockable::connectSignals() {
  ValueManager vm;
  Config cfg;

  connect(vm.getModel("showAbsolute", false), &ValueModel::valueChanged, this, &PositionDockable::setAbsolute);
//  connect(vm.getModel("axisMask", 0x0),       &ValueModel::valueChanged, this, &PositionDockable::setAxisMask);
  for (int i=0; i < 9; ++i) {
      QString modelKey = QString("homedJoint%1").arg(axisMask.joint4Axis(i));

      switch (i) {
        case 0: connect(vm.getModel(modelKey, false),  &ValueModel::valueChanged
                      , this, &PositionDockable::setXHomed); break;
        case 1: connect(vm.getModel(modelKey, false),  &ValueModel::valueChanged
                      , this, &PositionDockable::setYHomed); break;
        case 2: connect(vm.getModel(modelKey, false),  &ValueModel::valueChanged
                      , this, &PositionDockable::setZHomed); break;
        case 3: connect(vm.getModel(modelKey, false),  &ValueModel::valueChanged
                      , this, &PositionDockable::setAHomed); break;
        case 4: connect(vm.getModel(modelKey, false),  &ValueModel::valueChanged
                      , this, &PositionDockable::setBHomed); break;
        case 5: connect(vm.getModel(modelKey, false),  &ValueModel::valueChanged
                      , this, &PositionDockable::setCHomed); break;
        case 6: connect(vm.getModel(modelKey, false),  &ValueModel::valueChanged
                      , this, &PositionDockable::setUHomed); break;
        case 7: connect(vm.getModel(modelKey, false),  &ValueModel::valueChanged
                      , this, &PositionDockable::setVHomed); break;
        case 8: connect(vm.getModel(modelKey, false),  &ValueModel::valueChanged
                      , this, &PositionDockable::setWHomed); break;
        }
      connect(vm.getModel(QString("abs") + a[i], 0), &ValueModel::valueChanged, droAbs[i], &LabelAdapter::setValue);
      connect(vm.getModel(QString("rel") + a[i], 0), &ValueModel::valueChanged, droRel[i], &LabelAdapter::setValue);
      connect(vm.getModel(QString("dtg") + a[i], 0), &ValueModel::valueChanged, droDtg[i], &LabelAdapter::setValue);
      connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::DroAbs)), QColor(Qt::white))
            , &ValueModel::valueChanged
            , droAbs[i]->label()
            , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                          .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroAbs)).value<QColor>().rgb(), 0, 16)
                                          .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroAbs)).value<QColor>().rgba(), 0, 16);
                     droAbs[i]->label()->setStyleSheet(arg);
                     });
      connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::DroRel)), QColor(Qt::white))
            , &ValueModel::valueChanged
            , droRel[i]->label()
            , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                          .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroRel)).value<QColor>().rgb(), 0, 16)
                                          .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroRel)).value<QColor>().rgba(), 0, 16);
                     droRel[i]->label()->setStyleSheet(arg);
                     });
      connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::DroDtg)), QColor(Qt::white))
            , &ValueModel::valueChanged
            , droDtg[i]->label()
            , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                          .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroDtg)).value<QColor>().rgb(), 0, 16)
                                          .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroDtg)).value<QColor>().rgba(), 0, 16);
                     droDtg[i]->label()->setStyleSheet(arg);
                     });
      connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::DroAbs)), QColor(Qt::white))
            , &ValueModel::valueChanged
            , droAbs[i]->label()
            , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                          .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroAbs)).value<QColor>().rgb(), 0, 16)
                                          .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroAbs)).value<QColor>().rgba(), 0, 16);
                     droAbs[i]->label()->setStyleSheet(arg);
                     });
      connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::DroRel)), QColor(Qt::white))
            , &ValueModel::valueChanged
            , droRel[i]->label()
            , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                          .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroRel)).value<QColor>().rgb(), 0, 16)
                                          .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroRel)).value<QColor>().rgba(), 0, 16);
                     droRel[i]->label()->setStyleSheet(arg);
                     });
      connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::DroDtg)), QColor(Qt::white))
            , &ValueModel::valueChanged
            , droDtg[i]->label()
            , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                          .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroDtg)).value<QColor>().rgb(), 0, 16)
                                          .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroDtg)).value<QColor>().rgba(), 0, 16);
                     droDtg[i]->label()->setStyleSheet(arg);
                     });
      connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::DroAbs)), droAbs[i]->label()->font())
            , &ValueModel::valueChanged
            , droAbs[i]->label()
            , [=](){ droAbs[i]->label()->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::DroAbs)).value<QFont>());
                     });
      connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::DroRel)), droRel[i]->label()->font())
            , &ValueModel::valueChanged
            , droRel[i]->label()
            , [=](){ droRel[i]->label()->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::DroRel)).value<QFont>());
                     });
      connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::DroDtg)), droDtg[i]->label()->font())
            , &ValueModel::valueChanged
            , droDtg[i]->label()
            , [=](){ droDtg[i]->label()->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::DroDtg)).value<QFont>());
                     });
      }
  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , lblX
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 lblX->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , lblX
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 lblX->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)), lblX->font())
        , &ValueModel::valueChanged
        , lblX
        , [=](){ lblX->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QFont>());
                 });
  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , lblY
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 lblY->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , lblY
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 lblY->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)), lblX->font())
        , &ValueModel::valueChanged
        , lblY
        , [=](){ lblY->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QFont>());
                 });
  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , lblZ
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 lblZ->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , lblZ
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 lblZ->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)), lblX->font())
        , &ValueModel::valueChanged
        , lblZ
        , [=](){ lblZ->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QFont>());
                 });
  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , lblA
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 lblA->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , lblA
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 lblA->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)), lblX->font())
        , &ValueModel::valueChanged
        , lblA
        , [=](){ lblA->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QFont>());
                 });
  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , lblB
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 lblB->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , lblB
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 lblB->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)), lblX->font())
        , &ValueModel::valueChanged
        , lblB
        , [=](){ lblB->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QFont>());
                 });
  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , lblC
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 lblC->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , lblC
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 lblC->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)), lblX->font())
        , &ValueModel::valueChanged
        , lblC
        , [=](){ lblC->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QFont>());
                 });
  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , lblU
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 lblU->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , lblU
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 lblU->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)), lblX->font())
        , &ValueModel::valueChanged
        , lblU
        , [=](){ lblU->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QFont>());
                 });
  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , lblV
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 lblV->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , lblV
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 lblV->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)), lblX->font())
        , &ValueModel::valueChanged
        , lblV
        , [=](){ lblV->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QFont>());
                 });
  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , lblW
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 lblW->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , lblW
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 lblW->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)), lblX->font())
        , &ValueModel::valueChanged
        , lblW
        , [=](){ lblW->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QFont>());
                 });
  }


//void PositionDockable::setAxisMask(QVariant am) {
//  if (axisMask.mask() != am.toInt())  {
//     axisMask = am.toInt();
//     updatePos();
//     }
//  }


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
     for (int i=0; i < 9; ++i) {
         droAbs[i]->label()->show();
         droRel[i]->label()->hide();
         }
     }
  else {
     for (int i=0; i < 9; ++i) {
         droRel[i]->label()->show();
         droAbs[i]->label()->hide();
         }
     }
  setActive();
  }


void PositionDockable::setActive() {
  if (!axisMask.hasXAxis()) {
     ledX->hide();
     lblX->hide();
     droRel[0]->label()->hide();
     droAbs[0]->label()->hide();
     droDtg[0]->label()->hide();
     }
  if (!axisMask.hasYAxis()) {
     ledY->hide();
     lblY->hide();
     droRel[1]->label()->hide();
     droAbs[1]->label()->hide();
     droDtg[1]->label()->hide();
     }
  if (!axisMask.hasZAxis()) {
     ledZ->hide();
     lblZ->hide();
     droRel[2]->label()->hide();
     droAbs[2]->label()->hide();
     droDtg[2]->label()->hide();
     }
  if (!axisMask.hasAAxis()) {
     ledA->hide();
     lblA->hide();
     droRel[3]->label()->hide();
     droAbs[3]->label()->hide();
     droDtg[3]->label()->hide();
     }
  if (!axisMask.hasBAxis()) {
     ledB->hide();
     lblB->hide();
     droRel[4]->label()->hide();
     droAbs[4]->label()->hide();
     droDtg[4]->label()->hide();
     }
  if (!axisMask.hasCAxis()) {
     ledC->hide();
     lblC->hide();
     droRel[5]->label()->hide();
     droAbs[5]->label()->hide();
     droDtg[5]->label()->hide();
     }
  if (!axisMask.hasUAxis()) {
     ledU->hide();
     lblU->hide();
     droRel[6]->label()->hide();
     droAbs[6]->label()->hide();
     droDtg[6]->label()->hide();
     }
  if (!axisMask.hasVAxis()) {
     ledV->hide();
     lblV->hide();
     droRel[7]->label()->hide();
     droAbs[7]->label()->hide();
     droDtg[7]->label()->hide();
     }
  if (!axisMask.hasWAxis()) {
     ledW->hide();
     lblW->hide();
     droRel[8]->label()->hide();
     droAbs[8]->label()->hide();
     droDtg[8]->label()->hide();
     }
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


const char* PositionDockable::a[] = {"X", "Y", "Z", "A", "B", "C", "U", "V", "W"};
