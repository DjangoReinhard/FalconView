#include <dynwidget.h>
#include <QString>
#include <QWidget>
#include <QAction>
#include <QFile>
#include <QUiLoader>
#include <QStackedLayout>

DynWidget::DynWidget(const QString& fileName, QWidget* parent, int margin)
 : QWidget(parent)
 , vAction(nullptr) {
  setLayout(new QVBoxLayout);
  layout()->setContentsMargins(0, 0, 0, 0);
  w = loadFromUI(fileName);
  if (w) layout()->addWidget(w);
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
