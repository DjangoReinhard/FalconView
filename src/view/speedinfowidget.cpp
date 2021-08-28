#include "speedinfowidget.h"
#include "labeladapter.h"
#include <QFile>
#include <QUiLoader>
#include <QLabel>


SpeedInfoWidget::SpeedInfoWidget(QFile& uiDesc, QWidget* parent)
 : QDockWidget(tr("SpeedInfo"), parent) {
  initializeWidget(uiDesc);
  }


SpeedInfoWidget::~SpeedInfoWidget() {
  delete curFeed;
  delete curFastFeed;
  delete curSpeed;
  delete cmdFeed;
  delete cmdFastFeed;
  delete cmdSpeed;
  }

void SpeedInfoWidget::initializeWidget(QFile &uiDesc) {
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
  }
