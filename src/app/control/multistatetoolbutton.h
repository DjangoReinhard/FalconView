#ifndef MULTISTATEBUTTON_H
#define MULTISTATEBUTTON_H
#include <QToolButton>
#include <QObject>
class ValueModel;


class MultiStateToolButton : public QToolButton
{
  Q_OBJECT
public:
  MultiStateToolButton(ValueModel* vm, const QIcon& s0Icon, const QIcon& s1Icon, const QIcon& s2Icon, QWidget* parent = nullptr);

protected slots:
  void          stateChanged(const QVariant& state);

private:
  ValueModel*  model;
  const QIcon& s0Icon;
  const QIcon& s1Icon;
  const QIcon& s2Icon;
  };

#endif // MULTISTATEBUTTON_H
