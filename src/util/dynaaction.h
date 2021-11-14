#ifndef DYNAACTION_H
#define DYNAACTION_H
#include <QAction>
class AbstractCondition;


class DynaAction : public QAction
{
  Q_OBJECT
public:
  explicit DynaAction(const QIcon& ico, const QString& text, AbstractCondition* cEnabled, AbstractCondition* cChecked, QObject *parent = nullptr);

public slots:
  void setEnabled(bool enabled);
  void setChecked(bool checked);

private:
  AbstractCondition* cEnabled;
  AbstractCondition* cChecked;
  };
#endif // DYNAACTION_H
