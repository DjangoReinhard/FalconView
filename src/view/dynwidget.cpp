#include <dynwidget.h>
#include <QString>
#include <QWidget>
#include <QFile>
#include <QUiLoader>
#include <QStackedLayout>


DynWidget::DynWidget(const QString& fileName, QWidget* parent)
 : QFrame(parent) {
  QFile     uiDesc(fileName);

  if (uiDesc.exists()) {
     QUiLoader loader;
     QWidget* w = loader.load(&uiDesc, this);
     QStackedLayout* layout = new QStackedLayout;

     uiDesc.close();
     layout->addWidget(w);
     setLayout(layout);
     }
  }
