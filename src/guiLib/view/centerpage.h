#ifndef CENTERPAGE_H
#define CENTERPAGE_H
#include <QWidget>
//class CenterPageInterface;
class AbstractCenterWidget;
class QFrame;


class CenterPage : public QWidget
{
  Q_OBJECT
public:
  explicit CenterPage(AbstractCenterWidget* cp, bool visualFrame = false, QWidget *parent = nullptr);

  QString  name() const;
  QString  id() const;
  QAction* viewAction();
  inline AbstractCenterWidget* centerWidget() { return dcw; }
  inline AbstractCenterWidget* centerWidget() const { return dcw; }
  virtual void closeEvent(QCloseEvent* e) override;

private:
  QFrame*               frame;
  AbstractCenterWidget* dcw;
//  CenterPageInterface* cpi;
  };

#endif // CENTERPAGE_H
