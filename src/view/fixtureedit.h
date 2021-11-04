#ifndef FIXTUREEDIT_H
#define FIXTUREEDIT_H
#include <dynwidget.h>
#include <ui_Fixture.h>
class QLineEdit;


class FixtureEdit : public DynWidget // , protected Ui_frame
{
public:
  FixtureEdit(const QString& title, QWidget* parent = nullptr);

  virtual void connectSignals() override;
  virtual void updateStyles()   override;

protected:
  virtual void keyReleaseEvent(QKeyEvent *event) override;

private:
  Ui::frame* ui;
  };
#endif // FIXTUREEDIT_H
