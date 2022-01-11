#include "speedstatus.h"
#include <valuemanager.h>
#include <configacc.h>
#include <guicore.h>
#include <numlabel.h>
#include <QFile>
#include <QSlider>
#include <QLabel>
#include <QDebug>


SpeedStatus::SpeedStatus(QWidget* parent)
 : AbstractCenterWidget(QString(), parent)
 , isVertical(false) {
  setObjectName("SpeedStatus");
  setWindowTitle(tr("SpeedStatus"));
  setFocusPolicy(Qt::FocusPolicy::NoFocus);
  }


SpeedStatus::~SpeedStatus() {
  }


QWidget* SpeedStatus::createContent() {
  QWidget* rv = AbstractCenterWidget::createContent();

  cmdFastFeed    = rv->findChild<QLabel*>("cmdFastFeed");
  cmdFeed        = rv->findChild<QLabel*>("cmdFeed");
  cmdSpeed       = rv->findChild<QLabel*>("cmdSpeed");
  curFastFeed    = rv->findChild<QLabel*>("curFastFeed");
  curFeed        = rv->findChild<QLabel*>("curFeed");
  curSpeed       = rv->findChild<QLabel*>("curSpeed");
  fastfeedFactor = rv->findChild<QLabel*>("fastfeedFactor");
  feedFactor     = rv->findChild<QLabel*>("feedFactor");
  label          = rv->findChild<QLabel*>("label");
  label_3        = rv->findChild<QLabel*>("label_3");
  label_9        = rv->findChild<QLabel*>("label_9");
  speedFactor    = rv->findChild<QLabel*>("speedFactor");
  slFastFeed     = rv->findChild<QSlider*>("slFastFeed");
  slFeed         = rv->findChild<QSlider*>("slFeed");
  slSpeed        = rv->findChild<QSlider*>("slSpeed");
  slFeed->setTickInterval(10);
  slFeed->setTickPosition(QSlider::TicksRight);
  slFastFeed->setTickInterval(7);
  slFastFeed->setTickPosition(QSlider::TicksRight);
  slSpeed->setTickInterval(10);
  slSpeed->setTickPosition(QSlider::TicksRight);

  return rv;
  }


void SpeedStatus::connectSignals() {
  connect(vm->getModel("feedrate", 100),      &ValueModel::valueChanged, this, &SpeedStatus::feedRateChanged);
  connect(vm->getModel("rapidrate", 100),     &ValueModel::valueChanged, this, &SpeedStatus::fastFeedRateChanged);
  connect(vm->getModel("spindle0Scale", 100), &ValueModel::valueChanged, this, &SpeedStatus::speedRateChanged);

  connect(vm->getModel("cmdVelocity", 0),   &ValueModel::valueChanged, cmdFeed
       , [=](const QVariant& v){ cmdFeed->setText(core->locale().toString(v.toDouble(), 'f', 0)); });
  connect(vm->getModel("maxVelocity", 0),   &ValueModel::valueChanged, cmdFastFeed
       , [=](const QVariant& v){ cmdFastFeed->setText(core->locale().toString(v.toDouble(), 'f', 0)); });
  connect(vm->getModel("spindle0Speed", 0), &ValueModel::valueChanged, cmdSpeed
       , [=](const QVariant& v){ cmdSpeed->setText(core->locale().toString(v.toDouble(), 'f', 0)); });
  connect(vm->getModel("curVelocity", 0),   &ValueModel::valueChanged, curFeed
       , [=](const QVariant& v){ curFeed->setText(core->locale().toString(v.toDouble(), 'f', 0)); });
  connect(vm->getModel("curRapid", 0),      &ValueModel::valueChanged, curFastFeed
       , [=](const QVariant& v){ curFastFeed->setText(core->locale().toString(v.toDouble(), 'f', 0)); });
  connect(vm->getModel("curSpeed", 0),      &ValueModel::valueChanged, curSpeed
       , [=](const QVariant& v){ curSpeed->setText(core->locale().toString(v.toDouble(), 'f', 0)); });
  connect(slFeed,     &QSlider::valueChanged, this, &SpeedStatus::feedChanged);
  connect(slFastFeed, &QSlider::valueChanged, this, &SpeedStatus::fastFeedChanged);
  connect(slSpeed,    &QSlider::valueChanged, this, &SpeedStatus::speedChanged);

  connect(vm->getModel(QString("cfgBg" + cfg->nameOf(Config::GuiElem::Feed)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , curFeed
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(vm->getValue("cfgFg" + cfg->nameOf(Config::GuiElem::Feed)).value<QColor>().rgb(), 0, 16)
                                      .arg(vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::Feed)).value<QColor>().rgba(), 0, 16);
                 curFeed->setStyleSheet(arg);
                 });
  connect(vm->getModel(QString("cfgFg" + cfg->nameOf(Config::GuiElem::Feed)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , curFeed
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(vm->getValue("cfgFg" + cfg->nameOf(Config::GuiElem::Feed)).value<QColor>().rgb(), 0, 16)
                                      .arg(vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::Feed)).value<QColor>().rgba(), 0, 16);
                 curFeed->setStyleSheet(arg);
                 });
  connect(vm->getModel(QString("cfgF" + cfg->nameOf(Config::GuiElem::Feed)), curFeed->font())
        , &ValueModel::valueChanged
        , curFeed
        , [=](){ curFeed->setFont(vm->getValue("cfgF" + cfg->nameOf(Config::GuiElem::Feed)).value<QFont>());
                 });

  connect(vm->getModel(QString("cfgBg" + cfg->nameOf(Config::GuiElem::Feed)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , curFastFeed
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(vm->getValue("cfgFg" + cfg->nameOf(Config::GuiElem::Feed)).value<QColor>().rgb(), 0, 16)
                                      .arg(vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::Feed)).value<QColor>().rgba(), 0, 16);
                 curFastFeed->setStyleSheet(arg);
                 });
  connect(vm->getModel(QString("cfgFg" + cfg->nameOf(Config::GuiElem::Feed)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , curFastFeed
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(vm->getValue("cfgFg" + cfg->nameOf(Config::GuiElem::Feed)).value<QColor>().rgb(), 0, 16)
                                      .arg(vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::Feed)).value<QColor>().rgba(), 0, 16);
                 curFastFeed->setStyleSheet(arg);
                 });
  connect(vm->getModel(QString("cfgF" + cfg->nameOf(Config::GuiElem::Feed)), curFastFeed->font())
        , &ValueModel::valueChanged
        , curFastFeed
        , [=](){ curFastFeed->setFont(vm->getValue("cfgF" + cfg->nameOf(Config::GuiElem::Feed)).value<QFont>());
                 });

  connect(vm->getModel(QString("cfgBg" + cfg->nameOf(Config::GuiElem::Speed)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , curSpeed
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(vm->getValue("cfgFg" + cfg->nameOf(Config::GuiElem::Speed)).value<QColor>().rgb(), 0, 16)
                                      .arg(vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::Speed)).value<QColor>().rgba(), 0, 16);
                 curSpeed->setStyleSheet(arg);
                 });
  connect(vm->getModel(QString("cfgFg" + cfg->nameOf(Config::GuiElem::Speed)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , curSpeed
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(vm->getValue("cfgFg" + cfg->nameOf(Config::GuiElem::Speed)).value<QColor>().rgb(), 0, 16)
                                      .arg(vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::Speed)).value<QColor>().rgba(), 0, 16);
                 curSpeed->setStyleSheet(arg);
                 });
  connect(vm->getModel(QString("cfgF" + cfg->nameOf(Config::GuiElem::Speed)), curSpeed->font())
        , &ValueModel::valueChanged
        , curSpeed
        , [=](){ curSpeed->setFont(vm->getValue("cfgF" + cfg->nameOf(Config::GuiElem::Speed)).value<QFont>());
                 });

  connect(vm->getModel(QString("cfgBg" + cfg->nameOf(Config::GuiElem::Feed)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , cmdFeed
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(vm->getValue("cfgFg" + cfg->nameOf(Config::GuiElem::Feed)).value<QColor>().rgb(), 0, 16)
                                      .arg(vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::Feed)).value<QColor>().rgba(), 0, 16);
                 cmdFeed->setStyleSheet(arg);
                 });
  connect(vm->getModel(QString("cfgFg" + cfg->nameOf(Config::GuiElem::Feed)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , cmdFeed
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(vm->getValue("cfgFg" + cfg->nameOf(Config::GuiElem::Feed)).value<QColor>().rgb(), 0, 16)
                                      .arg(vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::Feed)).value<QColor>().rgba(), 0, 16);
                 cmdFeed->setStyleSheet(arg);
                 });
  connect(vm->getModel(QString("cfgF" + cfg->nameOf(Config::GuiElem::Feed)), cmdFeed->font())
        , &ValueModel::valueChanged
        , cmdFeed
        , [=](){ cmdFeed->setFont(vm->getValue("cfgF" + cfg->nameOf(Config::GuiElem::Feed)).value<QFont>());
                 });

  connect(vm->getModel(QString("cfgBg" + cfg->nameOf(Config::GuiElem::Feed)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , cmdFastFeed
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(vm->getValue("cfgFg" + cfg->nameOf(Config::GuiElem::Feed)).value<QColor>().rgb(), 0, 16)
                                      .arg(vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::Feed)).value<QColor>().rgba(), 0, 16);
                 cmdFastFeed->setStyleSheet(arg);
                 });
  connect(vm->getModel(QString("cfgFg" + cfg->nameOf(Config::GuiElem::Feed)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , cmdFastFeed
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(vm->getValue("cfgFg" + cfg->nameOf(Config::GuiElem::Feed)).value<QColor>().rgb(), 0, 16)
                                      .arg(vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::Feed)).value<QColor>().rgba(), 0, 16);
                 cmdFastFeed->setStyleSheet(arg);
                 });
  connect(vm->getModel(QString("cfgF" + cfg->nameOf(Config::GuiElem::Feed)), cmdFastFeed->font())
        , &ValueModel::valueChanged
        , cmdFastFeed
        , [=](){ cmdFastFeed->setFont(vm->getValue("cfgF" + cfg->nameOf(Config::GuiElem::Feed)).value<QFont>());
                 });

  connect(vm->getModel(QString("cfgBg" + cfg->nameOf(Config::GuiElem::Speed)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , cmdSpeed
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(vm->getValue("cfgFg" + cfg->nameOf(Config::GuiElem::Speed)).value<QColor>().rgb(), 0, 16)
                                      .arg(vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::Speed)).value<QColor>().rgba(), 0, 16);
                 cmdSpeed->setStyleSheet(arg);
                 });
  connect(vm->getModel(QString("cfgFg" + cfg->nameOf(Config::GuiElem::Speed)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , cmdSpeed
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(vm->getValue("cfgFg" + cfg->nameOf(Config::GuiElem::Speed)).value<QColor>().rgb(), 0, 16)
                                      .arg(vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::Speed)).value<QColor>().rgba(), 0, 16);
                 cmdSpeed->setStyleSheet(arg);
                 });
  connect(vm->getModel(QString("cfgF" + cfg->nameOf(Config::GuiElem::Speed)), cmdSpeed->font())
        , &ValueModel::valueChanged
        , cmdSpeed
        , [=](){ cmdSpeed->setFont(vm->getValue("cfgF" + cfg->nameOf(Config::GuiElem::Speed)).value<QFont>());
                 });
  }


QString SpeedStatus::fileName() const {
  if (isVertical) return ":/src/statusInfo/SpeedInfo/VSpeedInfo.ui";
  return ":/src/statusInfo/SpeedInfo/HSpeedInfo.ui";
  }


// backend callback (backend uses factor, frontend percent
void SpeedStatus::feedRateChanged(const QVariant& v) {
  int rate = int(v.toDouble() * 100.0);

  slFeed->setValue(rate);
  feedFactor->setNum(rate);
  }


// backend callback (backend uses factor, frontend percent
void SpeedStatus::fastFeedRateChanged(const QVariant& v) {
  int rate = int(v.toDouble() * 100.0);

  slFastFeed->setValue(rate);
  fastfeedFactor->setNum(rate);
  }


// backend callback (backend uses factor, frontend percent
void SpeedStatus::speedRateChanged(const QVariant& v) {
  int rate = int(v.toDouble() * 100.0);

  slSpeed->setValue(rate);
  speedFactor->setNum(rate);
  }


// slider callback
void SpeedStatus::feedChanged(const QVariant& v) {
  qDebug() << "SpeedInfoDockable::feedChanged(" << v << ")";
  if (core->checkBE()) {
     core->beSetFeedOverride(v.toDouble() / 100.0);
     }
 else {
     vm->setValue("feedrate", v.toDouble() / 100.0);
     }
  }


// slider callback
void SpeedStatus::fastFeedChanged(const QVariant& v) {
  qDebug() << "SpeedInfoDockable::fastFeedChanged(" << v << ")";
  if (core->checkBE()) {
     core->beSetRapidOverride(v.toDouble() / 100.0);
     }
 else {
     vm->setValue("rapidrate", v.toDouble() / 100.0);
     }
  }


// slider callback
void SpeedStatus::speedChanged(const QVariant& v) {
  qDebug() << "SpeedInfoDockable::speedChanged(" << v << ")";
  if (core->checkBE()) {
     core->beSetSpindleOverride(v.toDouble() / 100.0);
     }
  else {
     vm->setValue("spindle0Scale", v.toDouble() / 100.0);
     }
  qDebug() << "width: " << speedFactor->size();
  }


void SpeedStatus::updateStyles() {
  QColor       colBg = vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::Feed)).value<QColor>();
  QColor       colFg = vm->getValue("cfgFg" + cfg->nameOf(Config::GuiElem::Feed)).value<QColor>();
  QFont        font  = vm->getValue("cfgF"  + cfg->nameOf(Config::GuiElem::Feed)).value<QFont>();
  QString      style = QString("color: #%1; background: #%2;").arg(colFg.rgb(), 0, 16).arg(colBg.rgba(), 0, 16);

  slFeed->setValue(int(vm->getValue("feedrate").toDouble() * 100));
  slFastFeed->setValue(int(vm->getValue("rapidrate").toDouble() * 100));
  slSpeed->setValue(int(vm->getValue("spindle0Scale").toDouble() * 100));

  curFeed->setStyleSheet(style);
  curFeed->setFont(font);
  cmdFeed->setStyleSheet(style);
  cmdFeed->setFont(font);
  curFastFeed->setStyleSheet(style);
  curFastFeed->setFont(font);
  cmdFastFeed->setStyleSheet(style);
  cmdFastFeed->setFont(font);

  colBg = vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::Speed)).value<QColor>();
  colFg = vm->getValue("cfgFg" + cfg->nameOf(Config::GuiElem::Speed)).value<QColor>();
  font  = vm->getValue("cfgF"  + cfg->nameOf(Config::GuiElem::Speed)).value<QFont>();
  style = QString("color: #%1; background: #%2;").arg(colFg.rgb(), 0, 16).arg(colBg.rgba(), 0, 16);

  curSpeed->setStyleSheet(style);
  curSpeed->setFont(font);
  cmdSpeed->setStyleSheet(style);
  cmdSpeed->setFont(font);
  }
