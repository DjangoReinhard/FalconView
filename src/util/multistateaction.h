#ifndef MYWIDGETACTION_H
#define MYWIDGETACTION_H
#include <QWidgetAction>
class ValueModel;


class MultiStateAction : public QWidgetAction
{
  Q_OBJECT
public:
  MultiStateAction(ValueModel* vm, const QIcon& s0Icon, const QIcon& s1Icon, const QIcon& s2Icon, QWidget* parent = nullptr);

  QWidget* createWidget(QWidget* parent) override;

private:
  ValueModel* model;
  QIcon       s0Icon;
  QIcon       s1Icon;
  QIcon       s2Icon;
  };
#endif // MYWIDGETACTION_H
