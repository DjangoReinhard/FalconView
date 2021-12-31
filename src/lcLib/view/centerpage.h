#ifndef CENTERPAGE_H
#define CENTERPAGE_H
#include <QWidget>
class AbstractCenterWidget;
class QFrame;


class CenterPage : public QWidget
{
  Q_OBJECT
public:
  explicit CenterPage(AbstractCenterWidget* cw, bool visualFrame = false, QWidget *parent = nullptr);

  void     init(const QString& fileName, const QString& name, bool addScrollArea = false);
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

#endif // CENTERPAGE_H
