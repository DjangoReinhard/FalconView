#ifndef FIXTUREEDIT_H
#define FIXTUREEDIT_H
#include <dynwidget.h>
#include <ui_Fixture.h>
class QLineEdit;
class AxisMask;


class FixtureEdit : public DynWidget // , protected Ui_frame
{
public:
  FixtureEdit(const QString& title, const AxisMask& mask, QWidget* parent = nullptr);

  virtual void connectSignals() override;
  virtual void updateStyles()   override;

protected:
  virtual void focusInEvent(QFocusEvent *event) override;
  virtual void focusOutEvent(QFocusEvent *event) override;
  virtual void keyReleaseEvent(QKeyEvent* event) override;
  virtual void changeEvent(QEvent* event) override;
  void saveFixture();
  void setupUi(DynWidget* parent);

private:
  Ui::frame*        ui;
  QList<QLineEdit*> edits;
  const AxisMask&   m;
  };
#endif // FIXTUREEDIT_H
