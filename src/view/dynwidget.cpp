#include <dynwidget.h>
#include <QString>
#include <QFrame>
#include <QAction>
#include <QFile>
#include <QUiLoader>
#include <QStackedLayout>


DynWidget::DynWidget(const QString& fileName, QWidget* parent)
 : QFrame(parent)
 , vAction(nullptr) {
  QFile     uiDesc(fileName);

  if (uiDesc.exists()) {
     setLayout(new QVBoxLayout);
     w = loadFromUI(uiDesc);
     layout()->setContentsMargins(0, 0, 0, 0);
     if (w) layout()->addWidget(w);
     }
  }


void DynWidget::init() {
  connectSignals();
  updateStyles();
  }


QAction* DynWidget::viewAction() {
  if (!vAction) {
     vAction = new QAction(this);

     vAction->setMenuRole(QAction::NoRole);
     vAction->setText(objectName());
     }
  return vAction;
  }


QWidget* DynWidget::loadFromUI(QFile& uiFile) {
  QWidget*  rv = nullptr;

  if (uiFile.exists()) {
     QUiLoader loader;
     rv = loader.load(&uiFile, this);

     uiFile.close();
     }
  return rv;
  }
