#include <speedinfodockable.h>
#include <labeladapter.h>
#include <valuemanager.h>
#include <configacc.h>
#include <QFile>
#include <QSlider>
#include <QUiLoader>
#include <QLabel>
#include <QDebug>


SpeedInfoDockable::SpeedInfoDockable(const QString& fileName, QWidget* parent)
 : Dockable(fileName, tr("SpeedInfo"), parent)
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
  initializeWidget(widget());
  }


SpeedInfoDockable::~SpeedInfoDockable() {
    /*
  delete curFeed;
  delete curFastFeed;
  delete curSpeed;
  delete cmdFeed;
  delete cmdFastFeed;
  delete cmdSpeed;
  */
  }


void SpeedInfoDockable::initializeWidget(QWidget* /* w */) {
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

  setFocusPolicy(Qt::FocusPolicy::NoFocus);
  connectSignals();
  updateStyles();
  }


void SpeedInfoDockable::connectSignals() {
  ValueManager vm;
  Config       cfg;

  connect(vm.getModel("feedrate", 100),      &ValueModel::valueChanged, slFeed,     [=](QVariant v){ slFeed->setValue(int(v.toDouble() * 100.0)); });
  connect(vm.getModel("rapidrate", 100),     &ValueModel::valueChanged, slFastFeed, [=](QVariant v){ slFastFeed->setValue(int(v.toDouble() * 100.0)); });
  connect(vm.getModel("spindle0Scale", 100), &ValueModel::valueChanged, slSpeed,    [=](QVariant v){ slSpeed->setValue(int(v.toDouble() * 100.0)); });

  connect(vm.getModel("cmdVelocity", 0),     &ValueModel::valueChanged, cmdFeed,     &LabelAdapter::setValue);
  connect(vm.getModel("maxVelocity", 0),     &ValueModel::valueChanged, cmdFastFeed, &LabelAdapter::setValue);
  connect(vm.getModel("spindle0Speed", 0),   &ValueModel::valueChanged, cmdSpeed,    &LabelAdapter::setValue);
  connect(vm.getModel("curVelocity", 0),     &ValueModel::valueChanged, curFeed,     &LabelAdapter::setValue);
  connect(vm.getModel("curRapid", 0),        &ValueModel::valueChanged, curFastFeed, &LabelAdapter::setValue);
  connect(vm.getModel("curSpeed", 0),        &ValueModel::valueChanged, curSpeed,    &LabelAdapter::setValue);
  connect(slFeed,     &QSlider::valueChanged, feedFactor,     [=](QVariant v){ feedFactor->setValue(v.toDouble()); });
  connect(slFastFeed, &QSlider::valueChanged, fastfeedFactor, [=](QVariant v){ fastfeedFactor->setValue(v.toDouble()); });
  connect(slSpeed,    &QSlider::valueChanged, speedFactor,    [=](QVariant v){ speedFactor->setValue(v.toDouble()); });


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


void SpeedInfoDockable::updateStyles() {
  ValueManager vm;
  Config       cfg;
  QColor       colBg = vm.getValue("cfgBg" + cfg.nameOf(Config::GuiElem::Feed)).value<QColor>();
  QColor       colFg = vm.getValue("cfgFg" + cfg.nameOf(Config::GuiElem::Feed)).value<QColor>();
  QFont        font  = vm.getValue("cfgF"  + cfg.nameOf(Config::GuiElem::Feed)).value<QFont>();
  QString      style = QString("color: #%1; background: #%2;").arg(colFg.rgb(), 0, 16).arg(colBg.rgba(), 0, 16);

  slFeed->setValue(int(vm.getValue("feedrate").toDouble() * 100));
  slFastFeed->setValue(int(vm.getValue("rapidrate").toDouble() * 100));
  slSpeed->setValue(int(vm.getValue("spindle0Scale").toDouble() * 100));

//  qDebug() << "feed style: " << style;
//  qDebug() << "feed font:  " << font;

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

//  qDebug() << "speed style: " << style;
//  qDebug() << "speed font:  " << font;

  curSpeed->label()->setStyleSheet(style);
  curSpeed->label()->setFont(font);
  cmdSpeed->label()->setStyleSheet(style);
  cmdSpeed->label()->setFont(font);
  }
