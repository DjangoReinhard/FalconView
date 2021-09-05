#include <overlay.h>
#include <QFile>
#include <QUiLoader>
#include <QGridLayout>
#include <QLabel>
#include <labeladapter.h>
#include <valuemanager.h>


Overlay::Overlay(const QString& fileName, QWidget *parent)
 : DynWidget(fileName, parent) {
  initializeWidget();
  }


void Overlay::initializeWidget() {
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

  connect(vm.getModel("relX", 0), &ValueModel::valueChanged, relX, &LabelAdapter::setValue);
  connect(vm.getModel("relY", 0), &ValueModel::valueChanged, relY, &LabelAdapter::setValue);
  }
