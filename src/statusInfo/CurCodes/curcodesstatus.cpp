#include "curcodesstatus.h"
#include <valuemanager.h>
#include <configacc.h>
#include <valuemodel.h>
#include <QLabel>
#include <QColor>
#include <QFont>
#include <QDebug>


CurCodesStatus::CurCodesStatus(QWidget* parent)
 : AbstractCenterWidget(QString(), parent)
 , isVertical(false)
 , labels(nullptr) {
  setObjectName("CurCodesStatus");
  setWindowTitle(tr("CurCodesStatus"));
  setFocusPolicy(Qt::FocusPolicy::NoFocus);
  }


QWidget* CurCodesStatus::createContent() {
  QWidget* w = AbstractCenterWidget::createContent();

  labels = new QLabel*[25];
  labels[0]  = findChild<QLabel*>("g1");
  labels[1]  = findChild<QLabel*>("g2");
  labels[2]  = findChild<QLabel*>("g3");
  labels[3]  = findChild<QLabel*>("g4");
  labels[4]  = findChild<QLabel*>("g5");
  labels[5]  = findChild<QLabel*>("g6");
  labels[6]  = findChild<QLabel*>("g7");
  labels[7]  = findChild<QLabel*>("g8");
  labels[8]  = findChild<QLabel*>("g9");
  labels[9]  = findChild<QLabel*>("g10");
  labels[10] = findChild<QLabel*>("g11");
  labels[11] = findChild<QLabel*>("g12");
  labels[12] = findChild<QLabel*>("g13");
  labels[13] = findChild<QLabel*>("g14");
  labels[14] = findChild<QLabel*>("g15");
  labels[15] = findChild<QLabel*>("g16");
  labels[16] = findChild<QLabel*>("m1");
  labels[17] = findChild<QLabel*>("m2");
  labels[18] = findChild<QLabel*>("m3");
  labels[19] = findChild<QLabel*>("m4");
  labels[20] = findChild<QLabel*>("m5");
  labels[21] = findChild<QLabel*>("m6");
  labels[22] = findChild<QLabel*>("m7");
  labels[23] = findChild<QLabel*>("m8");
  labels[24] = findChild<QLabel*>("m9");

  return w;
  }


void CurCodesStatus::connectSignals() {
  ValueModel*  m = vm->getModel("GC1", "-9");

  qDebug() << "\tCCStatus::connectSignals() ... GC1 has value:" << m->getValue();
  connect(vm->getModel("GC1", "1"),   &ValueModel::valueChanged, labels[0],  [=](const QVariant& arg){ labels[0]->setText(arg.toString()); });
  connect(vm->getModel("GC2", "2"),   &ValueModel::valueChanged, labels[1],  [=](const QVariant& arg){ labels[1]->setText(arg.toString()); });
  connect(vm->getModel("GC3", "3"),   &ValueModel::valueChanged, labels[2],  [=](const QVariant& arg){ labels[2]->setText(arg.toString()); });
  connect(vm->getModel("GC4", "4"),   &ValueModel::valueChanged, labels[3],  [=](const QVariant& arg){ labels[3]->setText(arg.toString()); });
  connect(vm->getModel("GC5", "5"),   &ValueModel::valueChanged, labels[4],  [=](const QVariant& arg){ labels[4]->setText(arg.toString()); });
  connect(vm->getModel("GC6", "6"),   &ValueModel::valueChanged, labels[5],  [=](const QVariant& arg){ labels[5]->setText(arg.toString()); });
  connect(vm->getModel("GC7", "7"),   &ValueModel::valueChanged, labels[6],  [=](const QVariant& arg){ labels[6]->setText(arg.toString()); });
  connect(vm->getModel("GC8", "8"),   &ValueModel::valueChanged, labels[7],  [=](const QVariant& arg){ labels[7]->setText(arg.toString()); });
  connect(vm->getModel("GC9", "9"),   &ValueModel::valueChanged, labels[8],  [=](const QVariant& arg){ labels[8]->setText(arg.toString()); });
  connect(vm->getModel("GC10", "10"), &ValueModel::valueChanged, labels[9],  [=](const QVariant& arg){ labels[9]->setText(arg.toString()); });
  connect(vm->getModel("GC11", "11"), &ValueModel::valueChanged, labels[10], [=](const QVariant& arg){ labels[10]->setText(arg.toString()); });
  connect(vm->getModel("GC12", "12"), &ValueModel::valueChanged, labels[11], [=](const QVariant& arg){ labels[11]->setText(arg.toString()); });
  connect(vm->getModel("GC13", "13"), &ValueModel::valueChanged, labels[12], [=](const QVariant& arg){ labels[12]->setText(arg.toString()); });
  connect(vm->getModel("GC14", "14"), &ValueModel::valueChanged, labels[13], [=](const QVariant& arg){ labels[13]->setText(arg.toString()); });
  connect(vm->getModel("GC15", "15"), &ValueModel::valueChanged, labels[14], [=](const QVariant& arg){ labels[14]->setText(arg.toString()); });
  connect(vm->getModel("GC16", "16"), &ValueModel::valueChanged, labels[15], [=](const QVariant& arg){ labels[15]->setText(arg.toString()); });
  connect(vm->getModel("MC1", "1"),   &ValueModel::valueChanged, labels[16], [=](const QVariant& arg){ labels[16]->setText(arg.toString()); });
  connect(vm->getModel("MC2", "2"),   &ValueModel::valueChanged, labels[17], [=](const QVariant& arg){ labels[17]->setText(arg.toString()); });
  connect(vm->getModel("MC3", "3"),   &ValueModel::valueChanged, labels[18], [=](const QVariant& arg){ labels[18]->setText(arg.toString()); });
  connect(vm->getModel("MC4", "4"),   &ValueModel::valueChanged, labels[19], [=](const QVariant& arg){ labels[19]->setText(arg.toString()); });
  connect(vm->getModel("MC5", "5"),   &ValueModel::valueChanged, labels[20], [=](const QVariant& arg){ labels[20]->setText(arg.toString()); });
  connect(vm->getModel("MC6", "6"),   &ValueModel::valueChanged, labels[21], [=](const QVariant& arg){ labels[21]->setText(arg.toString()); });
  connect(vm->getModel("MC7", "7"),   &ValueModel::valueChanged, labels[22], [=](const QVariant& arg){ labels[22]->setText(arg.toString()); });
  connect(vm->getModel("MC8", "8"),   &ValueModel::valueChanged, labels[23], [=](const QVariant& arg){ labels[23]->setText(arg.toString()); });
  connect(vm->getModel("MC9", "9"),   &ValueModel::valueChanged, labels[24], [=](const QVariant& arg){ labels[24]->setText(arg.toString()); });
  QString keyBg  = QString("cfgBg" + cfg->nameOf(Config::GuiElem::ActCodes));
  QString keyFg  = QString("cfgFg" + cfg->nameOf(Config::GuiElem::ActCodes));
  QString keyF   = QString("cfgF"  + cfg->nameOf(Config::GuiElem::ActCodes));
  QString mask   = QString("color: #%1; background: #%2;");

  for (int i=0; i < 25; ++i) {
      connect(vm->getModel(keyBg, QColor(Qt::white))
            , &ValueModel::valueChanged
            , labels[i]
            , [=](){ QString arg = QString(mask)
                                          .arg(vm->getValue(keyFg).value<QColor>().rgb(), 0, 16)
                                          .arg(vm->getValue(keyBg).value<QColor>().rgba(), 0, 16);
                     labels[i]->setStyleSheet(arg);
                     });
      connect(vm->getModel(keyFg, QColor(Qt::black)), &ValueModel::valueChanged
            , labels[i], [=](){ QString arg = QString(mask)
                                              .arg(vm->getValue(keyFg).value<QColor>().rgb(), 0, 16)
                                              .arg(vm->getValue(keyBg).value<QColor>().rgba(), 0, 16);
                         labels[i]->setStyleSheet(arg);
                         });
      connect(vm->getModel(keyF, labels[i]->font()), &ValueModel::valueChanged
            , labels[i], [=](){ labels[i]->setFont(vm->getValue(keyF).value<QFont>()); });
      }
  }


QString CurCodesStatus::fileName() const {
  if (isVertical) return ":/src/statusInfo/CurCodes/VCurCodes.ui";
  return ":/src/statusInfo/CurCodes/HCurCodes.ui";
  }


void CurCodesStatus::patch(void *pk, void *pc, void *pv, void* pu, bool flag) {
  AbstractCenterWidget::patch(pk, pc, pv, pu, flag);
  isVertical = flag;
  }


void CurCodesStatus::updateStyles() {
  QString styles = QString("color: #%1; background: #%2;")
                          .arg(vm->getValue("cfgFg" + cfg->nameOf(Config::GuiElem::ActCodes)).value<QColor>().rgb(),  0, 16)
                          .arg(vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::ActCodes)).value<QColor>().rgba(), 0, 16);
  QFont font = vm->getValue("cfgF" + cfg->nameOf(Config::GuiElem::ActCodes)).value<QFont>();

  for (int i=0; i < 25; ++i) {
      labels[i]->setStyleSheet(styles);
      labels[i]->setFont(font);
      }
  }
