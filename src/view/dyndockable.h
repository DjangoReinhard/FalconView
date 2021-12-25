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

  void     init();
  QString  name() const;
  QString  id() const;
  QAction* viewAction();
  DynCenterWidget* centerWidget() { return dcw; }
  DynCenterWidget* centerWidget() const { return dcw; }

protected:
  static const int DockingTitleHeight = 39;
  virtual void closeEvent(QCloseEvent* e) override;
  virtual void keyPressEvent(QKeyEvent* e) override;
  virtual void keyReleaseEvent(QKeyEvent* e) override;

private:
  DynCenterWidget* dcw;
  };
#endif // DYNDOCKABLE_H
