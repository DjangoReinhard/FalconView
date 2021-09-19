#include <dynwidget.h>
#include <QString>
#include <QWidget>
#include <QFile>
#include <QUiLoader>
#include <QStackedLayout>

DynWidget::DynWidget(const QString& fileName, QWidget* parent)
 : QWidget(parent) {
  setLayout(new QVBoxLayout);
  layout()->addWidget(loadFromUI(fileName));
  }


QWidget* DynWidget::loadFromUI(const QString& fileName) {
  QFile     uiDesc(fileName);
  QWidget*  rv = nullptr;

  if (uiDesc.exists()) {
     QUiLoader loader;
     rv = loader.load(&uiDesc, this);

     uiDesc.close();
     }
  return rv;
  }
