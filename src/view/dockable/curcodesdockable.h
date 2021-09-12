#ifndef CURCODESDOCKABLE_H
#define CURCODESDOCKABLE_H
#include <dockable.h>
class QWidget;
class QLabel;

class CurCodesDockable : public Dockable
{
  Q_OBJECT
public:
  CurCodesDockable(const QString& fileName, QWidget* parent = nullptr);

protected:
  void connectSignals();
  void updateStyles();

private:
  QLabel** labels;
  };
#endif // CURCODESDOCKABLE_H
