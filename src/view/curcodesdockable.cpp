#include <curcodesdockable.h>
#include <valuemanager.h>
#include <QLabel>


CurCodesDockable::CurCodesDockable(const QString& fileName, QWidget* parent)
 : Dockable(fileName, tr("actual Codes"), parent)
 , g0(nullptr)
 , g1(nullptr)
 , g2(nullptr)
 , g3(nullptr)
 , g4(nullptr)
 , g5(nullptr)
 , g6(nullptr)
 , g7(nullptr)
 , g8(nullptr)
 , g9(nullptr)
 , g10(nullptr)
 , g11(nullptr)
 , g12(nullptr)
 , g13(nullptr)
 , g14(nullptr)
 , g15(nullptr)
 , g16(nullptr)
 , m0(nullptr)
 , m1(nullptr)
 , m2(nullptr)
 , m3(nullptr)
 , m4(nullptr)
 , m5(nullptr)
 , m6(nullptr)
 , m7(nullptr)
 , m8(nullptr)
 , m9(nullptr)
{
  g0  = findChild<QLabel*>("g0");
  g1  = findChild<QLabel*>("g1");
  g2  = findChild<QLabel*>("g2");
  g3  = findChild<QLabel*>("g3");
  g4  = findChild<QLabel*>("g4");
  g5  = findChild<QLabel*>("g5");
  g6  = findChild<QLabel*>("g6");
  g7  = findChild<QLabel*>("g7");
  g8  = findChild<QLabel*>("g8");
  g9  = findChild<QLabel*>("g9");
  g10 = findChild<QLabel*>("g10");
  g11 = findChild<QLabel*>("g11");
  g12 = findChild<QLabel*>("g12");
  g13 = findChild<QLabel*>("g13");
  g14 = findChild<QLabel*>("g14");
  g15 = findChild<QLabel*>("g15");
  g16 = findChild<QLabel*>("g16");
  m0  = findChild<QLabel*>("m0");
  m1  = findChild<QLabel*>("m1");
  m2  = findChild<QLabel*>("m2");
  m3  = findChild<QLabel*>("m3");
  m4  = findChild<QLabel*>("m4");
  m5  = findChild<QLabel*>("m5");
  m6  = findChild<QLabel*>("m6");
  m7  = findChild<QLabel*>("m7");
  m8  = findChild<QLabel*>("m8");
  m9  = findChild<QLabel*>("m9");

  connectLabels();
  }


void CurCodesDockable::connectLabels() {
  ValueManager vm;

  connect(vm.getModel("GC0", " "), &ValueModel::valueChanged,  g0,  [=](QVariant arg){ g0->setText(arg.toString()); });
  connect(vm.getModel("GC1", " "), &ValueModel::valueChanged,  g1,  [=](QVariant arg){ g1->setText(arg.toString()); });
  connect(vm.getModel("GC2", " "), &ValueModel::valueChanged,  g2,  [=](QVariant arg){ g2->setText(arg.toString()); });
  connect(vm.getModel("GC3", " "), &ValueModel::valueChanged,  g3,  [=](QVariant arg){ g3->setText(arg.toString()); });
  connect(vm.getModel("GC4", " "), &ValueModel::valueChanged,  g4,  [=](QVariant arg){ g4->setText(arg.toString()); });
  connect(vm.getModel("GC5", " "), &ValueModel::valueChanged,  g5,  [=](QVariant arg){ g5->setText(arg.toString()); });
  connect(vm.getModel("GC6", " "), &ValueModel::valueChanged,  g6,  [=](QVariant arg){ g6->setText(arg.toString()); });
  connect(vm.getModel("GC7", " "), &ValueModel::valueChanged,  g7,  [=](QVariant arg){ g7->setText(arg.toString()); });
  connect(vm.getModel("GC8", " "), &ValueModel::valueChanged,  g8,  [=](QVariant arg){ g8->setText(arg.toString()); });
  connect(vm.getModel("GC9", " "), &ValueModel::valueChanged,  g9,  [=](QVariant arg){ g9->setText(arg.toString()); });
  connect(vm.getModel("GC10", " "), &ValueModel::valueChanged, g10, [=](QVariant arg){ g10->setText(arg.toString()); });
  connect(vm.getModel("GC11", " "), &ValueModel::valueChanged, g11, [=](QVariant arg){ g11->setText(arg.toString()); });
  connect(vm.getModel("GC12", " "), &ValueModel::valueChanged, g12, [=](QVariant arg){ g12->setText(arg.toString()); });
  connect(vm.getModel("GC13", " "), &ValueModel::valueChanged, g13, [=](QVariant arg){ g13->setText(arg.toString()); });
  connect(vm.getModel("GC14", " "), &ValueModel::valueChanged, g14, [=](QVariant arg){ g14->setText(arg.toString()); });
  connect(vm.getModel("GC15", " "), &ValueModel::valueChanged, g15, [=](QVariant arg){ g15->setText(arg.toString()); });
  connect(vm.getModel("GC16", " "), &ValueModel::valueChanged, g16, [=](QVariant arg){ g16->setText(arg.toString()); });
  connect(vm.getModel("MC0", " "), &ValueModel::valueChanged, m0, [=](QVariant arg){ m0->setText(arg.toString()); });
  connect(vm.getModel("MC1", " "), &ValueModel::valueChanged, m1, [=](QVariant arg){ m1->setText(arg.toString()); });
  connect(vm.getModel("MC2", " "), &ValueModel::valueChanged, m2, [=](QVariant arg){ m2->setText(arg.toString()); });
  connect(vm.getModel("MC3", " "), &ValueModel::valueChanged, m3, [=](QVariant arg){ m3->setText(arg.toString()); });
  connect(vm.getModel("MC4", " "), &ValueModel::valueChanged, m4, [=](QVariant arg){ m4->setText(arg.toString()); });
  connect(vm.getModel("MC5", " "), &ValueModel::valueChanged, m5, [=](QVariant arg){ m5->setText(arg.toString()); });
  connect(vm.getModel("MC6", " "), &ValueModel::valueChanged, m6, [=](QVariant arg){ m6->setText(arg.toString()); });
  connect(vm.getModel("MC7", " "), &ValueModel::valueChanged, m7, [=](QVariant arg){ m7->setText(arg.toString()); });
  connect(vm.getModel("MC8", " "), &ValueModel::valueChanged, m8, [=](QVariant arg){ m8->setText(arg.toString()); });
  connect(vm.getModel("MC9", " "), &ValueModel::valueChanged, m9, [=](QVariant arg){ m9->setText(arg.toString()); });
  }
