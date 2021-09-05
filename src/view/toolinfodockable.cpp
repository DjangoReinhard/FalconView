#include <toolinfodockable.h>
#include <labeladapter.h>
#include <valuemanager.h>
#include <QUiLoader>
#include <QFile>
#include <QLabel>
#include <QResizeEvent>
#include <QDebug>


ToolInfoDockable::ToolInfoDockable(const QString & fileName, QWidget* parent)
 : Dockable(fileName, tr("ToolInfo"), parent)
 , tlCur(nullptr)
 , tlDesc(nullptr)
 , tlLen(nullptr)
 , tlRad(nullptr)
 , tlNext(nullptr) {
  initializeWidget(widget());
  }


ToolInfoDockable::~ToolInfoDockable() {
  delete tlCur;
  delete tlDesc;
  delete tlLen;
  delete tlRad;
  delete tlNext;
  }


void ToolInfoDockable::initializeWidget(QWidget* /* w */) {
  tlCur  = new LabelAdapter(findChild<QLabel*>("curToolNum"));
  tlDesc = new LabelAdapter(findChild<QLabel*>("toolDesc"));
  tlLen  = new LabelAdapter(findChild<QLabel*>("toolLen"));
  tlRad  = new LabelAdapter(findChild<QLabel*>("toolRadius"));
  tlNext = new LabelAdapter(findChild<QLabel*>("nextToolNum"));
  ValueManager vm;

  tlCur->label()->setStyleSheet("background: white; ");
  connect(vm.getModel("toolInSpindle", 0),  &ValueModel::valueChanged, tlCur,  &LabelAdapter::setValue);
  connect(vm.getModel("pocketPrepared", 0), &ValueModel::valueChanged, tlNext, &LabelAdapter::setValue);
  }
