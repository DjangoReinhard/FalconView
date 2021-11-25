#include <positionstatus.h>
#include <valuemanager.h>
#include <configacc.h>
#include <QtUiTools/QUiLoader>
#include <QFontMetrics>
#include <QGridLayout>
#include <QString>
#include <QFont>
#include <QFile>
#include <QDebug>
#include <iostream>


PositionStatus::PositionStatus(const QString& fileName, const AxisMask& am, QWidget* parent)
 : DynCenterWidget(fileName, tr("Position"), false, parent)
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
  }


PositionStatus::PositionStatus(const QString& fileName, const AxisMask& am, QWidget* parent, QString ledOnStyle, QString ledOffStyle)
 : DynCenterWidget(fileName, tr("Position"), false, parent)
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
  setFocusPolicy(Qt::FocusPolicy::NoFocus);
  }


PositionStatus::~PositionStatus() {
  }


QWidget* PositionStatus::createContent() {
  QWidget*     rv = DynCenterWidget::createContent();
  QGridLayout* gl = rv->findChild<QGridLayout*>("gridLayout");

  droRel = new LabelAdapter*[9];
  droAbs = new LabelAdapter*[9];
  droDtg = new LabelAdapter*[9];
  for (int i=0; i < 9; ++i) {
      droRel[i] = new LabelAdapter(rv->findChild<QLabel*>(QString("pos") + a[i]));
      droDtg[i] = new LabelAdapter(rv->findChild<QLabel*>(QString("dtg") + a[i]));
      droAbs[i] = new LabelAdapter(new QLabel("0.000", this));

      droAbs[i]->label()->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
      droAbs[i]->label()->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
      gl->addWidget(droAbs[i]->label(), i, 2);
      }
  lblX = rv->findChild<QLabel*>("lblX");
  lblY = rv->findChild<QLabel*>("lblY");
  lblZ = rv->findChild<QLabel*>("lblZ");
  lblA = rv->findChild<QLabel*>("lblA");
  lblB = rv->findChild<QLabel*>("lblB");
  lblC = rv->findChild<QLabel*>("lblC");
  lblU = rv->findChild<QLabel*>("lblU");
  lblV = rv->findChild<QLabel*>("lblV");
  lblW = rv->findChild<QLabel*>("lblW");

  ledX = rv->findChild<QLabel*>("ledX");
  ledY = rv->findChild<QLabel*>("ledY");
  ledZ = rv->findChild<QLabel*>("ledZ");
  ledA = rv->findChild<QLabel*>("ledA");
  ledB = rv->findChild<QLabel*>("ledB");
  ledC = rv->findChild<QLabel*>("ledC");
  ledU = rv->findChild<QLabel*>("ledU");
  ledV = rv->findChild<QLabel*>("ledV");
  ledW = rv->findChild<QLabel*>("ledW");

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

  return rv;
  }


void PositionStatus::updateStyles() {
  ValueManager vm;
  Config       cfg;

  QColor       colBg = vm.getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroAbs)).value<QColor>();
  QColor       colFg = vm.getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroAbs)).value<QColor>();
  QFont        font  = vm.getValue("cfgF"  + cfg.nameOf(Config::GuiElem::DroAbs)).value<QFont>();
  QFontMetrics fm(font);
  QRect        r = fm.boundingRect(widthPat);

  for (int i=0; i < 9; ++i) {
      droAbs[i]->label()->setStyleSheet(QString("color: #%1; background: #%2;").arg(colFg.rgb(), 0, 16).arg(colBg.rgba(), 0, 16));
      droAbs[i]->label()->setFont(font);
      droAbs[i]->label()->setMinimumWidth(r.width());
      }
  colBg = vm.getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroDtg)).value<QColor>();
  colFg = vm.getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroDtg)).value<QColor>();
  font  = vm.getValue("cfgF"  + cfg.nameOf(Config::GuiElem::DroDtg)).value<QFont>();
  fm    = QFontMetrics(font);
  r     = fm.boundingRect(widthPat);

  for (int i=0; i < 9; ++i) {
      droDtg[i]->label()->setStyleSheet(QString("color: #%1; background: #%2;").arg(colFg.rgb(), 0, 16).arg(colBg.rgba(), 0, 16));
      droDtg[i]->label()->setFont(font);
      droDtg[i]->label()->setMinimumWidth(r.width());
      }
  colBg = vm.getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroRel)).value<QColor>();
  colFg = vm.getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroRel)).value<QColor>();
  font  = vm.getValue("cfgF"  + cfg.nameOf(Config::GuiElem::DroRel)).value<QFont>();
  fm    = QFontMetrics(font);
  r     = fm.boundingRect(widthPat);

  for (int i=0; i < 9; ++i) {
      droRel[i]->label()->setStyleSheet(QString("color: #%1; background: #%2;").arg(colFg.rgb(), 0, 16).arg(colBg.rgba(), 0, 16));
      droRel[i]->label()->setFont(font);
      droRel[i]->label()->setMinimumWidth(r.width());
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

void PositionStatus::connectSignals() {
  ValueManager vm;
  Config cfg;

  connect(vm.getModel("showAbsolute", false), &ValueModel::valueChanged, this, &PositionStatus::setAbsolute);
  for (int i=0; i < 9; ++i) {
      QString modelKey = QString("homedJoint%1").arg(axisMask.joint4Axis(i));

      switch (i) {
        case 0: connect(vm.getModel(modelKey, false),  &ValueModel::valueChanged
                      , this, &PositionStatus::setXHomed); break;
        case 1: connect(vm.getModel(modelKey, false),  &ValueModel::valueChanged
                      , this, &PositionStatus::setYHomed); break;
        case 2: connect(vm.getModel(modelKey, false),  &ValueModel::valueChanged
                      , this, &PositionStatus::setZHomed); break;
        case 3: connect(vm.getModel(modelKey, false),  &ValueModel::valueChanged
                      , this, &PositionStatus::setAHomed); break;
        case 4: connect(vm.getModel(modelKey, false),  &ValueModel::valueChanged
                      , this, &PositionStatus::setBHomed); break;
        case 5: connect(vm.getModel(modelKey, false),  &ValueModel::valueChanged
                      , this, &PositionStatus::setCHomed); break;
        case 6: connect(vm.getModel(modelKey, false),  &ValueModel::valueChanged
                      , this, &PositionStatus::setUHomed); break;
        case 7: connect(vm.getModel(modelKey, false),  &ValueModel::valueChanged
                      , this, &PositionStatus::setVHomed); break;
        case 8: connect(vm.getModel(modelKey, false),  &ValueModel::valueChanged
                      , this, &PositionStatus::setWHomed); break;
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


void PositionStatus::setRelative() {
  setAbsolute(QVariant(false));
  }


void PositionStatus::setAbsolute(QVariant arg) {
  bool abs = arg.toBool();

  qDebug() << "PosDock::setAbsolute(" << (abs ? "yes" : "no") << ")";
  if (abs != absolute)  {
     absolute = abs;
     updatePos();
     }
  }


void PositionStatus::updatePos() {
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


void PositionStatus::setActive() {
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


void PositionStatus::setXHomed(QVariant homed) {
  ledX->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionStatus::setYHomed(QVariant homed) {
  ledY->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionStatus::setZHomed(QVariant homed) {
  ledZ->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionStatus::setAHomed(QVariant homed) {
  ledA->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionStatus::setBHomed(QVariant homed) {
  ledB->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionStatus::setCHomed(QVariant homed) {
  ledC->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionStatus::setUHomed(QVariant homed) {
  ledU->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionStatus::setVHomed(QVariant homed) {
  ledV->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionStatus::setWHomed(QVariant homed) {
  ledW->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


const char* PositionStatus::a[] = {"X", "Y", "Z", "A", "B", "C", "U", "V", "W"};
const char* PositionStatus::widthPat = "-10.333,333";
