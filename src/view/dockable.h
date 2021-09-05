#ifndef DOCKABLE_H
#define DOCKABLE_H
#include <QDockWidget>
class QString;
class QWidget;


class Dockable : public QDockWidget
{    
public:
  Dockable(const QString& fileName, const QString& title, QWidget* parent = nullptr);

protected:
  const int DockingTitleHeight = 39;
  };
#endif // DOCKABLE_H
