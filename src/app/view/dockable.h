#ifndef DOCKABLE_H
#define DOCKABLE_H
#include <QDockWidget>
class QString;
class QWidget;
class AbstractCenterWidget;


class Dockable : public QDockWidget
{    
public:
  Dockable(AbstractCenterWidget* cw, QWidget* parent = nullptr);

  QString  name() const;
  QString  id() const;
  QAction* viewAction();
  AbstractCenterWidget* centerWidget() { return dcw; }
  AbstractCenterWidget* centerWidget() const { return dcw; }

protected:
  static const int DockingTitleHeight = 39;
  virtual void closeEvent(QCloseEvent* e) override;
//  virtual void keyPressEvent(QKeyEvent* e) override;
//  virtual void keyReleaseEvent(QKeyEvent* e) override;

private:
  AbstractCenterWidget* dcw;
  };
#endif // DOCKABLE_H
