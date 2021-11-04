#ifndef DYNWIDGET_H
#define DYNWIDGET_H
#include <QFrame>
class QString;
class QWidget;
class QAction;
class QFile;


class DynWidget : public QFrame // QWidget
{
  Q_OBJECT
public:
  DynWidget(QWidget* parent = nullptr) : QFrame(parent), vAction(nullptr) {};

  void         init();
  QAction*     viewAction();

protected:
  DynWidget(const QString& fileName, QWidget* parent = nullptr);

  virtual void connectSignals() = 0;
  virtual void updateStyles()   = 0;
  QWidget*     loadFromUI(QFile& uiFile);
  QWidget*     w;

private:
  QAction*     vAction;
  };
#endif // DYNWIDGET_H
