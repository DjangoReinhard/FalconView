#include <overlay.h>
#include <QFile>
#include <QUiLoader>
#include <QGridLayout>
#include <QLabel>
#include <labeladapter.h>
#include <valuemanager.h>


Overlay::Overlay(QFile& uiDesc, QWidget *parent)
 : QWidget(parent) {
  initializeWidget(uiDesc);
  }


void Overlay::initializeWidget(QFile &uiDesc) {
  QUiLoader loader;
  QWidget*  w = loader.load(&uiDesc, this);

  ovRelX = findChild<QLabel*>("ovRelX");
  ovRelY = findChild<QLabel*>("ovRelY");
  ovRelZ = findChild<QLabel*>("ovRelZ");
  ovRelA = findChild<QLabel*>("ovRelA");
  ovRelB = findChild<QLabel*>("ovRelB");
  ovDtgX = findChild<QLabel*>("ovDtgX");
  ovDtgY = findChild<QLabel*>("ovDtgY");
  ovDtgZ = findChild<QLabel*>("ovDtgZ");
  ovDtgA = findChild<QLabel*>("ovDtgA");
  ovDtgB = findChild<QLabel*>("ovDtgB");
  xTitle = findChild<QLabel*>("xTitle");

  relX = new LabelAdapter(ovRelX);
  relY = new LabelAdapter(ovRelY);

  uiDesc.close();
  setLayout(new QGridLayout());
  ((QGridLayout*)layout())->addWidget(w, 0, 0);
  w->raise();

  QString relStyles("color: blue; background: rgba(220,220,255,200);");
  QString dtgStyles("color: orange; background: rgba(255,255,220,200);");
  QString titleStyles("color: blue; background: rgba(255,255,255,200);");

  ovRelX->setStyleSheet(relStyles);
  ovRelY->setStyleSheet(relStyles);
  ovRelZ->setStyleSheet(relStyles);
  ovRelA->setStyleSheet(relStyles);
  ovRelB->setStyleSheet(relStyles);
  ovDtgX->setStyleSheet(dtgStyles);
  ovDtgY->setStyleSheet(dtgStyles);
  ovDtgZ->setStyleSheet(dtgStyles);
  ovDtgA->setStyleSheet(dtgStyles);
  ovDtgB->setStyleSheet(dtgStyles);
  xTitle->setStyleSheet(titleStyles);
  ValueManager vm;

  connect(vm.getModel("relX"), &ValueModel::valueChanged, relX, &LabelAdapter::setValue);
  connect(vm.getModel("relY"), &ValueModel::valueChanged, relY, &LabelAdapter::setValue);
  }
