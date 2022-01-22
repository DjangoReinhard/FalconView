#include <dynaaction.h>
#include <abstractcondition.h>
#include <QDebug>


DynaAction::DynaAction(const QIcon& disIco, const QIcon& enIco, const QIcon& cIco, const QString& text, AbstractCondition* cEnabled, AbstractCondition* cChecked, QObject *parent)
 : QAction(disIco, text, parent)
 , cEnabled(cEnabled)
 , cChecked(cChecked)
 , disabledIcon(disIco)
 , enabledIcon(enIco)
 , checkedIcon(cIco) {
  setObjectName("DynaAction");
  if (cEnabled) {
     connect(cEnabled, &AbstractCondition::conditionChanged, this, &DynaAction::setEnabled);
     setEnabled(cEnabled->result());
     }
  if (cChecked) {
     connect(cChecked, &AbstractCondition::conditionChanged, this, &DynaAction::setChecked);
     setChecked(cChecked->result());
     }
  }


void DynaAction::setEnabled(bool enabled) {
//  qDebug() << "DA[" << text() << "]: setEnabled(" << (enabled ? "ON" : "OFF") << ")";
  if (enabled) {
//     setChecked(cChecked->result());
     QAction::setIcon(enabledIcon);
     QAction::setEnabled(enabled);
     }
  else {
     QAction::setIcon(disabledIcon);
     QAction::setEnabled(enabled);
     }
  }


void DynaAction::setChecked(bool checked) {
//  qDebug() << "DA[" << text() << "]: setChecked(" << (checked ? "YES" : "NO") << ")";
  if (checked) {
     QAction::setIcon(checkedIcon);
     QAction::setChecked(checked);
     }
  else {
     QAction::setIcon(enabledIcon);
     QAction::setChecked(checked);
     }
//  qDebug() << "DA[" << text() << "]: is checked(" << (checked ? "YES" : "NO") << ")";
  }
