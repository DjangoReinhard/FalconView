#ifndef DYNFRAME_H
#define DYNFRAME_H
#include <QWidget>
class DynCenterWidget;
class QFrame;


class DynFrame : public QWidget
{
  Q_OBJECT
public:
  explicit DynFrame(DynCenterWidget* cw, bool visualFrame = false, QWidget *parent = nullptr);

  virtual void init();
  QAction* viewAction();
  QString  name() const;
  virtual void closeEvent(QCloseEvent* e) override;
  DynCenterWidget* centerWidget() { return dcw; }
  DynCenterWidget* centerWidget() const { return dcw; }

protected:
//  virtual void closeEvent(QCloseEvent* e) override;

private:
  QFrame*          frame;
  DynCenterWidget* dcw;
  };

#endif // DYNFRAME_H
