#ifndef DYNFRAME_H
#define DYNFRAME_H
#include <QWidget>
class AbstractCenterWidget;
class QFrame;


class DynFrame : public QWidget
{
  Q_OBJECT
public:
  explicit DynFrame(AbstractCenterWidget* cw, bool visualFrame = false, QWidget *parent = nullptr);

  void     init();
  QString  name() const;
  QString  id() const;
  QAction* viewAction();
  AbstractCenterWidget* centerWidget() { return dcw; }
  AbstractCenterWidget* centerWidget() const { return dcw; }
  virtual void closeEvent(QCloseEvent* e) override;

private:
  QFrame*          frame;
  AbstractCenterWidget* dcw;
  };

#endif // DYNFRAME_H
