#ifndef DYNDOCKABLE_H
#define DYNDOCKABLE_H
#include <QDockWidget>
class QString;
class QWidget;
class AbstractCenterWidget;


class DynDockable : public QDockWidget
{    
public:
  DynDockable(AbstractCenterWidget* cw, QWidget* parent = nullptr);

  void     init(const QString& fileName, const QString& name, bool addScrollArea = false);
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
#endif // DYNDOCKABLE_H
