#include <speedinfodockable.h>
#include <labeladapter.h>
#include <valuemanager.h>
#include <QFile>
#include <QUiLoader>
#include <QLabel>


SpeedInfoDockable::SpeedInfoDockable(QFile& uiDesc, QWidget* parent)
 : QDockWidget(tr("SpeedInfo"), parent) {
  initializeWidget(uiDesc);
  }


SpeedInfoDockable::~SpeedInfoDockable() {
  delete curFeed;
  delete curFastFeed;
  delete curSpeed;
  delete cmdFeed;
  delete cmdFastFeed;
  delete cmdSpeed;
  }


void SpeedInfoDockable::initializeWidget(QFile &uiDesc) {
  QUiLoader loader;
  QWidget*  w = loader.load(&uiDesc, this);

  uiDesc.close();
  setWidget(w);

  curFeed     = new LabelAdapter(findChild<QLabel*>("curFeed"));
  curFastFeed = new LabelAdapter(findChild<QLabel*>("curFastFeed"));
  curSpeed    = new LabelAdapter(findChild<QLabel*>("curSpeed"));
  cmdFeed     = new LabelAdapter(findChild<QLabel*>("cmdFeed"));
  cmdFastFeed = new LabelAdapter(findChild<QLabel*>("cmdFastFeed"));
  cmdSpeed    = new LabelAdapter(findChild<QLabel*>("cmdSpeed"));
  ValueManager vm;

  connect(vm.getModel("feedrate", 0),      &ValueModel::valueChanged, curFeed,     &LabelAdapter::setValue);
  connect(vm.getModel("curVelocity", 0),   &ValueModel::valueChanged, cmdFeed,     &LabelAdapter::setValue);
  connect(vm.getModel("rapidrate", 0),     &ValueModel::valueChanged, curFastFeed, &LabelAdapter::setValue);
  connect(vm.getModel("spindle0Speed", 0), &ValueModel::valueChanged, curSpeed,    &LabelAdapter::setValue);
  }
