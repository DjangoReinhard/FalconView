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

  void     init();
  QString  name() const;
  QString  id() const;
  QAction* viewAction();
  DynCenterWidget* centerWidget() { return dcw; }
  DynCenterWidget* centerWidget() const { return dcw; }
  virtual void closeEvent(QCloseEvent* e) override;
  virtual void keyPressEvent(QKeyEvent* e) override;
  virtual void keyReleaseEvent(QKeyEvent* e) override;

private:
  QFrame*          frame;
  DynCenterWidget* dcw;
  };

#endif // DYNFRAME_H
