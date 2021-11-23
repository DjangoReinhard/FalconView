#include <speedstatus.h>
#include <labeladapter.h>
#include <valuemanager.h>
#include <configacc.h>
#include <core.h>
#include <QFile>
#include <QSlider>
#include <QUiLoader>
#include <QLabel>
#include <QDebug>


SpeedStatus::SpeedStatus(const QString& fileName, QWidget* parent)
 : DynCenterWidget(fileName, tr("SpeedInfo"), false, parent)
 , curFeed(nullptr)
 , curFastFeed(nullptr)
 , curSpeed(nullptr)
 , cmdFeed(nullptr)
 , cmdFastFeed(nullptr)
 , cmdSpeed(nullptr)
 , feedFactor(nullptr)
 , fastfeedFactor(nullptr)
 , speedFactor(nullptr)
 , slFeed(nullptr)
 , slFastFeed(nullptr)
 , slSpeed(nullptr) {
  setFocusPolicy(Qt::FocusPolicy::NoFocus);
  }


SpeedStatus::~SpeedStatus() {
  }


QWidget* SpeedStatus::createContent() {
  QWidget* rv = DynCenterWidget::createContent();

  curFeed        = new LabelAdapter(findChild<QLabel*>("curFeed"), 0);
  curFastFeed    = new LabelAdapter(findChild<QLabel*>("curFastFeed"), 0);
  curSpeed       = new LabelAdapter(findChild<QLabel*>("curSpeed"), 0);
  cmdFeed        = new LabelAdapter(findChild<QLabel*>("cmdFeed"), 0);
  cmdFastFeed    = new LabelAdapter(findChild<QLabel*>("cmdFastFeed"), 0);
  cmdSpeed       = new LabelAdapter(findChild<QLabel*>("cmdSpeed"), 0);
  feedFactor     = new LabelAdapter(findChild<QLabel*>("feedFactor"), 0);
  fastfeedFactor = new LabelAdapter(findChild<QLabel*>("fastfeedFactor"), 0);
  speedFactor    = new LabelAdapter(findChild<QLabel*>("speedFactor"), 0);
  slFeed         = findChild<QSlider*>("slFeed");
  slFeed->setTickInterval(10);
  slFeed->setTickPosition(QSlider::TicksRight);
  slFastFeed     = findChild<QSlider*>("slFastFeed");
  slFastFeed->setTickInterval(7);
  slFastFeed->setTickPosition(QSlider::TicksRight);
  slSpeed        = findChild<QSlider*>("slSpeed");
  slSpeed->setTickInterval(10);
  slSpeed->setTickPosition(QSlider::TicksRight);

  return rv;
  }


void SpeedStatus::connectSignals() {
  ValueManager vm;
  Config       cfg;

  connect(vm.getModel("feedrate", 100),      &ValueModel::valueChanged, this, &SpeedStatus::feedRateChanged);
  connect(vm.getModel("rapidrate", 100),     &ValueModel::valueChanged, this, &SpeedStatus::fastFeedRateChanged);
  connect(vm.getModel("spindle0Scale", 100), &ValueModel::valueChanged, this, &SpeedStatus::speedRateChanged);

  connect(vm.getModel("cmdVelocity", 0),     &ValueModel::valueChanged, cmdFeed,     &LabelAdapter::setValue);
  connect(vm.getModel("maxVelocity", 0),     &ValueModel::valueChanged, cmdFastFeed, &LabelAdapter::setValue);
  connect(vm.getModel("spindle0Speed", 0),   &ValueModel::valueChanged, cmdSpeed,    &LabelAdapter::setValue);
  connect(vm.getModel("curVelocity", 0),     &ValueModel::valueChanged, curFeed,     &LabelAdapter::setValue);
  connect(vm.getModel("curRapid", 0),        &ValueModel::valueChanged, curFastFeed, &LabelAdapter::setValue);
  connect(vm.getModel("curSpeed", 0),        &ValueModel::valueChanged, curSpeed,    &LabelAdapter::setValue);
  connect(slFeed,     &QSlider::valueChanged, this, &SpeedStatus::feedChanged);
  connect(slFastFeed, &QSlider::valueChanged, this, &SpeedStatus::fastFeedChanged);
  connect(slSpeed,    &QSlider::valueChanged, this, &SpeedStatus::speedChanged);

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::Feed)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , curFeed->label()
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::Feed)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::Feed)).value<QColor>().rgba(), 0, 16);
                 curFeed->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::Feed)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , curFeed->label()
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::Feed)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::Feed)).value<QColor>().rgba(), 0, 16);
                 curFeed->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::Feed)), curFeed->label()->font())
        , &ValueModel::valueChanged
        , curFeed->label()
        , [=](){ curFeed->label()->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::Feed)).value<QFont>());
                 });

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::Feed)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , curFastFeed->label()
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::Feed)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::Feed)).value<QColor>().rgba(), 0, 16);
                 curFastFeed->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::Feed)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , curFastFeed->label()
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::Feed)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::Feed)).value<QColor>().rgba(), 0, 16);
                 curFastFeed->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::Feed)), curFastFeed->label()->font())
        , &ValueModel::valueChanged
        , curFastFeed->label()
        , [=](){ curFastFeed->label()->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::Feed)).value<QFont>());
                 });

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::Speed)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , curSpeed->label()
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::Speed)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::Speed)).value<QColor>().rgba(), 0, 16);
                 curSpeed->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::Speed)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , curSpeed->label()
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::Speed)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::Speed)).value<QColor>().rgba(), 0, 16);
                 curSpeed->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::Speed)), curSpeed->label()->font())
        , &ValueModel::valueChanged
        , curSpeed->label()
        , [=](){ curSpeed->label()->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::Speed)).value<QFont>());
                 });

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::Feed)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , cmdFeed->label()
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::Feed)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::Feed)).value<QColor>().rgba(), 0, 16);
                 cmdFeed->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::Feed)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , cmdFeed->label()
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::Feed)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::Feed)).value<QColor>().rgba(), 0, 16);
                 cmdFeed->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::Feed)), cmdFeed->label()->font())
        , &ValueModel::valueChanged
        , cmdFeed->label()
        , [=](){ cmdFeed->label()->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::Feed)).value<QFont>());
                 });

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::Feed)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , cmdFastFeed->label()
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::Feed)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::Feed)).value<QColor>().rgba(), 0, 16);
                 cmdFastFeed->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::Feed)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , cmdFastFeed->label()
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::Feed)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::Feed)).value<QColor>().rgba(), 0, 16);
                 cmdFastFeed->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::Feed)), cmdFastFeed->label()->font())
        , &ValueModel::valueChanged
        , cmdFastFeed->label()
        , [=](){ cmdFastFeed->label()->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::Feed)).value<QFont>());
                 });

  connect(vm.getModel(QString("cfgBg" + cfg.nameOf(Config::GuiElem::Speed)), QColor(Qt::white))
        , &ValueModel::valueChanged
        , cmdSpeed->label()
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::Speed)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::Speed)).value<QColor>().rgba(), 0, 16);
                 cmdSpeed->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg" + cfg.nameOf(Config::GuiElem::Speed)), QColor(Qt::black))
        , &ValueModel::valueChanged
        , cmdSpeed->label()
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::Speed)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::Speed)).value<QColor>().rgba(), 0, 16);
                 cmdSpeed->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF" + cfg.nameOf(Config::GuiElem::Speed)), cmdSpeed->label()->font())
        , &ValueModel::valueChanged
        , cmdSpeed->label()
        , [=](){ cmdSpeed->label()->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::Speed)).value<QFont>());
                 });
  }


// backend callback (backend uses factor, frontend percent
void SpeedStatus::feedRateChanged(const QVariant& v) {
  int rate = int(v.toDouble() * 100.0);

  slFeed->setValue(rate);
  feedFactor->setValue(rate);
  }


// backend callback (backend uses factor, frontend percent
void SpeedStatus::fastFeedRateChanged(const QVariant& v) {
  int rate = int(v.toDouble() * 100.0);

  slFastFeed->setValue(rate);
  fastfeedFactor->setValue(rate);
  }


// backend callback (backend uses factor, frontend percent
void SpeedStatus::speedRateChanged(const QVariant& v) {
  int rate = int(v.toDouble() * 100.0);

  slSpeed->setValue(rate);
  speedFactor->setValue(rate);
  }


// slider callback
void SpeedStatus::feedChanged(const QVariant& v) {
  qDebug() << "SpeedInfoDockable::feedChanged(" << v << ")";
  Core().beSetFeedOverride(v.toDouble() / 100.0);
  }


// slider callback
void SpeedStatus::fastFeedChanged(const QVariant& v) {
  qDebug() << "SpeedInfoDockable::fastFeedChanged(" << v << ")";
  Core().beSetRapidOverride(v.toDouble() / 100.0);
  }


// slider callback
void SpeedStatus::speedChanged(const QVariant& v) {
  qDebug() << "SpeedInfoDockable::speedChanged(" << v << ")";
  Core().beSetSpindleOverride(v.toDouble() / 100.0);
  }


void SpeedStatus::updateStyles() {
  ValueManager vm;
  Config       cfg;
  QColor       colBg = vm.getValue("cfgBg" + cfg.nameOf(Config::GuiElem::Feed)).value<QColor>();
  QColor       colFg = vm.getValue("cfgFg" + cfg.nameOf(Config::GuiElem::Feed)).value<QColor>();
  QFont        font  = vm.getValue("cfgF"  + cfg.nameOf(Config::GuiElem::Feed)).value<QFont>();
  QString      style = QString("color: #%1; background: #%2;").arg(colFg.rgb(), 0, 16).arg(colBg.rgba(), 0, 16);

  slFeed->setValue(int(vm.getValue("feedrate").toDouble() * 100));
  slFastFeed->setValue(int(vm.getValue("rapidrate").toDouble() * 100));
  slSpeed->setValue(int(vm.getValue("spindle0Scale").toDouble() * 100));

  curFeed->label()->setStyleSheet(style);
  curFeed->label()->setFont(font);
  cmdFeed->label()->setStyleSheet(style);
  cmdFeed->label()->setFont(font);
  curFastFeed->label()->setStyleSheet(style);
  curFastFeed->label()->setFont(font);
  cmdFastFeed->label()->setStyleSheet(style);
  cmdFastFeed->label()->setFont(font);

  colBg = vm.getValue("cfgBg" + cfg.nameOf(Config::GuiElem::Speed)).value<QColor>();
  colFg = vm.getValue("cfgFg" + cfg.nameOf(Config::GuiElem::Speed)).value<QColor>();
  font  = vm.getValue("cfgF"  + cfg.nameOf(Config::GuiElem::Speed)).value<QFont>();
  style = QString("color: #%1; background: #%2;").arg(colFg.rgb(), 0, 16).arg(colBg.rgba(), 0, 16);

  curSpeed->label()->setStyleSheet(style);
  curSpeed->label()->setFont(font);
  cmdSpeed->label()->setStyleSheet(style);
  cmdSpeed->label()->setFont(font);
  }
