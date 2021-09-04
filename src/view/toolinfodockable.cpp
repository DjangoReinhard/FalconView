#include <toolinfodockable.h>
#include <labeladapter.h>
#include <valuemanager.h>
#include <QUiLoader>
#include <QFile>
#include <QLabel>
#include <QResizeEvent>
#include <QDebug>


ToolInfoDockable::ToolInfoDockable(QFile& uiDesc, QWidget* parent)
 : QDockWidget(tr("ToolInfo"), parent)
 , tlCur(nullptr)
 , tlDesc(nullptr)
 , tlLen(nullptr)
 , tlRad(nullptr)
 , tlNext(nullptr) {
  initializeWidget(uiDesc);
  }


ToolInfoDockable::~ToolInfoDockable() {
  delete tlCur;
  delete tlDesc;
  delete tlLen;
  delete tlRad;
  delete tlNext;
  }


void ToolInfoDockable::initializeWidget(QFile &uiDesc) {
  QUiLoader loader;
  QWidget*  w = loader.load(&uiDesc, this);

  uiDesc.close();
  setWidget(w);

  tlCur  = new LabelAdapter(findChild<QLabel*>("curToolNum"));
  tlDesc = new LabelAdapter(findChild<QLabel*>("toolDesc"));
  tlLen  = new LabelAdapter(findChild<QLabel*>("toolLen"));
  tlRad  = new LabelAdapter(findChild<QLabel*>("toolRadius"));
  tlNext = new LabelAdapter(findChild<QLabel*>("nextToolNum"));
  ValueManager vm;

  connect(vm.getModel("toolInSpindle", 0),  &ValueModel::valueChanged, tlCur,  &LabelAdapter::setValue);
  connect(vm.getModel("pocketPrepared", 0), &ValueModel::valueChanged, tlNext, &LabelAdapter::setValue);
  }
