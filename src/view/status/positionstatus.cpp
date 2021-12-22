#include <positionstatus.h>
#include <valuemanager.h>
#include <numlabel.h>
#include <core.h>
#include <QtUiTools/QUiLoader>
#include <QFontMetrics>
#include <QStackedLayout>
#include <QString>
#include <QFont>
#include <QFile>
#include <QDebug>
#include <iostream>
#include <ui_Position.h>
#include <ui_PositionMain.h>


PositionStatus::PositionStatus(const QString&, const AxisMask& am, QWidget* parent)
 : DynCenterWidget(QString(), "PositionStatus", false, parent)
 , frm(new Ui::PositionMain())
 , rel(new Ui::PositionForm())
 , abs(new Ui::PositionForm())
 , dtg(new Ui::PositionForm())
 , sl(new QStackedLayout)
 , frmRel(new QFrame)
 , frmAbs(new QFrame)
 , absolute(true)
 , axisMask(am)
 , ledOn("background: #0F0")
 , ledOff("background: red") {
  setWindowTitle(tr("PositionStatus"));
  }


PositionStatus::PositionStatus(const QString&, const AxisMask& am, QWidget* parent, QString ledOnStyle, QString ledOffStyle)
 : DynCenterWidget(QString(), "PositionStatus", false, parent)
 , frm(new Ui::PositionMain())
 , rel(new Ui::PositionForm())
 , abs(new Ui::PositionForm())
 , dtg(new Ui::PositionForm())
 , sl(new QStackedLayout)
 , frmRel(new QFrame)
 , frmAbs(new QFrame)
 , absolute(true)
 , axisMask(am)
 , ledOn(ledOnStyle)
 , ledOff(ledOffStyle) {
  setFocusPolicy(Qt::FocusPolicy::NoFocus);
  setWindowTitle(tr("PositionStatus"));
  }


PositionStatus::~PositionStatus() {
  }


QWidget* PositionStatus::createContent() {
  frm->setupUi(this);
  rel->setupUi(frmRel);
  abs->setupUi(frmAbs);
  dtg->setupUi(frm->frDtg);
  sl->addWidget(frmAbs);
  sl->addWidget(frmRel);
  frm->frPos->setLayout(sl);
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

  return nullptr;
  }


void PositionStatus::setStyles(Ui::PositionForm* frm, const QString& s, const QFont& f, int w) {
  frm->X->setStyleSheet(s);
  frm->X->setFont(f);
  frm->X->setMinimumWidth(w);
  frm->Y->setStyleSheet(s);
  frm->Y->setFont(f);
  frm->Y->setMinimumWidth(w);
  frm->Z->setStyleSheet(s);
  frm->Z->setFont(f);
  frm->Z->setMinimumWidth(w);
  frm->A->setStyleSheet(s);
  frm->A->setFont(f);
  frm->A->setMinimumWidth(w);
  frm->B->setStyleSheet(s);
  frm->B->setFont(f);
  frm->B->setMinimumWidth(w);
  frm->C->setStyleSheet(s);
  frm->C->setFont(f);
  frm->C->setMinimumWidth(w);
  frm->U->setStyleSheet(s);
  frm->U->setFont(f);
  frm->U->setMinimumWidth(w);
  frm->V->setStyleSheet(s);
  frm->V->setFont(f);
  frm->V->setMinimumWidth(w);
  frm->W->setStyleSheet(s);
  frm->W->setFont(f);
  frm->W->setMinimumWidth(w);
  }


void PositionStatus::updateStyles() {
  ValueManager vm;
  Config       cfg;
  QColor       colBg = vm.getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroAbs)).value<QColor>();
  QColor       colFg = vm.getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroAbs)).value<QColor>();
  QFont        font  = vm.getValue("cfgF"  + cfg.nameOf(Config::GuiElem::DroAbs)).value<QFont>();
  QFontMetrics fm(font);
  QRect        r = fm.boundingRect(widthPat);

  setStyles(abs
          , QString("color: #%1; background: #%2;").arg(colFg.rgb(), 0, 16).arg(colBg.rgba(), 0, 16)
          , font
          , r.width());

  colBg = vm.getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroDtg)).value<QColor>();
  colFg = vm.getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroDtg)).value<QColor>();
  font  = vm.getValue("cfgF"  + cfg.nameOf(Config::GuiElem::DroDtg)).value<QFont>();
  fm    = QFontMetrics(font);
  r     = fm.boundingRect(widthPat);

  setStyles(dtg
          , QString("color: #%1; background: #%2;").arg(colFg.rgb(), 0, 16).arg(colBg.rgba(), 0, 16)
          , font
          , r.width());

  colBg = vm.getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroRel)).value<QColor>();
  colFg = vm.getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroRel)).value<QColor>();
  font  = vm.getValue("cfgF"  + cfg.nameOf(Config::GuiElem::DroRel)).value<QFont>();
  fm    = QFontMetrics(font);
  r     = fm.boundingRect(widthPat);

  setStyles(rel
          , QString("color: #%1; background: #%2;").arg(colFg.rgb(), 0, 16).arg(colBg.rgba(), 0, 16)
          , font
          , r.width());

  colBg = vm.getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>();
  colFg = vm.getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>();
  font  = vm.getValue("cfgF"  + cfg.nameOf(Config::GuiElem::DroTitle)).value<QFont>();
  QString style = QString("color: #%1; background: #%2;").arg(colFg.rgb(), 0, 16).arg(colBg.rgba(), 0, 16);

  frm->lX->setStyleSheet(style);
  frm->lX->setFont(font);
  frm->lY->setStyleSheet(style);
  frm->lY->setFont(font);
  frm->lZ->setStyleSheet(style);
  frm->lZ->setFont(font);
  frm->lA->setStyleSheet(style);
  frm->lA->setFont(font);
  frm->lB->setStyleSheet(style);
  frm->lB->setFont(font);
  frm->lC->setStyleSheet(style);
  frm->lC->setFont(font);
  frm->lU->setStyleSheet(style);
  frm->lU->setFont(font);
  frm->lV->setStyleSheet(style);
  frm->lV->setFont(font);
  frm->lW->setStyleSheet(style);
  frm->lW->setFont(font);
  setActive();
  }


void PositionStatus::connectPos(Ui::PositionForm* frm, const QString& key, Config::GuiElem e) {
  ValueManager vm;
  Config       cfg;

  connect(vm.getModel(key + "X", 0), &ValueModel::valueChanged, frm->X, &NumLabel::setValue);
  connect(vm.getModel(key + "Y", 0), &ValueModel::valueChanged, frm->Y, &NumLabel::setValue);
  connect(vm.getModel(key + "Z", 0), &ValueModel::valueChanged, frm->Z, &NumLabel::setValue);
  connect(vm.getModel(key + "A", 0), &ValueModel::valueChanged, frm->A, &NumLabel::setValue);
  connect(vm.getModel(key + "B", 0), &ValueModel::valueChanged, frm->B, &NumLabel::setValue);
  connect(vm.getModel(key + "C", 0), &ValueModel::valueChanged, frm->C, &NumLabel::setValue);
  connect(vm.getModel(key + "U", 0), &ValueModel::valueChanged, frm->U, &NumLabel::setValue);
  connect(vm.getModel(key + "V", 0), &ValueModel::valueChanged, frm->V, &NumLabel::setValue);
  connect(vm.getModel(key + "W", 0), &ValueModel::valueChanged, frm->W, &NumLabel::setValue);

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(e)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->X
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(e)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(e)).value<QColor>().rgba(), 0, 16);
                 frm->X->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(e)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->X
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(e)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(e)).value<QColor>().rgba(), 0, 16);
                 frm->X->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(e)), frm->X->font())
        , &ValueModel::valueChanged
        , frm->X
        , [=](){ frm->X->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(e)).value<QFont>()); });

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(e)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->Y
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(e)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(e)).value<QColor>().rgba(), 0, 16);
                 frm->Y->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(e)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->Y
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(e)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(e)).value<QColor>().rgba(), 0, 16);
                 frm->Y->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(e)), frm->Y->font())
        , &ValueModel::valueChanged
        , frm->Y
        , [=](){ frm->Y->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(e)).value<QFont>()); });

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(e)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->Z
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(e)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(e)).value<QColor>().rgba(), 0, 16);
                 frm->Z->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(e)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->Z
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(e)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(e)).value<QColor>().rgba(), 0, 16);
                 frm->Z->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(e)), frm->Z->font())
        , &ValueModel::valueChanged
        , frm->Z
        , [=](){ frm->Z->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(e)).value<QFont>()); });

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(e)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->A
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(e)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(e)).value<QColor>().rgba(), 0, 16);
                 frm->A->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(e)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->A
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(e)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(e)).value<QColor>().rgba(), 0, 16);
                 frm->A->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(e)), frm->A->font())
        , &ValueModel::valueChanged
        , frm->A
        , [=](){ frm->A->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(e)).value<QFont>()); });

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(e)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->B
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(e)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(e)).value<QColor>().rgba(), 0, 16);
                 frm->B->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(e)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->B
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(e)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(e)).value<QColor>().rgba(), 0, 16);
                 frm->B->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(e)), frm->B->font())
        , &ValueModel::valueChanged
        , frm->B
        , [=](){ frm->B->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(e)).value<QFont>()); });

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(e)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->C
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(e)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(e)).value<QColor>().rgba(), 0, 16);
                 frm->C->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(e)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->C
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(e)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(e)).value<QColor>().rgba(), 0, 16);
                 frm->C->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(e)), frm->C->font())
        , &ValueModel::valueChanged
        , frm->C
        , [=](){ frm->C->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(e)).value<QFont>()); });

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(e)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->U
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(e)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(e)).value<QColor>().rgba(), 0, 16);
                 frm->U->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(e)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->U
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(e)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(e)).value<QColor>().rgba(), 0, 16);
                 frm->U->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(e)), frm->U->font())
        , &ValueModel::valueChanged
        , frm->U
        , [=](){ frm->U->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(e)).value<QFont>()); });

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(e)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->V
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(e)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(e)).value<QColor>().rgba(), 0, 16);
                 frm->V->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(e)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->V
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(e)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(e)).value<QColor>().rgba(), 0, 16);
                 frm->V->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(e)), frm->V->font())
        , &ValueModel::valueChanged
        , frm->V
        , [=](){ frm->V->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(e)).value<QFont>()); });

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(e)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->W
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(e)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(e)).value<QColor>().rgba(), 0, 16);
                 frm->W->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(e)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->W
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(e)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(e)).value<QColor>().rgba(), 0, 16);
                 frm->W->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(e)), frm->W->font())
        , &ValueModel::valueChanged
        , frm->W
        , [=](){ frm->W->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(e)).value<QFont>()); });
  }

void PositionStatus::connectSignals() {
  ValueManager vm;
  Config       cfg;

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
      }
  connectPos(abs, "abs", Config::GuiElem::DroAbs);
  connectPos(rel, "rel", Config::GuiElem::DroRel);
  connectPos(dtg, "dtg", Config::GuiElem::DroDtg);

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->lX
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 frm->lX->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , frm->lX
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 frm->lX->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)), frm->lX->font())
        , &ValueModel::valueChanged
        , frm->lX
        , [=](){ frm->lX->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QFont>()); });

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->lY
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 frm->lY->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , frm->lY
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 frm->lY->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)), frm->lY->font())
        , &ValueModel::valueChanged
        , frm->lY
        , [=](){ frm->lY->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QFont>()); });

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->lZ
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 frm->lZ->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , frm->lZ
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 frm->lZ->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)), frm->lZ->font())
        , &ValueModel::valueChanged
        , frm->lZ
        , [=](){ frm->lZ->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QFont>()); });

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->lA
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 frm->lA->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , frm->lA
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 frm->lA->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)), frm->lA->font())
        , &ValueModel::valueChanged
        , frm->lA
        , [=](){ frm->lA->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QFont>()); });

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->lB
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 frm->lB->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , frm->lB
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 frm->lB->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)), frm->lB->font())
        , &ValueModel::valueChanged
        , frm->lB
        , [=](){ frm->lB->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QFont>()); });

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->lC
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 frm->lC->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , frm->lC
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 frm->lC->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)), frm->lC->font())
        , &ValueModel::valueChanged
        , frm->lC
        , [=](){ frm->lC->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QFont>()); });

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->lU
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 frm->lU->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , frm->lU
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 frm->lU->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)), frm->lU->font())
        , &ValueModel::valueChanged
        , frm->lU
        , [=](){ frm->lU->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QFont>()); });

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->lV
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 frm->lV->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , frm->lV
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 frm->lV->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)), frm->lV->font())
        , &ValueModel::valueChanged
        , frm->lV
        , [=](){ frm->lV->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QFont>()); });

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , frm->lW
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 frm->lW->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , frm->lW
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QColor>().rgba(), 0, 16);
                 frm->lW->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)), frm->lW->font())
        , &ValueModel::valueChanged
        , frm->lW
        , [=](){ frm->lW->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::DroTitle)).value<QFont>()); });
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
  if (absolute) sl->setCurrentWidget(frmAbs);
  else          sl->setCurrentWidget(frmRel);
  }


void PositionStatus::setActive() {
  if (!axisMask.hasXAxis()) {
     frm->ledX->hide();
     frm->lX->hide();
     rel->X->hide();
     abs->X->hide();
     dtg->X->hide();
     }
  if (!axisMask.hasYAxis()) {
     frm->ledY->hide();
     frm->lY->hide();
     rel->Y->hide();
     abs->Y->hide();
     dtg->Y->hide();
     }
  if (!axisMask.hasZAxis()) {
     frm->ledZ->hide();
     frm->lZ->hide();
     rel->Z->hide();
     abs->Z->hide();
     dtg->Z->hide();
     }
  if (!axisMask.hasAAxis()) {
     frm->ledA->hide();
     frm->lA->hide();
     rel->A->hide();
     abs->A->hide();
     dtg->A->hide();
     }
  if (!axisMask.hasBAxis()) {
     frm->ledB->hide();
     frm->lB->hide();
     rel->B->hide();
     abs->B->hide();
     dtg->B->hide();
     }
  if (!axisMask.hasCAxis()) {
     frm->ledC->hide();
     frm->lC->hide();
     rel->C->hide();
     abs->C->hide();
     dtg->C->hide();
     }
  if (!axisMask.hasUAxis()) {
     frm->ledU->hide();
     frm->lU->hide();
     rel->U->hide();
     abs->U->hide();
     dtg->U->hide();
     }
  if (!axisMask.hasVAxis()) {
     frm->ledV->hide();
     frm->lV->hide();
     rel->V->hide();
     abs->V->hide();
     dtg->V->hide();
     }
  if (!axisMask.hasWAxis()) {
     frm->ledW->hide();
     frm->lW->hide();
     rel->W->hide();
     abs->W->hide();
     dtg->W->hide();
     }
  }


void PositionStatus::setXHomed(QVariant homed) {
  frm->ledX->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionStatus::setYHomed(QVariant homed) {
  frm->ledY->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionStatus::setZHomed(QVariant homed) {
  frm->ledZ->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionStatus::setAHomed(QVariant homed) {
  frm->ledA->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionStatus::setBHomed(QVariant homed) {
  frm->ledB->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionStatus::setCHomed(QVariant homed) {
  frm->ledC->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionStatus::setUHomed(QVariant homed) {
  frm->ledU->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionStatus::setVHomed(QVariant homed) {
  frm->ledV->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


void PositionStatus::setWHomed(QVariant homed) {
  frm->ledW->setStyleSheet(homed.toBool() ? ledOn : ledOff);
  }


const char* PositionStatus::a[] = {"X", "Y", "Z", "A", "B", "C", "U", "V", "W"};
const char* PositionStatus::widthPat = "-10.333,333";
