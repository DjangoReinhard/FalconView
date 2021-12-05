#include <toolstatus.h>
#include <labeladapter.h>
#include <valuemanager.h>
#include <configacc.h>
#include <core.h>
#include <tooltable.h>
#include <QUiLoader>
#include <QFile>
#include <QLabel>
#include <QResizeEvent>
#include <QDebug>


ToolStatus::ToolStatus(const QString & fileName, QWidget* parent)
 : DynCenterWidget(fileName, "ToolStatus", parent)
 , curTool(nullptr)
 , nxtTool(nullptr)
 , tlDesc(nullptr)
 , tlLen(nullptr)
 , tlRad(nullptr) {
  setFocusPolicy(Qt::FocusPolicy::NoFocus);
  setWindowTitle(tr("ToolStatus"));
  }


ToolStatus::~ToolStatus() {
  }


QWidget* ToolStatus::createContent() {
  QWidget* rv = DynCenterWidget::createContent();

  tlDesc  = findChild<QLabel*>("toolDesc");
  tlLen   = new LabelAdapter(findChild<QLabel*>("toolLen"));
  tlRad   = new LabelAdapter(findChild<QLabel*>("toolRadius"));
  curTool = new LabelAdapter(findChild<QLabel*>("curToolNum"), 0);
  nxtTool = new LabelAdapter(findChild<QLabel*>("nextToolNum"), 0);
//  tlDesc->setText(tr(tlDesc->text().toStdString().c_str(), "ToolInfoForm"));

  return rv;
  }


void ToolStatus::toolChanged(const QVariant& toolNum) {
  const ToolEntry* te = Core().toolTable().tool(toolNum.toInt());

  if (!te) return;
  qDebug() << "> ToolInfoDockable::toolChanged(" << toolNum << ")";
  te->dump();
  qDebug() << "< ToolInfoDockable::toolChanged(" << toolNum << ")";
  curTool->setValue(toolNum);
  tlLen->setValue(tr("L: %1").arg(te->length()));
  tlRad->setValue(tr("D: %1").arg(te->diameter() / 2.0));
  tlDesc->setText(te->description());
  }


void ToolStatus::connectSignals() {
  ValueManager vm;
  Config       cfg;

  curTool->label()->setStyleSheet("background: white; ");
  connect(vm.getModel("toolInSpindle", 0),  &ValueModel::valueChanged
        , this, &ToolStatus::toolChanged);
  connect(vm.getModel("pocketPrepared", 0),  &ValueModel::valueChanged
        , nxtTool, [=](){ nxtTool->label()->setNum(ValueManager().getValue("pocketPrepared").toInt()); });

  connect(vm.getModel(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolNum), QColor(Qt::white))
        , &ValueModel::valueChanged
        , curTool
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolNum)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolNum)).value<QColor>().rgba(), 0, 16);
                 curTool->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolNum), QColor(Qt::black))
        , &ValueModel::valueChanged
        , curTool
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolNum)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolNum)).value<QColor>().rgba(), 0, 16);
                 curTool->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF") + cfg.nameOf(Config::GuiElem::ToolNum), curTool->label()->font())
        , &ValueModel::valueChanged
        , curTool
        , [=](){ QFont font = ValueManager().getValue(QString("cfgF") + cfg.nameOf(Config::GuiElem::ToolNum)).value<QFont>();

                 curTool->label()->setFont(font);
                 });
  connect(vm.getModel(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolNext), QColor(Qt::white))
        , &ValueModel::valueChanged
        , nxtTool
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolNext)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolNext)).value<QColor>().rgba(), 0, 16);
                 nxtTool->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolNext), QColor(Qt::black))
        , &ValueModel::valueChanged
        , nxtTool
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolNext)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolNext)).value<QColor>().rgba(), 0, 16);
                 nxtTool->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF") + cfg.nameOf(Config::GuiElem::ToolNext), nxtTool->label()->font())
        , &ValueModel::valueChanged
        , nxtTool
        , [=](){ QFont font = ValueManager().getValue(QString("cfgF") + cfg.nameOf(Config::GuiElem::ToolNext)).value<QFont>();

                 nxtTool->label()->setFont(font);
                 });
  connect(vm.getModel(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolDesc), QColor(Qt::white))
        , &ValueModel::valueChanged
        , tlDesc
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgba(), 0, 16);
                 tlDesc->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolDesc), QColor(Qt::black))
        , &ValueModel::valueChanged
        , tlDesc
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgba(), 0, 16);
                 tlDesc->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF") + cfg.nameOf(Config::GuiElem::ToolDesc), tlDesc->font())
        , &ValueModel::valueChanged
        , tlDesc
        , [=](){ QFont font = ValueManager().getValue(QString("cfgF") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QFont>();

                 tlDesc->setFont(font);
                 });
  connect(vm.getModel(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolDesc), QColor(Qt::white))
        , &ValueModel::valueChanged
        , tlLen->label()
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgba(), 0, 16);
                 tlLen->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolDesc), QColor(Qt::black))
        , &ValueModel::valueChanged
        , tlLen->label()
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgba(), 0, 16);
                 tlLen->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF") + cfg.nameOf(Config::GuiElem::ToolDesc), tlLen->label()->font())
        , &ValueModel::valueChanged
        , tlLen->label()
        , [=](){ QFont font = ValueManager().getValue(QString("cfgF") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QFont>();

                 tlLen->label()->setFont(font);
                 });
  connect(vm.getModel(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolDesc), QColor(Qt::white))
        , &ValueModel::valueChanged
        , tlRad->label()
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgba(), 0, 16);
                 tlRad->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolDesc), QColor(Qt::black))
        , &ValueModel::valueChanged
        , tlRad->label()
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgba(), 0, 16);
                 tlRad->label()->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF") + cfg.nameOf(Config::GuiElem::ToolDesc), tlRad->label()->font())
        , &ValueModel::valueChanged
        , tlRad->label()
        , [=](){ QFont font = ValueManager().getValue(QString("cfgF") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QFont>();

                 tlRad->label()->setFont(font);
                 });
  }


void ToolStatus::updateStyles() {
  ValueManager vm;
  Config       cfg;

  curTool->label()->setStyleSheet(QString("color: #%1; background: #%2;")
                                 .arg(vm.getValue(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolNum)).value<QColor>().rgb(), 0, 16)
                                 .arg(vm.getValue(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolNum)).value<QColor>().rgba(), 0, 16));
  curTool->label()->setFont(vm.getValue(QString("cfgF") + cfg.nameOf(Config::GuiElem::ToolNum)).value<QFont>());
  nxtTool->label()->setStyleSheet(QString("color: #%1; background: #%2;")
                                 .arg(vm.getValue(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolNext)).value<QColor>().rgb(), 0, 16)
                                 .arg(vm.getValue(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolNext)).value<QColor>().rgba(), 0, 16));
  nxtTool->label()->setFont(vm.getValue(QString("cfgF") + cfg.nameOf(Config::GuiElem::ToolNext)).value<QFont>());
  QString style = QString("color: #%1; background: #%2;")
          .arg(vm.getValue(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgb(), 0, 16)
          .arg(vm.getValue(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgba(), 0, 16);
  QFont font = vm.getValue(QString("cfgF") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QFont>();

  tlDesc->setStyleSheet(style);
  tlDesc->setFont(font);
  tlLen->label()->setStyleSheet(style);
  tlLen->label()->setFont(font);
  tlRad->label()->setStyleSheet(style);
  tlRad->label()->setFont(font);
  }
