#include <dynaaction.h>
#include <abstractcondition.h>
#include <QDebug>


DynaAction::DynaAction(const QIcon& ico, const QString& text, AbstractCondition* cEnabled, AbstractCondition* cChecked, QObject *parent)
 : QAction(ico, text, parent)
 , cEnabled(cEnabled)
 , cChecked(cChecked) {
  connect(cEnabled, &AbstractCondition::conditionChanged, this, &DynaAction::setEnabled);
  connect(cChecked, &AbstractCondition::conditionChanged, this, &DynaAction::setChecked);
  setEnabled(cEnabled->result());
  setChecked(cChecked->result());
  }


void DynaAction::setEnabled(bool enabled) {
//  qDebug() << "DA[" << text() << "]: setEnabled(" << (enabled ? "ON" : "OFF") << ")";
  QAction::setEnabled(enabled);
  }


void DynaAction::setChecked(bool checked) {
//  qDebug() << "DA[" << text() << "]: setChecked(" << (checked ? "YES" : "NO") << ")";
  QAction::setChecked(checked);
  }
