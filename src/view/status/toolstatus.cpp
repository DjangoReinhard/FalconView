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
 , nxtTool(nullptr) {
  setFocusPolicy(Qt::FocusPolicy::NoFocus);
  setWindowTitle(tr("ToolStatus"));
  }


ToolStatus::~ToolStatus() {
  }


QWidget* ToolStatus::createContent() {
  QWidget* rv = DynCenterWidget::createContent();

  tDesc   = findChild<QLabel*>("toolDesc");
  tLen    = findChild<QLabel*>("toolLen");
  tRad    = findChild<QLabel*>("toolRadius");
  tPic    = findChild<QLabel*>("toolPic");
  curTool = new LabelAdapter(findChild<QLabel*>("curToolNum"), 0);
  nxtTool = new LabelAdapter(findChild<QLabel*>("nextToolNum"), 0);

  return rv;
  }


void ToolStatus::toolChanged(const QVariant& toolNum) {
  const ToolEntry* te = Core().toolTable().tool(toolNum.toInt());

  if (!te) return;
  qDebug() << "> ToolInfoDockable::toolChanged(" << toolNum << ")";
  te->dump();
  qDebug() << "< ToolInfoDockable::toolChanged(" << toolNum << ")";
  curTool->setValue(toolNum);
  tLen->setText(tr("L: %1").arg(Core().locale().toString(te->length(), 'f', 3)));
  tRad->setText(tr("R: %1").arg(Core().locale().toString(te->diameter() / 2.0, 'f', 3)));
  tPic->setPixmap(te->icon());
  tDesc->setText(te->description());
//  tDesc->setText(QString("<html><p>%1</p></html>").arg(te->description()));
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
        , tDesc
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgba(), 0, 16);
                 tDesc->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolDesc), QColor(Qt::black))
        , &ValueModel::valueChanged
        , tDesc
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgba(), 0, 16);
                 tDesc->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF") + cfg.nameOf(Config::GuiElem::ToolDesc), tDesc->font())
        , &ValueModel::valueChanged
        , tDesc
        , [=](){ QFont font = ValueManager().getValue(QString("cfgF") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QFont>();

                 tDesc->setFont(font);
                 });
  connect(vm.getModel(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolDesc), QColor(Qt::white))
        , &ValueModel::valueChanged
        , tLen
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgba(), 0, 16);
                 tLen->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolDesc), QColor(Qt::black))
        , &ValueModel::valueChanged
        , tLen
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgba(), 0, 16);
                 tLen->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF") + cfg.nameOf(Config::GuiElem::ToolDesc), tLen->font())
        , &ValueModel::valueChanged
        , tLen
        , [=](){ QFont font = ValueManager().getValue(QString("cfgF") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QFont>();

                 tLen->setFont(font);
                 });
  connect(vm.getModel(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolDesc), QColor(Qt::white))
        , &ValueModel::valueChanged
        , tRad
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgba(), 0, 16);
                 tRad->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolDesc), QColor(Qt::black))
        , &ValueModel::valueChanged
        , tRad
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(ValueManager().getValue(QString("cfgFg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgb(), 0, 16)
                                      .arg(ValueManager().getValue(QString("cfgBg") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgba(), 0, 16);
                 tRad->setStyleSheet(arg);
                 });
  connect(vm.getModel(QString("cfgF") + cfg.nameOf(Config::GuiElem::ToolDesc), tRad->font())
        , &ValueModel::valueChanged
        , tRad
        , [=](){ QFont font = ValueManager().getValue(QString("cfgF") + cfg.nameOf(Config::GuiElem::ToolDesc)).value<QFont>();

                 tRad->setFont(font);
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

  tDesc->setStyleSheet(style);
  tDesc->setFont(font);
  tLen->setStyleSheet(style);
  tLen->setFont(font);
  tRad->setStyleSheet(style);
  tRad->setFont(font);
  }
