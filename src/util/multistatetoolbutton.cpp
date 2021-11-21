#include <multistatetoolbutton.h>
#include <valuemanager.h>
#include <valuemodel.h>
#include <QDebug>


MultiStateToolButton::MultiStateToolButton(ValueModel* vm, const QIcon& s0Icon, const QIcon& s1Icon, const QIcon& s2Icon, QWidget* parent)
 : QToolButton(parent)
 , model(vm)
 , s0Icon(s0Icon)
 , s1Icon(s1Icon)
 , s2Icon(s2Icon) {
  setIcon(this->s0Icon);
  connect(model, &ValueModel::valueChanged, this, &MultiStateToolButton::stateChanged);
  }


void MultiStateToolButton::stateChanged(const QVariant& state) {
  ValueManager vm;

  qDebug() << "\t<<<< ==========   MultiStateButton::stateChanged ... " << state;
  vm.getModel("allHomed")->dump();
  vm.getModel("taskState")->dump();
  vm.getModel("execState")->dump();
  vm.getModel("errorActive")->dump();

  switch (state.toInt()) {
    case 2:
    case 3:   setIcon(s1Icon); break;
    case 4:   setIcon(s2Icon); break;
    default:  setIcon(s0Icon); break;
    }
  }
