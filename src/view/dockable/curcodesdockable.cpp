#include <curcodesdockable.h>
#include <valuemanager.h>
#include <configacc.h>
#include <QLabel>
#include <QColor>
#include <QFont>


CurCodesDockable::CurCodesDockable(const QString& fileName, QWidget* parent)
 : Dockable(fileName, tr("actual Codes"), parent)
 , labels(nullptr) {
  labels = new QLabel*[28];
  labels[0] = findChild<QLabel*>("g1");
  labels[1] = findChild<QLabel*>("g2");
  labels[2] = findChild<QLabel*>("g3");
  labels[3] = findChild<QLabel*>("g4");
  labels[4] = findChild<QLabel*>("g5");
  labels[5] = findChild<QLabel*>("g6");
  labels[6] = findChild<QLabel*>("g7");
  labels[7] = findChild<QLabel*>("g8");
  labels[8] = findChild<QLabel*>("g10");
  labels[9] = findChild<QLabel*>("g11");
  labels[10] = findChild<QLabel*>("g12");
  labels[11] = findChild<QLabel*>("g13");
  labels[12] = findChild<QLabel*>("g14");
  labels[13] = findChild<QLabel*>("g15");
  labels[14] = findChild<QLabel*>("g16");
  labels[15] = findChild<QLabel*>("m4");
  labels[16] = findChild<QLabel*>("m7");
  labels[17] = findChild<QLabel*>("m8");
  labels[18] = findChild<QLabel*>("m9");
  labels[19] = findChild<QLabel*>("m10");

  setFocusPolicy(Qt::FocusPolicy::NoFocus);
  connectSignals();
  updateStyles();
  }


void CurCodesDockable::connectSignals() {
  ValueManager vm;

  connect(vm.getModel("GC1", " "), &ValueModel::valueChanged,  labels[0],  [=](QVariant arg){ labels[0]->setText(arg.toString()); });
  connect(vm.getModel("GC2", " "), &ValueModel::valueChanged,  labels[1],  [=](QVariant arg){ labels[1]->setText(arg.toString()); });
  connect(vm.getModel("GC3", " "), &ValueModel::valueChanged,  labels[2],  [=](QVariant arg){ labels[2]->setText(arg.toString()); });
  connect(vm.getModel("GC4", " "), &ValueModel::valueChanged,  labels[3],  [=](QVariant arg){ labels[3]->setText(arg.toString()); });
  connect(vm.getModel("GC5", " "), &ValueModel::valueChanged,  labels[4],  [=](QVariant arg){ labels[4]->setText(arg.toString()); });
  connect(vm.getModel("GC6", " "), &ValueModel::valueChanged,  labels[5],  [=](QVariant arg){ labels[5]->setText(arg.toString()); });
  connect(vm.getModel("GC7", " "), &ValueModel::valueChanged,  labels[6],  [=](QVariant arg){ labels[6]->setText(arg.toString()); });
  connect(vm.getModel("GC8", " "), &ValueModel::valueChanged,  labels[7],  [=](QVariant arg){ labels[7]->setText(arg.toString()); });
  connect(vm.getModel("GC10", " "), &ValueModel::valueChanged, labels[8],  [=](QVariant arg){ labels[8]->setText(arg.toString()); });
  connect(vm.getModel("GC11", " "), &ValueModel::valueChanged, labels[9],  [=](QVariant arg){ labels[9]->setText(arg.toString()); });
  connect(vm.getModel("GC12", " "), &ValueModel::valueChanged, labels[10], [=](QVariant arg){ labels[10]->setText(arg.toString()); });
  connect(vm.getModel("GC13", " "), &ValueModel::valueChanged, labels[11], [=](QVariant arg){ labels[11]->setText(arg.toString()); });
  connect(vm.getModel("GC14", " "), &ValueModel::valueChanged, labels[12], [=](QVariant arg){ labels[12]->setText(arg.toString()); });
  connect(vm.getModel("GC15", " "), &ValueModel::valueChanged, labels[13], [=](QVariant arg){ labels[13]->setText(arg.toString()); });
  connect(vm.getModel("GC16", " "), &ValueModel::valueChanged, labels[14], [=](QVariant arg){ labels[14]->setText(arg.toString()); });
  connect(vm.getModel("MC4", " "), &ValueModel::valueChanged,  labels[15], [=](QVariant arg){ labels[15]->setText(arg.toString()); });
  connect(vm.getModel("MC7", " "), &ValueModel::valueChanged,  labels[16], [=](QVariant arg){ labels[16]->setText(arg.toString()); });
  connect(vm.getModel("MC8", " "), &ValueModel::valueChanged,  labels[17], [=](QVariant arg){ labels[17]->setText(arg.toString()); });
  connect(vm.getModel("MC9", " "), &ValueModel::valueChanged,  labels[18], [=](QVariant arg){ labels[18]->setText(arg.toString()); });
  connect(vm.getModel("MC10", " "), &ValueModel::valueChanged, labels[19], [=](QVariant arg){ labels[19]->setText(arg.toString()); });
  Config  cfg;
  QString keyBg  = QString("cfgBg" + cfg.nameOf(Config::GuiElem::ActCodes));
  QString keyFg  = QString("cfgFg" + cfg.nameOf(Config::GuiElem::ActCodes));
  QString keyF   = QString("cfgF"  + cfg.nameOf(Config::GuiElem::ActCodes));
  QString mask   = QString("color: #%1; background: #%2;");

  for (int i=0; i < 20; ++i) {
      connect(vm.getModel(keyBg, QColor(Qt::white))
            , &ValueModel::valueChanged
            , labels[i]
            , [=](){ QString arg = QString(mask)
                                          .arg(ValueManager().getValue(keyFg).value<QColor>().rgb(), 0, 16)
                                          .arg(ValueManager().getValue(keyBg).value<QColor>().rgba(), 0, 16);
                     labels[i]->setStyleSheet(arg);
                     });
      connect(vm.getModel(keyFg, QColor(Qt::black)), &ValueModel::valueChanged
            , labels[i], [=](){ QString arg = QString(mask)
                                              .arg(ValueManager().getValue(keyFg).value<QColor>().rgb(), 0, 16)
                                              .arg(ValueManager().getValue(keyBg).value<QColor>().rgba(), 0, 16);
                         labels[i]->setStyleSheet(arg);
                         });
      connect(vm.getModel(keyF, labels[i]->font()), &ValueModel::valueChanged
            , labels[i], [=](){ labels[i]->setFont(ValueManager().getValue(keyF).value<QFont>()); });
      }
  }


void CurCodesDockable::updateStyles() {
  Config  cfg;
  QString styles = QString("color: #%1; background: #%2;")
                          .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(Config::GuiElem::ActCodes)).value<QColor>().rgb(),  0, 16)
                          .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(Config::GuiElem::ActCodes)).value<QColor>().rgba(), 0, 16);
  QFont font = ValueManager().getValue("cfgF" + cfg.nameOf(Config::GuiElem::ActCodes)).value<QFont>();

  for (int i=0; i < 20; ++i) {
      labels[i]->setStyleSheet(styles);
      labels[i]->setFont(font);
      }
  }
