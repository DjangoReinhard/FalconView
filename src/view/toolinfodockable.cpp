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
 , curTool(nullptr)
 , nxtTool(nullptr)
 , tlDesc(nullptr)
 , tlLen(nullptr)
 , tlRad(nullptr) {
  initializeWidget(widget());
  }


ToolInfoDockable::~ToolInfoDockable() {
  /*
  delete tlDesc;
  delete tlLen;
  delete tlRad;
   */
  }


void ToolInfoDockable::initializeWidget(QWidget* /* w */) {
  tlDesc  = new LabelAdapter(findChild<QLabel*>("toolDesc"));
  tlLen   = new LabelAdapter(findChild<QLabel*>("toolLen"));
  tlRad   = new LabelAdapter(findChild<QLabel*>("toolRadius"));
  curTool = findChild<QLabel*>("curToolNum");
  nxtTool = findChild<QLabel*>("nextToolNum");
  ValueManager vm;

  curTool->setStyleSheet("background: white; ");
  connect(vm.getModel("toolInSpindle", 0),  &ValueModel::valueChanged
        , curTool, [=](){ curTool->setNum(ValueManager().getValue("toolInSpindle").toInt()); });
  connect(vm.getModel("pocketPrepared", 0),  &ValueModel::valueChanged
        , nxtTool, [=](){ curTool->setNum(ValueManager().getValue("pocketPrepared").toInt()); });
  }
