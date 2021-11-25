#ifndef FIXTUREEDIT_H
#define FIXTUREEDIT_H
#include <dyncenterwidget.h>
#include <ui_Fixture.h>
class QLineEdit;
class AxisMask;


class FixtureEdit : public DynCenterWidget // , protected Ui_frame
{
public:
  FixtureEdit(const QString& title, int ordinal, const AxisMask& mask, QWidget* parent = nullptr);

  virtual void connectSignals() override;
  virtual void updateStyles()   override;

protected:
  virtual void keyReleaseEvent(QKeyEvent* event) override;
  virtual void changeEvent(QEvent* event) override;
  virtual bool focusNextPrevChild(bool next) override;
  virtual QWidget* createContent() override;
  void saveFixture();
  void setupUi(DynCenterWidget* parent);

private:
  Ui::frame*        ui;
  int               ordinal;
  QList<QLineEdit*> edits;
  const AxisMask&   m;
  };
#endif // FIXTUREEDIT_H
