#ifndef DYNFRAME_H
#define DYNFRAME_H
#include <QWidget>
class DynCenterWidget;
class QFrame;


class DynFrame : public QWidget
{
  Q_OBJECT
public:
  explicit DynFrame(DynCenterWidget* cw, QWidget *parent = nullptr);

  virtual void init();
  QAction* viewAction();
  virtual void closeEvent(QCloseEvent* e) override;

protected:
//  virtual void closeEvent(QCloseEvent* e) override;

private:
  QFrame*          frame;
  DynCenterWidget* dcw;
  };

#endif // DYNFRAME_H
