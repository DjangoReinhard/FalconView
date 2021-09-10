#include <dockable.h>
#include <QString>
#include <QWidget>
#include <QFile>
#include <QUiLoader>


Dockable::Dockable(const QString& fileName, const QString& title, QWidget* parent)
 : QDockWidget(title, parent) {
  QFile     uiDesc(fileName);

  if (uiDesc.exists()) {
     QUiLoader loader;
     QWidget* w = loader.load(&uiDesc, this);

     uiDesc.close();
     setWidget(w);
     }
  setObjectName(title);
  }
