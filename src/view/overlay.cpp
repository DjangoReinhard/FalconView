#include <overlay.h>
#include <QFile>
#include <QUiLoader>


Overlay::Overlay(QFile& uiDesc, QWidget *parent)
 : QWidget(parent) {
  initializeWidget(uiDesc);
  }


void Overlay::initializeWidget(QFile &uiDesc) {
  QUiLoader loader;
  QWidget*  w = loader.load(&uiDesc, this);

  uiDesc.close();

  }
