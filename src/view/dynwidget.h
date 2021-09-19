#ifndef DYNWIDGET_H
#define DYNWIDGET_H
#include <QWidget>
class QString;
class QWidget;
class QAction;


class DynWidget : public QWidget
{
  Q_OBJECT
public:
  DynWidget(QWidget* parent = nullptr)
   : QWidget(parent)
   , vAction(nullptr) {};

  void     init();
  QAction* viewAction();

protected:
  DynWidget(const QString& fileName, QWidget* parent = nullptr, int margin = 0);

  virtual void connectSignals() = 0;
  virtual void updateStyles()   = 0;
  QWidget*     loadFromUI(const QString& fileName);
  QWidget*     w; 

private:
  QAction* vAction;
  };
#endif // DYNWIDGET_H
