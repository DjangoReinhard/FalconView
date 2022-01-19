#include "toolstatus.h"
#include <valuemanager.h>
#include <configacc.h>
#include <guicore.h>
//#include <tooltable.h>
#include <QGridLayout>
#include <QFile>
#include <QLabel>
#include <QResizeEvent>
#include <QDebug>


ToolStatus::ToolStatus(QWidget* parent)
 : AbstractCenterWidget(":/src/statusInfo/ToolInfo/ToolInfo.ui", parent)
 , isInPreview(false)
 , curTool(nullptr)
 , nxtTool(nullptr) {
  setObjectName("ToolStatus");
  setWindowTitle(tr("ToolStatus"));
  setFocusPolicy(Qt::FocusPolicy::NoFocus);
  }


ToolStatus::~ToolStatus() {
  }


QWidget* ToolStatus::createContent() {
  QWidget*     rv = AbstractCenterWidget::createContent();
  QGridLayout* gl = static_cast<QGridLayout*>(rv->layout());

  tDesc   = findChild<QLabel*>("toolDesc");
  tLen    = findChild<QLabel*>("toolLen");
  tRad    = findChild<QLabel*>("toolRadius");
  tPic    = findChild<QLabel*>("toolPic");
  curTool = findChild<QLabel*>("curToolNum");
  nxtTool = findChild<QLabel*>("nextToolNum");

  if (isInPreview && gl) {
     gl->removeWidget(curTool);
     gl->addWidget(curTool, 0, 1);
     gl->removeWidget(tRad);
     gl->addWidget(tRad, 0, 3);
     gl->removeWidget(nxtTool);
     gl->addWidget(nxtTool, 0, 4);
     gl->removeWidget(tDesc);
     gl->addWidget(tDesc, 1, 1, 3, 4);
     }
  return rv;
  }


void ToolStatus::toolChanged(const QVariant& toolNum) {
//  const ToolEntry* te = core->toolTable().tool(toolNum.toInt());

//  if (!te) return;
//  curTool->setNum(toolNum.toInt());
//  tLen->setText(tr("L: %1").arg(core->locale().toString(te->length(), 'f', 3)));
//  tRad->setText(tr("R: %1").arg(core->locale().toString(te->diameter() / 2.0, 'f', 3)));
//  tPic->setPixmap(te->icon());
//  tDesc->setText(te->description());
  }


void ToolStatus::connectSignals() {
  connect(vm->getModel("toolInSpindle", 0),  &ValueModel::valueChanged, this, &ToolStatus::toolChanged);
  connect(vm->getModel("pocketPrepared", 0),  &ValueModel::valueChanged, nxtTool, [=](const QVariant& v){ nxtTool->setNum(v.toInt()); });

  connect(vm->getModel(QString("cfgBg") + cfg->nameOf(Config::GuiElem::ToolNum), QColor(Qt::white))
        , &ValueModel::valueChanged
        , curTool
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(vm->getValue(QString("cfgFg") + cfg->nameOf(Config::GuiElem::ToolNum)).value<QColor>().rgb(), 0, 16)
                                      .arg(vm->getValue(QString("cfgBg") + cfg->nameOf(Config::GuiElem::ToolNum)).value<QColor>().rgba(), 0, 16);
                 curTool->setStyleSheet(arg);
                 });
  connect(vm->getModel(QString("cfgFg") + cfg->nameOf(Config::GuiElem::ToolNum), QColor(Qt::black))
        , &ValueModel::valueChanged
        , curTool
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(vm->getValue(QString("cfgFg") + cfg->nameOf(Config::GuiElem::ToolNum)).value<QColor>().rgb(), 0, 16)
                                      .arg(vm->getValue(QString("cfgBg") + cfg->nameOf(Config::GuiElem::ToolNum)).value<QColor>().rgba(), 0, 16);
                 curTool->setStyleSheet(arg);
                 });
  connect(vm->getModel(QString("cfgF") + cfg->nameOf(Config::GuiElem::ToolNum), curTool->font())
        , &ValueModel::valueChanged
        , curTool
        , [=](){ QFont font = vm->getValue(QString("cfgF") + cfg->nameOf(Config::GuiElem::ToolNum)).value<QFont>();

                 curTool->setFont(font);
                 });
  connect(vm->getModel(QString("cfgBg") + cfg->nameOf(Config::GuiElem::ToolNext), QColor(Qt::white))
        , &ValueModel::valueChanged
        , nxtTool
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(vm->getValue(QString("cfgFg") + cfg->nameOf(Config::GuiElem::ToolNext)).value<QColor>().rgb(), 0, 16)
                                      .arg(vm->getValue(QString("cfgBg") + cfg->nameOf(Config::GuiElem::ToolNext)).value<QColor>().rgba(), 0, 16);
                 nxtTool->setStyleSheet(arg);
                 });
  connect(vm->getModel(QString("cfgFg") + cfg->nameOf(Config::GuiElem::ToolNext), QColor(Qt::black))
        , &ValueModel::valueChanged
        , nxtTool
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(vm->getValue(QString("cfgFg") + cfg->nameOf(Config::GuiElem::ToolNext)).value<QColor>().rgb(), 0, 16)
                                      .arg(vm->getValue(QString("cfgBg") + cfg->nameOf(Config::GuiElem::ToolNext)).value<QColor>().rgba(), 0, 16);
                 nxtTool->setStyleSheet(arg);
                 });
  connect(vm->getModel(QString("cfgF") + cfg->nameOf(Config::GuiElem::ToolNext), nxtTool->font())
        , &ValueModel::valueChanged
        , nxtTool
        , [=](){ QFont font = vm->getValue(QString("cfgF") + cfg->nameOf(Config::GuiElem::ToolNext)).value<QFont>();

                 nxtTool->setFont(font);
                 });
  connect(vm->getModel(QString("cfgBg") + cfg->nameOf(Config::GuiElem::ToolDesc), QColor(Qt::white))
        , &ValueModel::valueChanged
        , tDesc
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(vm->getValue(QString("cfgFg") + cfg->nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgb(), 0, 16)
                                      .arg(vm->getValue(QString("cfgBg") + cfg->nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgba(), 0, 16);
                 tDesc->setStyleSheet(arg);
                 });
  connect(vm->getModel(QString("cfgFg") + cfg->nameOf(Config::GuiElem::ToolDesc), QColor(Qt::black))
        , &ValueModel::valueChanged
        , tDesc
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(vm->getValue(QString("cfgFg") + cfg->nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgb(), 0, 16)
                                      .arg(vm->getValue(QString("cfgBg") + cfg->nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgba(), 0, 16);
                 tDesc->setStyleSheet(arg);
                 });
  connect(vm->getModel(QString("cfgF") + cfg->nameOf(Config::GuiElem::ToolDesc), tDesc->font())
        , &ValueModel::valueChanged
        , tDesc
        , [=](){ QFont font = vm->getValue(QString("cfgF") + cfg->nameOf(Config::GuiElem::ToolDesc)).value<QFont>();

                 tDesc->setFont(font);
                 });
  connect(vm->getModel(QString("cfgBg") + cfg->nameOf(Config::GuiElem::ToolDesc), QColor(Qt::white))
        , &ValueModel::valueChanged
        , tLen
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(vm->getValue(QString("cfgFg") + cfg->nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgb(), 0, 16)
                                      .arg(vm->getValue(QString("cfgBg") + cfg->nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgba(), 0, 16);
                 tLen->setStyleSheet(arg);
                 });
  connect(vm->getModel(QString("cfgFg") + cfg->nameOf(Config::GuiElem::ToolDesc), QColor(Qt::black))
        , &ValueModel::valueChanged
        , tLen
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(vm->getValue(QString("cfgFg") + cfg->nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgb(), 0, 16)
                                      .arg(vm->getValue(QString("cfgBg") + cfg->nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgba(), 0, 16);
                 tLen->setStyleSheet(arg);
                 });
  connect(vm->getModel(QString("cfgF") + cfg->nameOf(Config::GuiElem::ToolDesc), tLen->font())
        , &ValueModel::valueChanged
        , tLen
        , [=](){ QFont font = vm->getValue(QString("cfgF") + cfg->nameOf(Config::GuiElem::ToolDesc)).value<QFont>();

                 tLen->setFont(font);
                 });
  connect(vm->getModel(QString("cfgBg") + cfg->nameOf(Config::GuiElem::ToolDesc), QColor(Qt::white))
        , &ValueModel::valueChanged
        , tRad
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(vm->getValue(QString("cfgFg") + cfg->nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgb(), 0, 16)
                                      .arg(vm->getValue(QString("cfgBg") + cfg->nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgba(), 0, 16);
                 tRad->setStyleSheet(arg);
                 });
  connect(vm->getModel(QString("cfgFg") + cfg->nameOf(Config::GuiElem::ToolDesc), QColor(Qt::black))
        , &ValueModel::valueChanged
        , tRad
        , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                      .arg(vm->getValue(QString("cfgFg") + cfg->nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgb(), 0, 16)
                                      .arg(vm->getValue(QString("cfgBg") + cfg->nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgba(), 0, 16);
                 tRad->setStyleSheet(arg);
                 });
  connect(vm->getModel(QString("cfgF") + cfg->nameOf(Config::GuiElem::ToolDesc), tRad->font())
        , &ValueModel::valueChanged
        , tRad
        , [=](){ QFont font = vm->getValue(QString("cfgF") + cfg->nameOf(Config::GuiElem::ToolDesc)).value<QFont>();

                 tRad->setFont(font);
                 });
  }


void ToolStatus::updateStyles() {
  curTool->setStyleSheet(QString("color: #%1; background: #%2;")
                                 .arg(vm->getValue(QString("cfgFg") + cfg->nameOf(Config::GuiElem::ToolNum)).value<QColor>().rgb(), 0, 16)
                                 .arg(vm->getValue(QString("cfgBg") + cfg->nameOf(Config::GuiElem::ToolNum)).value<QColor>().rgba(), 0, 16));
  curTool->setFont(vm->getValue(QString("cfgF") + cfg->nameOf(Config::GuiElem::ToolNum)).value<QFont>());
  nxtTool->setStyleSheet(QString("color: #%1; background: #%2;")
                                 .arg(vm->getValue(QString("cfgFg") + cfg->nameOf(Config::GuiElem::ToolNext)).value<QColor>().rgb(), 0, 16)
                                 .arg(vm->getValue(QString("cfgBg") + cfg->nameOf(Config::GuiElem::ToolNext)).value<QColor>().rgba(), 0, 16));
  nxtTool->setFont(vm->getValue(QString("cfgF") + cfg->nameOf(Config::GuiElem::ToolNext)).value<QFont>());
  QString style = QString("color: #%1; background: #%2;")
          .arg(vm->getValue(QString("cfgFg") + cfg->nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgb(), 0, 16)
          .arg(vm->getValue(QString("cfgBg") + cfg->nameOf(Config::GuiElem::ToolDesc)).value<QColor>().rgba(), 0, 16);
  QFont font = vm->getValue(QString("cfgF") + cfg->nameOf(Config::GuiElem::ToolDesc)).value<QFont>();

  tDesc->setStyleSheet(style);
  tDesc->setFont(font);
  tLen->setStyleSheet(style);
  tLen->setFont(font);
  tRad->setStyleSheet(style);
  tRad->setFont(font);
  }
