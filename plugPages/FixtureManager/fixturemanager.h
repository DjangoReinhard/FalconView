#ifndef FIXTUREMANAGER_H
#define FIXTUREMANAGER_H
#include <abscenterwidget.h>

QT_BEGIN_NAMESPACE
class FixtureEdit;
class AxisMask;
QT_END_NAMESPACE


class FixtureManager : public AbstractCenterWidget
{
  Q_OBJECT
public:
  FixtureManager(const AxisMask& mask, QWidget* parent = nullptr);

  virtual void connectSignals() override;
  virtual void updateStyles()   override;
  void activateEditor(int index);

protected:
  virtual void keyPressEvent(QKeyEvent* event) override;
  virtual void showEvent(QShowEvent *event) override;
//  virtual void resizeEvent(QResizeEvent *event) override;
  virtual QWidget* createContent() override;

private:
  QWidget*            client;
  QFont               cFonts[4];
  QString             cStyle[4];
  const AxisMask&     axisMask;
  };
#endif // FIXTUREMANAGER_H
