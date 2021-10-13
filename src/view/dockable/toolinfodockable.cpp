#include <toolinfodockable.h>
#include <labeladapter.h>
#include <valuemanager.h>
#include <configmgr.h>
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
  connectSignals();
  updateStyles();
}


void ToolInfoDockable::connectSignals() {
  ValueManager vm;
  Config       cfg;

  curTool->setStyleSheet("background: white; ");
  connect(vm.getModel("toolInSpindle", 0),  &ValueModel::valueChanged
        , curTool, [=](){ curTool->setNum(ValueManager().getValue("toolInSpindle").toInt()); });
  connect(vm.getModel("pocketPrepared", 0),  &ValueModel::valueChanged
        , nxtTool, [=](){ nxtTool->setNum(ValueManager().getValue("pocketPrepared").toInt()); });

  connect(vm.getModel(QString("cfgBg") + cfg.guiSettings[10], QColor(Qt::white))
        , &ValueModel::valueChanged
        , curTool
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.guiSettings[10]).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.guiSettings[10]).value<QColor>().rgba(), 0, 16);
                 curTool->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg") + cfg.guiSettings[10], QColor(Qt::black))
        , &ValueModel::valueChanged
        , curTool
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.guiSettings[10]).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.guiSettings[10]).value<QColor>().rgba(), 0, 16);
                 curTool->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF") + cfg.guiSettings[10], curTool->font())
        , &ValueModel::valueChanged
        , curTool
        , [=](){ QFont font = ValueManager().getValue(QString("cfgF") + cfg.guiSettings[10]).value<QFont>();

                 curTool->setFont(font);
                 });
  connect(vm.getModel(QString("cfgBg") + cfg.guiSettings[11], QColor(Qt::white))
        , &ValueModel::valueChanged
        , nxtTool
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.guiSettings[11]).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.guiSettings[11]).value<QColor>().rgba(), 0, 16);
                 nxtTool->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg") + cfg.guiSettings[11], QColor(Qt::black))
        , &ValueModel::valueChanged
        , nxtTool
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.guiSettings[11]).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.guiSettings[11]).value<QColor>().rgba(), 0, 16);
                 nxtTool->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF") + cfg.guiSettings[11], nxtTool->font())
        , &ValueModel::valueChanged
        , nxtTool
        , [=](){ QFont font = ValueManager().getValue(QString("cfgF") + cfg.guiSettings[11]).value<QFont>();

                 nxtTool->setFont(font);
                 });
  connect(vm.getModel(QString("cfgBg") + cfg.guiSettings[9], QColor(Qt::white))
        , &ValueModel::valueChanged
        , tlDesc->label()
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.guiSettings[9]).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.guiSettings[9]).value<QColor>().rgba(), 0, 16);
                 tlDesc->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg") + cfg.guiSettings[9], QColor(Qt::black))
        , &ValueModel::valueChanged
        , tlDesc->label()
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.guiSettings[9]).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.guiSettings[9]).value<QColor>().rgba(), 0, 16);
                 tlDesc->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF") + cfg.guiSettings[9], tlDesc->label()->font())
        , &ValueModel::valueChanged
        , tlDesc->label()
        , [=](){ QFont font = ValueManager().getValue(QString("cfgF") + cfg.guiSettings[9]).value<QFont>();

                 tlDesc->label()->setFont(font);
                 });
  connect(vm.getModel(QString("cfgBg") + cfg.guiSettings[9], QColor(Qt::white))
        , &ValueModel::valueChanged
        , tlLen->label()
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.guiSettings[9]).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.guiSettings[9]).value<QColor>().rgba(), 0, 16);
                 tlLen->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg") + cfg.guiSettings[9], QColor(Qt::black))
        , &ValueModel::valueChanged
        , tlLen->label()
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.guiSettings[9]).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.guiSettings[9]).value<QColor>().rgba(), 0, 16);
                 tlLen->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF") + cfg.guiSettings[9], tlLen->label()->font())
        , &ValueModel::valueChanged
        , tlLen->label()
        , [=](){ QFont font = ValueManager().getValue(QString("cfgF") + cfg.guiSettings[9]).value<QFont>();

                 tlLen->label()->setFont(font);
                 });
  connect(vm.getModel(QString("cfgBg") + cfg.guiSettings[9], QColor(Qt::white))
        , &ValueModel::valueChanged
        , tlRad->label()
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.guiSettings[9]).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.guiSettings[9]).value<QColor>().rgba(), 0, 16);
                 tlRad->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg") + cfg.guiSettings[9], QColor(Qt::black))
        , &ValueModel::valueChanged
        , tlRad->label()
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.guiSettings[9]).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.guiSettings[9]).value<QColor>().rgba(), 0, 16);
                 tlRad->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF") + cfg.guiSettings[9], tlRad->label()->font())
        , &ValueModel::valueChanged
        , tlRad->label()
        , [=](){ QFont font = ValueManager().getValue(QString("cfgF") + cfg.guiSettings[9]).value<QFont>();

                 tlRad->label()->setFont(font);
                 });
  }


void ToolInfoDockable::updateStyles() {
  ValueManager vm;
  Config       cfg;

  curTool->setStyleSheet(QString("color: #%1; background: #%2;")
                         .arg(vm.getValue(QString("cfgFg") + cfg.guiSettings[10]).value<QColor>().rgb(), 0, 16)
                         .arg(vm.getValue(QString("cfgBg") + cfg.guiSettings[10]).value<QColor>().rgba(), 0, 16));
  curTool->setFont(vm.getValue(QString("cfgF") + cfg.guiSettings[10]).value<QFont>());
  nxtTool->setStyleSheet(QString("color: #%1; background: #%2;")
                         .arg(vm.getValue(QString("cfgFg") + cfg.guiSettings[11]).value<QColor>().rgb(), 0, 16)
                         .arg(vm.getValue(QString("cfgBg") + cfg.guiSettings[11]).value<QColor>().rgba(), 0, 16));
  nxtTool->setFont(vm.getValue(QString("cfgF") + cfg.guiSettings[11]).value<QFont>());
  QString style = QString("color: #%1; background: #%2;")
          .arg(vm.getValue(QString("cfgFg") + cfg.guiSettings[9]).value<QColor>().rgb(), 0, 16)
          .arg(vm.getValue(QString("cfgBg") + cfg.guiSettings[9]).value<QColor>().rgba(), 0, 16);
  QFont font = vm.getValue(QString("cfgF") + cfg.guiSettings[9]).value<QFont>();

  tlDesc->label()->setStyleSheet(style);
  tlDesc->label()->setFont(font);
  tlLen->label()->setStyleSheet(style);
  tlLen->label()->setFont(font);
  tlRad->label()->setStyleSheet(style);
  tlRad->label()->setFont(font);
  }
