#ifndef FIXTUREEDIT_H
#define FIXTUREEDIT_H
#include <dynwidget.h>


class FixtureEdit : public DynWidget
{
public:
  FixtureEdit(const QString& title, const QString& fileName, QWidget* parent = nullptr);

  virtual void connectSignals() override;
  virtual void updateStyles()   override;
  };
#endif // FIXTUREEDIT_H
