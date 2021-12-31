#include <multistateaction.h>
#include <multistatetoolbutton.h>
#include <QPushButton>
#include <valuemodel.h>


MultiStateAction::MultiStateAction(ValueModel* vm, const QIcon& s0Icon, const QIcon& s1Icon, const QIcon& s2Icon, QWidget *parent)
 : QWidgetAction(parent)
 , model(vm)
 , s0Icon(s0Icon)
 , s1Icon(s1Icon)
 , s2Icon(s2Icon) {
  setIcon(s0Icon);
  setText("MultiStateFactoryAction");
  }


QWidget *MultiStateAction::createWidget(QWidget *parent) {
  QToolButton* tb = new MultiStateToolButton(model, s0Icon, s1Icon, s2Icon, parent);

  tb->setDefaultAction(this);

  return tb;
  }
