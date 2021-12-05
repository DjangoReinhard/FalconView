#ifndef DYNDOCKABLE_H
#define DYNDOCKABLE_H
#include <QDockWidget>
class QString;
class QWidget;
class DynCenterWidget;


class DynDockable : public QDockWidget
{    
public:
  DynDockable(DynCenterWidget* cw, QWidget* parent = nullptr);

  void initialize();

protected:
  static const int DockingTitleHeight = 39;

private:
  DynCenterWidget* centerWidget;
  };
#endif // DYNDOCKABLE_H
